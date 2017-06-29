#include "include/Humanoid.h"
#include <iostream>

int main (int argc, char** argv){
    Humanoid* humanoid;
    humanoid = new Humanoid();

    std::cin.ignore();
    humanoid->WalkForward();
    std::cin.ignore();
    humanoid->Stop();

    //runDetectNet(argc, argv);

    std::cout << "exiting.." << std::endl;
    return 0;
}
