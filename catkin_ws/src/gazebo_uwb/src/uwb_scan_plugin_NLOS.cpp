// uwb_scan_plugin_NLOS.cpp (OnUpdate 版本 + 修正 Ray 高度 + Debug 降為 1Hz)
#include <gazebo/common/Plugin.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/gazebo.hh>
#include <gazebo/common/Events.hh>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sstream>
#include <random>

namespace gazebo
{
  class UWBScanPluginNLOS : public ModelPlugin
  {
  public:
    void Load(physics::ModelPtr _model, sdf::ElementPtr /*_sdf*/)
    {
      this->model = _model;
      this->world = _model->GetWorld();

      if (!ros::isInitialized()) {
        int argc = 0;
        char **argv = NULL;
        ros::init(argc, argv, "uwb_scan_plugin_nlos_node",
                  ros::init_options::NoSigintHandler);
      }

      this->rosNode.reset(new ros::NodeHandle("~"));
      std::string topicName = "/" + this->model->GetName() + "/nearest";
      this->rosPub = this->rosNode->advertise<std_msgs::String>(topicName, 10);

      rng.seed(std::random_device()());

      this->ray = boost::dynamic_pointer_cast<physics::RayShape>(
          this->world->Physics()->CreateShape("ray", physics::CollisionPtr()));

      if (!this->ray)
      {
        ROS_ERROR("[UWB Plugin] Failed to create RayShape.");
        return;
      }

      this->updateConnection = event::Events::ConnectWorldUpdateBegin(
          std::bind(&UWBScanPluginNLOS::OnUpdate, this));
    }

    void OnUpdate()
    {
      if (++updateCounter % 1000 != 0)  // 10Hz 模擬下每秒觸發一次
        return;

      auto selfPose = this->model->WorldPose().Pos();
      std::string selfName = this->model->GetName();

      double minDist = 1e6;
      std::string nearestName = "";
      bool nearestIsNLOS = false;

      for (auto &m : this->world->Models())
      {
        if (m->GetName() == selfName) continue;
        if (m->GetName().find("uwb_anchor") == std::string::npos) continue;

        auto pos = m->WorldPose().Pos();
        double dist = selfPose.Distance(pos);
        bool isNLOS = false;

        if (this->ray)
        {
          ignition::math::Vector3d start = selfPose;
          ignition::math::Vector3d end = pos;
          start.Z() += 0.3;
          end.Z() += 0.3;

          this->ray->SetPoints(start, end);
          std::string entityName;
          double rayDist;
          this->ray->GetIntersection(rayDist, entityName);

          if (!entityName.empty() && entityName != m->GetName()) {
            isNLOS = true;
            std::cout << "[DEBUG] NLOS detected from " << selfName
                      << " to " << m->GetName()
                      << ". Ray hit: " << entityName << std::endl;
          }
        }

        if (isNLOS) {
          dist += nlosBias + nlosNoise(rng);
        } else {
          dist += noise(rng);
        }

        if (dist < minDist) {
          minDist = dist;
          nearestName = m->GetName();
          nearestIsNLOS = isNLOS;
        }
      }

      std_msgs::String msg;
      std::stringstream ss;
      ss << "Nearest anchor: " << nearestName
         << " | Distance: " << minDist
         << " | LOS: " << (nearestIsNLOS ? "false" : "true");
      msg.data = ss.str();
      this->rosPub.publish(msg);
    }

  private:
    physics::ModelPtr model;
    physics::WorldPtr world;
    std::unique_ptr<ros::NodeHandle> rosNode;
    ros::Publisher rosPub;
    physics::RayShapePtr ray;
    event::ConnectionPtr updateConnection;
    int updateCounter = 0;

    std::default_random_engine rng;
    std::normal_distribution<double> noise{0.0, 0.05};
    std::normal_distribution<double> nlosNoise{0.0, 0.2};
    double nlosBias = 1.0;
  };

  GZ_REGISTER_MODEL_PLUGIN(UWBScanPluginNLOS)
} // namespace gazebo
