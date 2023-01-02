#include <first_pkg/squareController.hpp>
#define ratio 10
squareController::squareController() : Node ("squarecontroller"){
  count_=0;
  publisher_=this->create_publisher<std_msgs::msg::String>("/cmd_square",10);
}

squareController::~squareController(){
  printf("Leaving gently\n");
}

void squareController::publish_method(){
  auto message= std_msgs::msg::String();
  int figura = 4;                  // Lados de la figura
  int lado = 10;                   // Longitud del lado de la figura

  for(int j = 0; j<4; j++)
    {
      for(int i = 0; i<lado; i++)
        {
          if (mod(i,ratio) == 0)
            {
              message.data = "girar";
            }
          else
            {
              message.data = "avanzar";
            }
        }
    }

int main(int argc, char **argv)
{
  // Incializar ROS
  rclcpp::init (argc,argv);


  // Instancia de la clase
  squareController p;

  // Clase que controla el tiempo, la inicializa a 1 Hz
  rclcpp::Rate loop_rate(1);


  while(rclcpp::ok())
    {
      p.publish_method();

      // Duerme la hebra para intentar asegurar la frecuencia de 1 Hz, si tarda menos se queda dormido hasta el 1 Hz si tarda más ah se siente
      loop_rate.sleep();
    }
  rclcpp::shutdown();
  return 0;
}
