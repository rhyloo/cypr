#include <first_pkg/keyController.hpp>

keyController::keyController() : Node ("keyController"){
  count_=0;

  publisher_=this->create_publisher<std_msgs::msg::String>("/cmd_key",10);
}

keyController::~keyController()
{
  printf("Leaving gently\n");
}


void keyController::publish_method(){
  auto message= std_msgs::msg::String();
  RCLCPP_INFO(this->get_logger(), "Use arrow keys to move the robot.");
  RCLCPP_INFO(this->get_logger(), "Press the space bar to stop the robot.");
  RCLCPP_INFO(this->get_logger(), "Press q to stop the program.");

  system("stty raw -echo");

  // Loop until "q" is pressed
  bool salir=false;
  while (rclcpp::ok() && !salir){
    char input = getchar();
    if(input != 27 && input != 91){
      switch (input){
      case 0x41:
        // RCLCPP_INFO(this->get_logger(), "[KeyController] Detected Up key\r");
        message.data = "fordwards";
        break;
      case 0x42:
        // RCLCPP_INFO(this->get_logger(), "[KeyController] Detected Down key\r");
        message.data = "backwards";
        break;
      case 0x43:
        // RCLCPP_INFO(this->get_logger(), "[KeyController] Detected Right key\r");
        message.data = "right";
        break;
      case 0x44:
        // RCLCPP_INFO(this->get_logger(), "[KeyController] Detected Left key\r");
        message.data = "left";
        break;
      case 0x20:
        // RCLCPP_INFO(this->get_logger(), "[KeyController] Detected Space key\r");
        message.data = "stop";
        break;
      case 'q':
        // RCLCPP_INFO(this->get_logger(), "[KeyController] Detected q = Exit\r");
        salir=true;
        //restore the console
        system("stty cooked echo");
      }
      count_++;
      RCLCPP_INFO(this->get_logger(),"[#%ld] Publishing: '%s'\r",count_,message.data.c_str());
      publisher_->publish(message);
    }
  }
}

int main(int argc, char **argv)
{
  // Incializar ROS
  rclcpp::init (argc,argv);


  // Instancia de la clase
  keyController p;

  // Clase que controla el tiempo, la inicializa a 1 Hz
  p.publish_method();
  rclcpp::shutdown();
  return 0;
}
