#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class squareController : public rclcpp::Node {
public:
  squareController(); // Mi constructor, se llama exactamente igual que la clase
  ~squareController(); // Destructor

  void publish_method();

private:
  size_t count_;

  // Variable que es un puntero a una clase que es la encargada de publicar.
  // Variable de tipo publisher
  // Puntero a un tipo string de una clase publisher (LOL xD)
  // Como es un puntero hay que inicializarlo

  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
};
