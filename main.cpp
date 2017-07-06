#include "include/Humanoid.h"
#include <iostream>

int main (int argc, char** argv){
    Humanoid* humanoid = new Humanoid(argc, argv);
    
    float** bbArray;
    volatile int numBB;
    int c; 
    while((c = getchar()) != 27){
        bbArray = humanoid->detectnetController->GetBBArray();
        numBB = *humanoid->detectnetController->GetNumBB();
        printf("numBB %i\n:", numBB);
        for(int i=0; i< numBB; i++){
            float* bb = bbArray[i];
            for(int j=0; j<4; j++) {
                printf("BB %i: %f, %f, %f, %f\n", i, bb[0], bb[1], bb[2], bb[3]);
            }
        }
    }
     

//    humanoid->detectnetController->JoinDetect();
    std::cout << "exiting.." << std::endl;

    return 0;
}
