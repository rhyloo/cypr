#include <first_pkg/keyController.hpp>

// Definimos el constructor
// Con herencia, se llama a la clase de la que hereda primero
// Node("controller") es el nombre de mi nodo

keyController::keyController() : Node ("keyController"){
  count_=0;

  // this: palabra reservada que es un puntero a la clase reservada, create_publisher es una funcion de la clase Node
  // El primer parametro es el nombre del topic
  // El segundo parametro es el número de mensajes que se pueden encolar

  publisher_=this->create_publisher<std_msgs::msg::String>("/cmd_key",10);
}

// Este destructor es el que llama al destructor de Node
keyController::~keyController()
{
  printf("Leaving gently\n");
}

// Se encarga de publicar
void keyController::publish_method(){
  // Standart de la ultimas las versiones de C++, auto= std_msgs::msg::String(), simplifica el codigo
  // Ros incluye muchas cosas stdio.h, por ejemplo
  auto message= std_msgs::msg::String();
  int random=round(4*(float)rand()/(float)RAND_MAX);
  count_++;
  switch (random)
    {
    case 0:
      message.data = "stop";
      break;
    case 1:
      message.data = "fordwards";
      break;
    case 2:
      message.data = "backwards";
      break;
    case 3:
      message.data = "left";
      break;
    case 4:
      message.data = "right";
      break;
      // default:

    }
  // Lo imprime por pantalla y lo guarda en logs, además puedo definir el nivel de información que quiero ver, warnings, critics
  RCLCPP_INFO(this->get_logger(),"[#%ld] Publishing: '%s'",count_,message.data.c_str());

  // Tengo el mensaje, ahora solo necesito enviarlo
  publisher_->publish(message);

}

int main(int argc, char **argv)
{
  // Incializar ROS
  rclcpp::init (argc,argv);


  // Instancia de la clase
  keyController p;

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
