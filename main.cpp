#include "include/Humanoid.h"
#include <iostream>

int main (int argc, char** argv){
    Humanoid* humanoid;
    humanoid = new Humanoid(argc, argv);
    
//    humanoid->serialHandler->OpenZigbPort();
//    humanoid->Stop();
//    humanoid->WalkForward();
    //Control Humanoid with keyboard
//    humanoid->UseKeyboard();

    //std::cout << std::endl << std::endl;

    humanoid->serialHandler->OpenDynamixelPort();
    //humanoid->arm->SetDefaultPose();
    humanoid->arm->Set(802, 1002, 702, 612);    
//Move a servo    
    //int input;
  /*  while(true){
        std::cout << "Enter a setpoint for the servo (0 - 1023):" << std::endl;
        std::cin >> input;
        //humanoid->motor_1->SetSetpoint(100);
//        humanoid->arm->SetShoulder(input);
    }*/
    std::cout << "exiting.." << std::endl;

    return 0;
}
