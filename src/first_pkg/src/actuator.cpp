#include <first_pkg/actuator.hpp>

using std::placeholders::_1;

Actuator::Actuator(): Node ("actuator"){
  pub_ = this->create_publisher<geometry_msgs::msg::Twist> ("/turtle1/cmd_vel", 10);
  sub_ = this->create_subscription<std_msgs::msg::String> ("/cmd_random",10,std::bind(&Actuator::execute_command, this, _1));
}

Actuator::~Actuator()
{
  printf("Leaving gently\n");
}

void Actuator::execute_command(const std_msgs::msg::String::SharedPtr msg) const{
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

int main(int argc, char * argv[])
{
  rclcpp::init(argc,argv);
  auto node = std::make_shared<Actuator>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
