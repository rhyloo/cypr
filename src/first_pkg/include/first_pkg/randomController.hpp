#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

// Para crear un nodo de ROS mis clases deben heredar de la clase nodo
class randomController : public rclcpp::Node {
public:
  randomController(); // Mi constructor, se llama exactamente igual que la clase
  ~randomController(); // Destructor

  void publish_method();

  // Voy a contar cuantas veces publico
  // Es buena practica que las variables terminen en _ para identificar las variables privadas
private:
  size_t count_;

  // Variable que es un puntero a una clase que es la encargada de publicar.
  // Variable de tipo publisher
  // Puntero a un tipo string de una clase publisher (LOL xD)
  // Como es un puntero hay que inicializarlo

  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
};
