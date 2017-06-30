#include "include/Humanoid.h"
#include <iostream>

int main (int argc, char** argv){
    Humanoid* humanoid;
    humanoid = new Humanoid(argc, argv);
    
    //Control Humanoid with keyboard
    //humanoid->UseKeyboard();

    std::cout << std::endl << std::endl;

    //Move a servo    
    int input;
    std::cout << "Enter a setpoint for the servo (0 - 1023):" << std::endl;
    std::cin >> input;
    humanoid->motor_1->SetSetpoint(input);
    
    std::cout << "exiting.." << std::endl;
    return 0;
}
