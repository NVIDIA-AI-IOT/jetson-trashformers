#include "include/Humanoid.h"
#include <iostream>

int main (int argc, char** argv){
    Humanoid* humanoid = new Humanoid(argc, argv);
    
    std::cout << "exiting.." << std::endl;

    return 0;
}
