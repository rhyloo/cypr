#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/twist.hpp"

// Esta libreria puede eliminarse, no se usará
#include <string>

class Actuator: public rclcpp::Node{
public:

  Actuator();

  ~Actuator();

  void sendRandomCommand(const std_msgs::msg::String::SharedPtr msg) const;
  void sendKeyCommand(const std_msgs::msg::String::SharedPtr msg) const;
  void sendSquareCommand(const std_msgs::msg::String::SharedPtr msg) const;
  void publishActuation() ;

private:
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr pub_;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub2_;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub3_;
  size_t count_;
};
