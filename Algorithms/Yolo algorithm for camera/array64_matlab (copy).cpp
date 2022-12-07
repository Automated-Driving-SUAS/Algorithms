#include "ros/ros.h"
#include"vector"
#include"iostream"
#include "std_msgs/Int64MultiArray.h"


#include <sensor_msgs/CameraInfo.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>
#include <cv_bridge/cv_bridge.h>
#include "opencv2/opencv.hpp"
#include "darknet_ros_msgs/BoundingBox.h"
#include "darknet_ros_msgs/BoundingBoxes.h"


darknet_ros_msgs::BoundingBox boundingBox; 
darknet_ros_msgs::BoundingBoxes boundingBoxesResults;
std::vector<darknet_ros_msgs::BoundingBox> v;
float x_c = 0;
float y_c = 0;
float dist = 0;
ros::Publisher ArrayPublisher;
std_msgs::Int64MultiArray array ;
cv_bridge::CvImagePtr cv_ptr;
cv::Mat depthImage(480, 640, CV_16UC1);
void bb_callback(const darknet_ros_msgs::BoundingBoxes::ConstPtr& msg){

    v = msg->bounding_boxes;}

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
        
                double x0 ;
        /*double x1;
        double x2;
        double x3;
        double x4;
        double x5;
        double x6;
        double x7;*/

                int x_0 =0;
        /*int x_1 =120;
        int x_2 =200;
        int x_3 =280;
        int x_4 =360;
        int x_5 =440;
        int x_6 =520;
        int x_7 =640;*/
                for (int x_0=0; x_0<=100;x_0++){
                    int y_0 = 240;
                    x0 = depthImage.at<unsigned short>(y_0,x_0);
       /* x1 = depthImage.at<unsigned short>(y_0,x_1);
        x2 = depthImage.at<unsigned short>(y_0,x_2);
        x3 = depthImage.at<unsigned short>(y_0,x_3);
        x4 = depthImage.at<unsigned short>(y_0,x_4);
        x5 = depthImage.at<unsigned short>(y_0,x_5);
        x6 = depthImage.at<unsigned short>(y_0,x_6);
        x7 = depthImage.at<unsigned short>(y_0,x_7);*/
            
        //x0 = 1;
        
                    array.data.push_back(x0);}
        /*array.data.push_back(x1);
        array.data.push_back(x2);
        array.data.push_back(x3);
        array.data.push_back(x4);
        array.data.push_back(x5);
        array.data.push_back(x6);
        array.data.push_back(x7);*/
            
                x_c = ((int) x.xmin + (int) x.xmax)/2;
                y_c = ((int) x.ymin + (int) x.ymax)/2;
                dist = depthImage.at<unsigned short>(y_c, x_c);
                array.data.push_back(dist/10);
                
    });
        
            //array.data[((x_c*8)/640)]=(dist/10) ;
            ArrayPublisher.publish(array);
            array.data.clear();
        
                    /*x_c = ((int) x.xmin + (int) x.xmax)/2;
            y_c = ((int) x.ymin + (int) x.ymax)/2;
            dist = depthImage.at<unsigned short>(y_c, x_c);
            array.data[((x_c*19)/640)]=(dist/10) ;*/
            //ArrayPublisher.publish(array);
            //array.data.clear();
        };
        
        //array.data.clear();
        ros::spinOnce();

        return 0;
}

    //ros::spin();

   

