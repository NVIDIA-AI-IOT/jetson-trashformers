#include "include/Humanoid.h"
#include <iostream>

int main (int argc, char** argv){
    Humanoid* humanoid;
    humanoid = new Humanoid();
    
    //Control Humanoid with keyboard
    humanoid->UseKeyboard();
    
    std::cout << "exiting.." << std::endl;
    return 0;
}
