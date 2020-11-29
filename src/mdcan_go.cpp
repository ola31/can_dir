#include "ros/ros.h"
#include "std_msgs/UInt8MultiArray.h"
//#include "std_msgs/MultiArrayLayout.h"
//#include "std_msgs/MultiArrayDimension.h"

void mdcanCallback(const std_msgs::UInt8MultiArray::ConstPtr& msg)
{
    ROS_INFO("I heard: [%d],[%d],[%d],[%d]", msg->data.at(0),msg->data.at(1),msg->data.at(2),msg->data.at(3));
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "mdcan_go");
  ros::NodeHandle nh;

  ros::Publisher mdcan_pub = nh.advertise<std_msgs::UInt8MultiArray>("mdcan", 10);

 //ros::Subscriber sub = nh.subscribe("mdcan_go", 10, mdcanCallback);

  ros::Rate loop_rate(10);

  //int PID; //parameter id
 int D0,D1,D2,D3,D4,D5,D6,D7;  //data(8바이트) 1~7
//int PI;
  while (ros::ok())
  {
    std_msgs::UInt8MultiArray array;
    //array.data.resize(8);

    //printf("PID :");
    //scanf("%d",&D0);
    printf("PID D1 D2 D3 D4 D5 D6 D7 :");
    scanf("%d %d %d %d %d %d %d %d",&D0,&D1,&D2,&D3,&D4,&D5,&D6,&D7);

    //if(D0<0){break;}


    //array.layout.dim[0].label="height";
    //array.layout.dim[0].size=8;
    //array.layout.dim[0].stride=1;

    //array.layout.data_offset=0;
    array.data.clear();
/*
    array.data[0]=D0;
    array.data[1]=D1;
    array.data[2]=D2;
    array.data[3]=D3;
    array.data[4]=D4;
    array.data[5]=D5;
    array.data[6]=D6;
    array.data[7]=D7;*/

    //D0=1,D2=1,D3=1,D4=1,D5=1,D6=1,D7=1,D1=1;
    array.data.push_back(D0);
    array.data.push_back(D1);
    array.data.push_back(D2);
    array.data.push_back(D3);
    array.data.push_back(D4);
    array.data.push_back(D5);
    array.data.push_back(D6);
    array.data.push_back(D7);
    //PID=1;
    //uint8_t aiai[8]={1,2,3,4,5,6,7,8};
    //D1=1;D2=2;D3=3;D4=4;D5=5;D6=6;D7=7;
    //array.data=aiai;
    mdcan_pub.publish(array);
    ROS_INFO("send %d | %d %d %d %d %d %d %d\n",D0,D1,D2,D3,D4,D5,D6,D7);


    ros::Subscriber sub = nh.subscribe("recived", 10, mdcanCallback);

    ros::spinOnce();

    loop_rate.sleep();
  }

  return 0;
}
