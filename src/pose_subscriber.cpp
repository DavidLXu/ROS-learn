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
