#include "ros/ros.h"
#include <iostream>
#include <math.h>
#include "geometry_msgs/Twist.h"

//Global Variables
    //Distance
float x = 0; 
float y = 0; 
    //Velocity
float vx = 0;
float vx_ = 0;
float vy = 0;
float vy_ = 0;

float ax = 0;
float ay = 0;


float dt = 1/20.0;

void calculate_distance(const geometry_msgs::Twist::ConstPtr& data);

int main(int argc, char** argv){
    ros::init(argc,argv,"distance");

    ros::NodeHandle n;

    ros::Subscriber dist_sub = n.subscribe("/mpu_data",1000,calculate_distance);

    ros::spin();

    return 0;
}

void calculate_distance(const geometry_msgs::Twist::ConstPtr& data){
    if(abs(data->linear.x)>1.2){
        vx = vx_ + (ax+data->linear.x)*dt/2;
        ax = data->linear.x;
    }
    else{
        vx = 0;
        ax = 0;
    }
    
    if(abs(data->linear.y)>0.7){
        vy = vy_ + (ay+data->linear.y)*dt/2;
        ay = data->linear.y;
    }
    else{
        vy = 0;
        ay = 0;
    }

    x = x + (vx_+vx)*dt/2;
    y = y + (vy_+vy)*dt/2;
    vx_ = vx;
    vy_ = vy;

    std::cout<<"x = "<<x<<" y = "<<y<<std::endl;
}
