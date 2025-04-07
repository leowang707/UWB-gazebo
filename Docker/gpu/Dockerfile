FROM nvidia/cuda:11.3.1-devel-ubuntu20.04

SHELL ["/bin/bash", "-o", "pipefail", "-c"]
ENV DEBIAN_FRONTEND=noninteractive
ENV USER=leowang707
ENV HOME=/home/${USER}

# --------------------- 系統基礎套件 ---------------------
RUN echo 'Etc/UTC' > /etc/timezone && \
    ln -fs /usr/share/zoneinfo/Etc/UTC /etc/localtime && \
    apt-get update && apt-get -y dist-upgrade && \
    apt-get install -y --no-install-recommends \
    tzdata sudo locales curl gnupg2 wget git \
    build-essential cmake unzip pkg-config make \
    vim net-tools \
    python3-dev python3-pip python3-numpy \
    python3-venv python3-setuptools \
    software-properties-common lsb-release dirmngr \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# --------------------- 建立非 root 使用者 ---------------------
RUN useradd -m -s /bin/bash ${USER} && \
    usermod -aG sudo ${USER} && \
    echo "root ALL=(ALL) ALL" >> /etc/sudoers && \
    echo "${USER} ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

# --------------------- 安裝 cuDNN ---------------------
RUN apt-get update && apt-get install -y --no-install-recommends \
    libcudnn8 libcudnn8-dev && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

# --------------------- 安裝 ROS Noetic 基礎系統 ---------------------
RUN apt-get update && apt-get install -y --no-install-recommends \
    curl gnupg2 lsb-release apt-transport-https ca-certificates && \
    echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" | tee /etc/apt/sources.list.d/ros-latest.list && \
    curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.key | apt-key add - && \
    apt-get update && apt-get install -y --no-install-recommends \
    ros-noetic-ros-base \
    python3-rosdep \
    python3-rospy \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

RUN rosdep init && rosdep update --rosdistro noetic

# --------------------- 安裝 ROS 工具與 Gazebo 模擬 ---------------------
RUN apt-get update && apt-get install -y --no-install-recommends \
    ros-noetic-rviz \
    ros-noetic-rqt \
    ros-noetic-rqt-common-plugins \
    ros-noetic-rqt-robot-plugins \
    ros-noetic-tf2-tools \
    ros-noetic-xacro \
    ros-noetic-urdf \
    ros-noetic-robot-state-publisher \
    ros-noetic-joint-state-publisher \
    gazebo11 \
    libgazebo11-dev \
    ros-noetic-gazebo-ros \
    ros-noetic-gazebo-ros-pkgs \
    ros-noetic-gazebo-ros-control \
    ros-noetic-gazebo-plugins \
    ros-noetic-hector-gazebo-plugins \
    python3-catkin-tools \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# --------------------- Python 擴充工具（非影像處理） ---------------------
RUN pip3 install tqdm

# --------------------- 設定 bash 環境變數 ---------------------
# Source ROS
RUN echo "source /opt/ros/noetic/setup.bash" >> /root/.bashrc && \
    echo "source /opt/ros/noetic/setup.bash" >> ${HOME}/.bashrc

# Source catkin_ws + ROS_PACKAGE_PATH
RUN echo "source ${HOME}/UWB-gazebo/catkin_ws/devel/setup.bash" >> ${HOME}/.bashrc && \
    echo "export ROS_PACKAGE_PATH=${HOME}/UWB-gazebo/catkin_ws/src:\$ROS_PACKAGE_PATH" >> ${HOME}/.bashrc

RUN echo "source ${HOME}/UWB-gazebo/catkin_ws/devel/setup.bash" >> /root/.bashrc && \
    echo "export ROS_PACKAGE_PATH=${HOME}/UWB-gazebo/catkin_ws/src:\$ROS_PACKAGE_PATH" >> /root/.bashrc

# 加入 GAZEBO_MODEL_PATH 設定（root 與 HOME 都加）
RUN echo "export GAZEBO_MODEL_PATH=\$GAZEBO_MODEL_PATH:${HOME}/UWB-gazebo/catkin_ws/src/gazebo_uwb/models:/usr/share/gazebo-11/models" >> /root/.bashrc && \
    echo "export GAZEBO_MODEL_PATH=\$GAZEBO_MODEL_PATH:${HOME}/UWB-gazebo/catkin_ws/src/gazebo_uwb/models:/usr/share/gazebo-11/models" >> ${HOME}/.bashrc

# 加入 GAZEBO_PLUGIN_PATH 設定（root 與 HOME 都加）
RUN echo "export GAZEBO_PLUGIN_PATH=\$GAZEBO_PLUGIN_PATH:${HOME}/UWB-gazebo/catkin_ws/devel/lib" >> /root/.bashrc && \
    echo "export GAZEBO_PLUGIN_PATH=\$GAZEBO_PLUGIN_PATH:${HOME}/UWB-gazebo/catkin_ws/devel/lib" >> ${HOME}/.bashrc

# 再次設定用戶權限（確保 ${USER} 擁有 sudo 權限）
RUN echo "root ALL=(ALL) ALL" >> /etc/sudoers && \
    echo "${USER} ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

# --------------------- 預設啟動 ---------------------
CMD ["bash"]
