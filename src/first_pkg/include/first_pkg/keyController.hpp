#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/twist.hpp"

// Esta libreria puede eliminarse, no se usará
#include <string>

class keyController: public rclcpp::Node{
public:
  keyController();
  ~keyController();

  void execute_command(const std_msgs::msg::String::SharedPtr msg) const;

private:
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr pub_;
  size_t count_;
};
