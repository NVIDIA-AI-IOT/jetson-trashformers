#include "include/Humanoid.h"
#include <iostream>

int main (int argc, char** argv){
    Humanoid* humanoid = new Humanoid(argc, argv);
    int c; 
   
    //while camera is not loaded, do nothing
    while(!humanoid->detectnetController->IsCameraLoaded()) {

    }

    humanoid->detectnetController->Init();

    while((c = getchar()) != 27){
        humanoid->detectnetController->GetTargetBB();
    }
     

    //humanoid->detectnetController->JoinDetectThread();
    std::cout << "exiting.." << std::endl;

    return 0;
}
