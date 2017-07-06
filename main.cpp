#include "include/Humanoid.h"
#include <iostream>
#include <signal.h>

sig_atomic_t signaled = 0;

void handler(int signum) {
    signaled = 1;
}


int main (int argc, char** argv){
    Humanoid* humanoid = new Humanoid(argc, argv);
    
    signal(SIGINT, handler);
    float** bbArray;
    volatile int numBB;
    std::cin.ignore(); 
     
    while(!signaled){
        bbArray = humanoid->detectnetController->GetBBArray();
        numBB = *humanoid->detectnetController->GetNumBB();
        printf("numBB %i\n:", numBB);
        for(int i=0; i< numBB; i++){
            float* bb = bbArray[i];
            printf("BB %i: %f, %f, %f, %f\n", i, bb[0], bb[1], bb[2], bb[3]);
        }
        std::cin.ignore();
    }
   

    humanoid->detectnetController->JoinDetect();
    std::cout << "exiting.." << std::endl;

    return 0;
}
