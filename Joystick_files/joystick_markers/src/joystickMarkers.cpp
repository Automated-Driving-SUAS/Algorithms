
#include<ros/ros.h>
#include<std_msgs/String.h>
#include<sensor_msgs/Joy.h>


class joystickMarkers
{
public:
    joystickMarkers(){
        sub = nh.subscribe("/joy",10,&joystickMarkers::joy_callback,this);
        pub = nh.advertise<std_msgs::String>("joy_markers_pressed",10);
    }    

    void joy_callback(const sensor_msgs::Joy&msg ){
        std_msgs::String newMsg;
        if(msg.buttons[1]==1){
            newMsg.data = "Button X pressed --> Situation: traffic encounter.";                
        }
        else if(msg.buttons[3] == 1){
            newMsg.data ="Button Y pressed --> Situation: slight dodge of traffic.";                
        }
        else if(msg.buttons[0] == 1 ){
            newMsg.data = "Buttons A pressed --> Situation: robot blocks way of traffic.";    
        }
        else if(msg.buttons[2] == 1 ){
            newMsg.data = "Buttons B -->  Situation: robot is in crowd";    
        }
        if(newMsg.data != ""){
            pub.publish(newMsg);
        }
}

private:
    ros::NodeHandle nh;
    ros::Subscriber sub;
    ros::Publisher pub;
};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "joyMarker");
  joystickMarkers joyObject;
  ros::spin();
}
