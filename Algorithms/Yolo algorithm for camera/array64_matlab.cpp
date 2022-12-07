#include "ros/ros.h"
#include"vector"
#include"iostream"
#include "std_msgs/Int64MultiArray.h"
#include "darknet_ros_msgs/BoundingBox.h"
#include "darknet_ros_msgs/BoundingBoxes.h"
//#include "position_msgs/ObjectPosition.h"
//#include "position_msgs/ObjectPositions.h"
#include <sensor_msgs/CameraInfo.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>
#include <cv_bridge/cv_bridge.h>
#include "opencv2/opencv.hpp"

darknet_ros_msgs::BoundingBox boundingBox; 
darknet_ros_msgs::BoundingBoxes boundingBoxesResults;
std::vector<darknet_ros_msgs::BoundingBox> v;
//position_msgs::ObjectPositions objectpositionresults;
ros::Publisher ArrayPublisher;
std_msgs::Int64MultiArray array ;
cv_bridge::CvImagePtr cv_ptr;
cv::Mat depthImage(480, 640, CV_16UC1);



int x_c = 0;
int y_c = 0;
double dist = 0;

void bb_callback(const darknet_ros_msgs::BoundingBoxes::ConstPtr& msg){

    v = msg->bounding_boxes;
/*
    std::for_each(v.begin(), v.end(), [](const darknet_ros_msgs::BoundingBox& x){
        //position_msgs::ObjectPosition objectPosition;
        std_msgs::Int64MultiArray array ;
        for (int64_t i = 0; i < 19; i++){
             array.data.push_back(0);
        }
        x_c = ((int) x.xmin + (int) x.xmax)/2;
        y_c = ((int) x.ymin + (int) x.ymax)/2;
        dist = depthImage.at<unsigned short>(y_c, x_c);
        //objectPosition.x = 
        array.data[((x_c*19)/640)]=(dist/10) ;
        //objectPosition.y = ((y_c*135)/480);
        //objectPosition.z = (dist/10);
        //objectpositionresults.object_positions.push_back(objectPosition);
        ArrayPublisher.publish(array);
        array.data.clear();
    });
    //PositionPublisher.publish(objectpositionresults);
    //array.clear();*/
}

void di_callback(const sensor_msgs::Image::ConstPtr& msg){
    try{
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::TYPE_16UC1);
    }catch (cv_bridge::Exception& ex){
        ROS_ERROR("error");
        exit(-1);
    }
    depthImage = cv_ptr->image;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "Array64_Matlab");
    ros::NodeHandle n;
   
    ros::Subscriber Depth_image = n.subscribe("/camera/aligned_depth_to_color/image_raw", 10, di_callback);
    ros::Subscriber Inference_result = n.subscribe("/darknet_ros/bounding_boxes", 10, bb_callback);
    ArrayPublisher = n.advertise<std_msgs::Int64MultiArray>("/array64_matlab/message", 10);
    while (ros::ok())  {
        //std_msgs::Int64MultiArray array ;
        //array.data.clear();
        std::for_each(v.begin(), v.end(), [](const darknet_ros_msgs::BoundingBox& x){
            std_msgs::Int64MultiArray array ;
            x_c = ((int) x.xmin + (int) x.xmax)/2;
            y_c = ((int) x.ymin + (int) x.ymax)/2;
            dist = depthImage.at<unsigned short>(y_c, x_c);
            for (float i = 0; i <=8; i++){
                array.data.push_back(0);
                
            }
            array.data[((x_c*8)/640)]=(dist/10) ;
            ArrayPublisher.publish(array);
            /*x_c = ((int) x.xmin + (int) x.xmax)/2;
            y_c = ((int) x.ymin + (int) x.ymax)/2;
            dist = depthImage.at<unsigned short>(y_c, x_c);
            array.data[((x_c*19)/640)]=(dist/10) ;*/
            //ArrayPublisher.publish(array);
            //array.data.clear();
        });
        
        //array.data.clear();
        ros::spinOnce();
    }

    //ros::spin();

    return 0;
}
