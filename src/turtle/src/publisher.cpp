#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/Spawn.h>
#include <turtlesim/Kill.h>
#include <vector>
#include <math.h>

using namespace std;

void move_turtle(ros::Publisher &pub_data, double linear_x, double linear_y, double angular_z = 0)
{
    geometry_msgs::Twist msg;
    msg.linear.x = linear_x;
    msg.linear.y = linear_y;
    msg.angular.z = angular_z != 0 ? (angular_z * M_PI) / 180 : 0;

    ros::Rate loop_rate(1); // 1 Hz

    pub_data.publish(msg);
    loop_rate.sleep();

    // Stop
    msg.linear.x = 0;
    msg.linear.y = 0;
    pub_data.publish(msg);
}

void kill_and_spawn(ros::NodeHandle &nh, const string &name, float x, float y)
{
    ros::ServiceClient kill_client = nh.serviceClient<turtlesim::Kill>("kill");
    ros::ServiceClient spawn_client = nh.serviceClient<turtlesim::Spawn>("spawn");

    turtlesim::Kill kill_srv;
    kill_srv.request.name = name;

    if (kill_client.call(kill_srv))
    {
        ROS_INFO("Killed turtle: %s", name.c_str());
    }
    else
    {
        ROS_ERROR("Failed to kill turtle: %s", name.c_str());
    }

    turtlesim::Spawn spawn_srv;
    spawn_srv.request.x = x;
    spawn_srv.request.y = y;
    spawn_srv.request.theta = 0;
    spawn_srv.request.name = name;

    if (spawn_client.call(spawn_srv))
    {
        ROS_INFO("Spawned turtle: %s", spawn_srv.response.name.c_str());
    }
    else
    {
        ROS_ERROR("Failed to spawn turtle");
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "turtle_publisher");
    ros::NodeHandle nh;

    // Publisher
    ros::Publisher pub_data = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);

    // Start X
    kill_and_spawn(nh, "turtle1", 2, 5);
    ros::Duration(1).sleep();

    // X
    move_turtle(pub_data, -1.5, 1.5);
    move_turtle(pub_data, 0.75, -0.75);
    move_turtle(pub_data, 0.75, 0.75);
    move_turtle(pub_data, -1.5, -1.5);

    // Spasi
    kill_and_spawn(nh, "turtle1", 2.5, 5);
    ros::Duration(1).sleep();

    // A
    move_turtle(pub_data, 0.7, 1.5);
    move_turtle(pub_data, 0.7, -1.5);
    move_turtle(pub_data, -0.35, 0.75);
    move_turtle(pub_data, -0.7, 0);

    // Spasi
    kill_and_spawn(nh, "turtle1", 4.5, 5);
    ros::Duration(1).sleep();

    // V
    move_turtle(pub_data, -0.5, 1.5);
    move_turtle(pub_data, 0.5, -1.5);
    move_turtle(pub_data, 0.5, 1.5);

    // Spasi
    kill_and_spawn(nh, "turtle1", 5.5, 5);
    ros::Duration(1).sleep();

    // I
    move_turtle(pub_data, 0, 1.5);

    // Spasi
    kill_and_spawn(nh, "turtle1", 6, 5);
    ros::Duration(1).sleep();

    // E
    move_turtle(pub_data, 0, 1.5);
    move_turtle(pub_data, 0.75, 0);
    move_turtle(pub_data, -0.75, 0);
    move_turtle(pub_data, 0, -0.75);
    move_turtle(pub_data, 0.75, 0);
    move_turtle(pub_data, -0.75, 0);
    move_turtle(pub_data, 0, -0.75);
    move_turtle(pub_data, 0.75, 0);

    // Spasi
    kill_and_spawn(nh, "turtle1", 7.25, 5);
    ros::Duration(1).sleep();

    // R
    move_turtle(pub_data, 0, 1.5);
    move_turtle(pub_data, 0.375, 0);
    move_turtle(pub_data, 1.25, 0, -180);
    move_turtle(pub_data, 0.375, 0, 0);
    move_turtle(pub_data, -0.75, 0.75, 0);

    // Spasi
    kill_and_spawn(nh, "turtle1", 8.5, 5);
    ros::Duration(1).sleep();

    // A
    move_turtle(pub_data, 0.7, 1.5);
    move_turtle(pub_data, 0.7, -1.5);
    move_turtle(pub_data, -0.35, 0.75);
    move_turtle(pub_data, -0.7, 0);

    // Garis bawah
    kill_and_spawn(nh, "turtle1", 0.75, 4.5);
    ros::Duration(1).sleep();
    move_turtle(pub_data, 9, 0);

    // Love
    kill_and_spawn(nh, "turtle1", 5, 9);
    ros::Duration(1).sleep();
    move_turtle(pub_data, 0.3, 1.0, 60);
    move_turtle(pub_data, 0.5, 1.0, 90);
    move_turtle(pub_data, 0.5, 1.0, 90);
    move_turtle(pub_data, 0.75, 2, 30);
    move_turtle(pub_data, -1, 2, 30);
    move_turtle(pub_data, -0.75, 1.0, 90);
    move_turtle(pub_data, -0.75, 1.0, 90);
    move_turtle(pub_data, -0.3, 1.0, 60);

    return 0;
}