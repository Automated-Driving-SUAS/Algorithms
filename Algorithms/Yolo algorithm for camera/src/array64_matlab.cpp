#include "ros/ros.h"
#include"vector"
#include"iostream"
#include "std_msgs/Int64MultiArray.h"


#include <sensor_msgs/CameraInfo.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>
#include <cv_bridge/cv_bridge.h>
#include "opencv2/opencv.hpp"

ros::Publisher ArrayPublisher;
std_msgs::Int64MultiArray array ;
cv_bridge::CvImagePtr cv_ptr;
cv::Mat depthImage(480, 640, CV_16UC1);

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
   
    ArrayPublisher = n.advertise<std_msgs::Int64MultiArray>("/array64_matlab/message", 10);
    while (ros::ok())  {
        std_msgs::Int64MultiArray array ;
        array.data.clear();
        for (int64_t i=0; i<=47; i++){
            array.data.push_back(depthImage.at<unsigned short>(240,(int)i*10)) ;

        }
            //array.data[((x_c*8)/640)]=(dist/10) ;
        ArrayPublisher.publish(array);
        array.data.clear();
        ros::spinOnce();
        
                    /*x_c = ((int) x.xmin + (int) x.xmax)/2;
            y_c = ((int) x.ymin + (int) x.ymax)/2;
            dist = depthImage.at<unsigned short>(y_c, x_c);
            array.data[((x_c*19)/640)]=(dist/10) ;*/
            //ArrayPublisher.publish(array);
            //array.data.clear();
        };
        
        //array.data.clear();
        ros::spin();

        return 0;
}

    //ros::spin();

   

