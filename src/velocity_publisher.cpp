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
		vel_msg.angular.z = 3.3;

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
