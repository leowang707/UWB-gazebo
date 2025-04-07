// uwb_scan_plugin.cpp
#include <gazebo/common/Plugin.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/gazebo.hh>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <thread>
#include <sstream>

namespace gazebo
{
  class UWBScanPlugin : public ModelPlugin
  {
  public:
    void Load(physics::ModelPtr _model, sdf::ElementPtr /*_sdf*/)
    {
      this->model = _model;
      this->world = _model->GetWorld();

      // ROS 初始化（只初始化一次）
      if (!ros::isInitialized()) {
        int argc = 0;
        char **argv = NULL;
        ros::init(argc, argv, "uwb_scan_plugin_node",
                  ros::init_options::NoSigintHandler);
      }

      this->rosNode.reset(new ros::NodeHandle("~"));

      std::string topicName = "/" + this->model->GetName() + "/nearest";
      this->rosPub = this->rosNode->advertise<std_msgs::String>(topicName, 10);

      // 啟動執行緒定期更新
      this->updateThread = std::thread(std::bind(&UWBScanPlugin::Loop, this));
    }

    void Loop()
    {
      ros::Rate rate(10); // 10 Hz 更新頻率
      while (ros::ok())
      {
        auto selfPose = this->model->WorldPose().Pos();
        std::string selfName = this->model->GetName();

        double minDist = 1e6;
        std::string nearestName = "";

        for (auto &m : this->world->Models())
        {
          if (m->GetName() == selfName) continue;
          if (m->GetName().find("uwb_anchor") == std::string::npos) continue;

          auto pos = m->WorldPose().Pos();
          double dist = selfPose.Distance(pos);
          if (dist < minDist)
          {
            minDist = dist;
            nearestName = m->GetName();
          }
        }

        std_msgs::String msg;
        std::stringstream ss;
        ss << "Nearest anchor: " << nearestName << " | Distance: " << minDist;
        msg.data = ss.str();
        this->rosPub.publish(msg);

        rate.sleep();
      }
    }

  private:
    physics::ModelPtr model;
    physics::WorldPtr world;
    std::unique_ptr<ros::NodeHandle> rosNode;
    ros::Publisher rosPub;
    std::thread updateThread;
  };

  GZ_REGISTER_MODEL_PLUGIN(UWBScanPlugin)
} // namespace gazebo