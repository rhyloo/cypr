#include <first_pkg/squareController.hpp>
#include <math.h>

squareController::squareController() : Node ("squarecontroller"){
  this->declare_parameter<int>("lado",5);
  count_=0;
  publisher_=this->create_publisher<std_msgs::msg::String>("/cmd_square",10);
}

squareController::~squareController(){
  printf("Leaving gently\n");
}

void squareController::publish_method(){
  //
  int side;
  int lado;
  this->get_parameter("lado",lado);

  side = lado;
  // 
  
  auto message= std_msgs::msg::String();
  
  RCLCPP_INFO(this->get_logger(), "SquareController activo!");

  // Calcula el tiempo que tardará el robot en recorrer un lado del cuadrado
  double time = side / 1;

  rclcpp::Rate loop_rate(1/time);
  // Itera sobre los cuatro lados del cuadrado
  for (int i = 0; i < 9; i++)
    {
      // Si el índice del bucle es par, entonces el robot debe avanzar
      if(i == 8){
        message.data = "stop";
      }else if (i % 2 == 0){
        message.data = "avanzar";
      }else{    // Si el índice del bucle es impar, entonces el robot debe girar
        message.data = "girar";
      }
      // Espera el tiempo calculado
      publisher_->publish(message);
      loop_rate.sleep();
    }
}

int main(int argc, char **argv)
{
  // rclcpp::Rate loop_rate(1);
  // Incializar ROS
  rclcpp::init (argc,argv);

  // Instancia de la clase
  squareController p;
  // while(rclcpp::ok())
  //   {
      // Clase que controla el tiempo, la inicializa a 1 Hz
      p.publish_method();
    //   loop_rate.sleep();
    // }
  rclcpp::shutdown();
  return 0;
}
