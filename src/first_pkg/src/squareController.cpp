#include <first_pkg/squareController.hpp>

const int lado = 5;

squareController::squareController() : Node ("squarecontroller"){
  count_=0;
  publisher_=this->create_publisher<std_msgs::msg::String>("/cmd_square",10);
}

squareController::~squareController(){
  printf("Leaving gently\n");
}

void squareController::publish_method(){
  
  rclcpp::Rate loop_rate(1);
  auto message= std_msgs::msg::String();
  
  RCLCPP_INFO(this->get_logger(), "SquareController activo!");
    
  for (int i = 1; i <= 44; i++){
    if (i != 11 && i != 22 && i != 33 && i != 44){
      message.data = "avanzar";
    }else{
      message.data = "girar";
    }
      
    // Publicar el mensaje
    publisher_->publish(message);
    
    // Esperar un tiempo para dar tiempo a que el robot procese el comando
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
