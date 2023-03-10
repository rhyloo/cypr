#include <first_pkg/actuator.hpp>
#include <math.h>
using std::placeholders::_1;

Actuator::Actuator(): Node ("actuator"){
  pub_ = this->create_publisher<geometry_msgs::msg::Twist> ("/turtle1/cmd_vel", 10);
  sub_ = this->create_subscription<std_msgs::msg::String> ("/cmd_random",10,std::bind(&Actuator::sendRandomCommand, this, _1));
  sub2_ = this->create_subscription<std_msgs::msg::String> ("/cmd_key",10,std::bind(&Actuator::sendKeyCommand, this, _1));
  sub3_ = this->create_subscription<std_msgs::msg::String> ("/cmd_square",10,std::bind(&Actuator::sendSquareCommand, this, _1));
}

Actuator::~Actuator()
{
  printf("Leaving gently\n");
}

void Actuator::sendRandomCommand(const std_msgs::msg::String::SharedPtr msg) const{
  geometry_msgs::msg::Twist actuation;
  float linear, angular;

  RCLCPP_INFO (this->get_logger(), "Received: '%s'",msg->data.c_str());

  if(msg->data=="stop"){
    linear = 0; angular=0;
  }else if (msg->data=="fordwards"){
    linear=1;angular=0;
  }else if (msg->data=="backwards"){
    linear=-1;angular=0;
  }else if (msg->data=="left"){
    linear=0;angular=-1;
  }else if (msg->data=="right"){
    linear=0;angular=1;
  }

  actuation.linear.x = linear;
  actuation.angular.z = angular;

  pub_->publish(actuation);

}

geometry_msgs::msg::Twist keyControllerActuation;
void Actuator::sendKeyCommand(const std_msgs::msg::String::SharedPtr msg) const{
  static float linear = 0.0;
  static float angular = 0.0;

  if(msg->data=="stop"){
    linear = 0; angular=0;
  }else if (msg->data=="v++"){
    linear=linear+1.0;
  }else if (msg->data=="v--"){
    linear=linear-1.0;
  }else if (msg->data=="w++"){
    angular=angular+1.0;
  }else if (msg->data=="w--"){
    angular=angular-1.0;
  }

  keyControllerActuation.linear.x = linear;
  keyControllerActuation.angular.z = angular;
  RCLCPP_INFO (this->get_logger(), "Velocidad lineal: '%f'",linear);
  RCLCPP_INFO (this->get_logger(), "Velocidad angular: '%f'",angular);
}

void Actuator::sendSquareCommand(const std_msgs::msg::String::SharedPtr msg) const{

  RCLCPP_INFO (this->get_logger(), "Received: '%s'",msg->data.c_str());

  if(msg->data=="avanzar"){
  keyControllerActuation.linear.x = 1;
  keyControllerActuation.angular.z = 0;
  }else if (msg->data=="girar"){
  keyControllerActuation.linear.x = 0;
  keyControllerActuation.angular.z =  1.57079633; //rad/s
  }else if (msg->data=="stop"){
  keyControllerActuation.linear.x = 0;
  keyControllerActuation.angular.z =0; //rad/s
  }
  
}

void Actuator::publishActuation(){
  pub_->publish(keyControllerActuation);
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc,argv);
  //  Actuator Publicador;
  auto node = std::make_shared<Actuator>();

  rclcpp::Rate loop_rate(20);
  
  while (rclcpp::ok()) {
    //Atendemos a los topics subscritos y modificamos velocidades
    rclcpp::spin_some(node);
    //publicamos Twist al robot (idealmente con un m??todo de la clase)
    node->publishActuation();
    // mantenemos rate
    loop_rate.sleep();
  }
  
  // rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
