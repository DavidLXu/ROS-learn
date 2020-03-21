# A Simple Implement of Publisher in ROS

## create workspace

```bash
# create workspace
mkdir -p ~/catkin_ws/src
cd ~/catkin_ws/src
catkin_init_workspace
```

```bash
# complie workspace
cd ~/catkin_ws/
catkin_make
```

```shell
# set environment variable
source devel/setup.bash # only works once within current active shell
# you can add this line to ~/.bashrc to get executed everytime in a new shell
```

```bash
# check environment variable
echo $ROS_PACKAGE_PATH
```

## create package

```bash
# create package
cd ~/catkin_ws/src
catkin_create_pkg learning topic roscpp rospy std_msgs geometry_msgs turtlesim 
```

## write code

path: ~/catkin_ws/src/learning_topic/src

```c++
//publish the turtle1/cmd_vel topic, message class geometry_msgs::Twist

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

int main(int argc, char ** argv)
{
	// initialize ROS node
	ros::init(argc,argv,"velocity_publisher");
	
	// create node handle (handles the resource of node)
	ros::NodeHandle n;

	// create a publisher, with the topic of /turtle1/cmd_vel, message type geometry_msgs::Twist, queue length 10 (queue is like cache, if too short, may experience drop of frame)
	ros::Publisher turtle_vel_pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",10);

	// set loop frequency
	ros::Rate loop_rate(10);

	int count = 0;
	double speed = 0.1;
	while (ros::ok())
	{
		// initialize geometry_msgs::Twist
		geometry_msgs::Twist vel_msg;
		speed += 0.05;
		vel_msg.linear.x = speed;
		vel_msg.angular.z = 0.2;

		// publish message
		turtle_vel_pub.publish(vel_msg);
		// logging
		ROS_INFO("Publish turtle velocity command[%0.2f m/s,%0.2f rad/s]",
					vel_msg.linear.x,vel_msg.angular.z);
		// loop as the rate
		loop_rate.sleep();

	}
	return 0;
}
```

## edit CMakeList.txt

path: ~/catkin_ws/src/learning_topic/

add to the last of *Build* section, right before *Install* section

```cmake
add_executable(velocity_publisher src/velocity_publisher.cpp) 
# compile src/velocity_publisher.cpp as velocity_publisher
target_link_libraries(velocity_publisher ${catkin_LIBRARIES})
# link api to ros libraries
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
rosrun learning_topic velocity_publisher
```

