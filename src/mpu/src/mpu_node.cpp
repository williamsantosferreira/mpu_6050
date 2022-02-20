#include <iostream>
#include "ros/ros.h"
#include "mpu_6050.h"
#include "std_msgs/String.h"
#include <sstream>
#include "geometry_msgs/Twist.h"

MPU_6050 sensor;


void leitura_dados_sensor();

int main(int argc, char **argv){
	geometry_msgs::Twist info;	
	ros::init(argc,argv,"mpu_node");

	ros::NodeHandle n;

	ros::Publisher pub = n.advertise<geometry_msgs::Twist>("mpu_data",1000);

	while(ros::ok()){
	sensor.read_data();	

	info.linear.x = sensor.read_ax();
        info.linear.y = sensor.read_ay();
        info.linear.z = sensor.read_az();

        info.angular.x = sensor.read_gx();
        info.angular.y = sensor.read_gy();
        info.angular.z = sensor.read_gz();

	pub.publish(info);

	}

return 0;
}

