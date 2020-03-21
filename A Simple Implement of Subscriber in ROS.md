# A Simple Implement of Subscriber in ROS

## workspace

under the same workspace with Publisher

## package

under the same package

## write code

path: ~/catkin_ws/src/learning_topic/src/pose_subscriber.cpp

```c++
// subscibe the /turtle1/pose topic, msg type turtlesim::Pose

#include <ros/ros.h>
#include <turtlesim/Pose.h>

// received subscribed msg, enter the poseCallback function
void poseCallback(const turtlesim::Pose::ConstPtr& msg)
{
	// print the received msgs
	ROS_INFO("Turtle pose: x:%0.6f, y:%0.6f",msg->x,msg->y);
}

int main(int argc, char** argv)
{
	// initialize ROS node
	ros::init(argc,argv,"velocity_publisher");

	// create node handle (manages node resources)
	ros::NodeHandle n;

	// create a subscriber, with the topic of /turtle1/pose, callback function being poseCallback
	ros::Subscriber pos_sub = n.subscribe("/turtle1/pose",10,poseCallback);
	// note: because the subscribe does not know when to receive the msg
	// so uses callback, think of interrupt in MCUS
	// once the data comes in, call the callback function immediately

	// waiting for callback in loop
	ros::spin(); // this is more like a dead loop

	return 0;

}

```

## edit CMakeList.txt

path: ~/catkin_ws/src/learning_topic/

add to the last of *Build* section, right before *Install* section

```cmake
#right after these
'''
# compile src/velocity_publisher.cpp as velocity_publisher
add_executable(velocity_publisher src/velocity_publisher.cpp) 
# link api to ros libraries
target_link_libraries(velocity_publisher ${catkin_LIBRARIES})
'''
add_executable(pose_subscriber src/pose_subscriber.cpp) 
target_link_libraries(pose_subscriber ${catkin_LIBRARIES})

```

##  compile package

```bash
# compile package
cd ~/catkin_ws/
catkin_make
source ~/catkin_ws/devel/setup.bash
```



## run program

``` bash
# open one shell
roscore
# open another shell
rosrun turtlesim turtlesim_node
# open another shell
rosrun learning_topic pose_subscriber
```

## a problem

However, pose_subscriber and velocity_publisher can't be run at the same time.

I am just at the beginning of ROS, anyone know this please contact me at xulixincn@163.com.

But you can get python versions run together. The python files along with cpp source code are uploaded, see my github.

Special thanks!