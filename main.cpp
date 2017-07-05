#include "include/Humanoid.h"
#include <iostream>

int main (int argc, char** argv){
    Humanoid* humanoid;
    humanoid = new Humanoid(argc, argv);
    
    humanoid->serialHandler->OpenZigbPort();
    humanoid->Stop();
    humanoid->WalkForward();
    //Control Humanoid with keyboard
    //humanoid->UseKeyboard();

    //std::cout << std::endl << std::endl;

    //Move a servo    
    /*int input;
    std::cout << "Enter a setpoint for the servo (0 - 1023):" << std::endl;
    std::cin >> input;*/
    humanoid->serialHandler->OpenDynamixelPort();
    humanoid->motor_1->SetSetpoint(900);
    
    std::cout << "exiting.." << std::endl;
    return 0;
}
