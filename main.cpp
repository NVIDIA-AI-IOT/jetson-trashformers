#include "include/Humanoid.h"
#include <iostream>
#include <signal.h>
#include <math.h>
#include <algorithm>
#include <functional>
#include <array>

sig_atomic_t signaled = 0;

void handler(int signum) {
    signaled = 1;
}

float hypotenuse(float x1, float y1, float x2, float y2) {
    return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}


int main (int argc, char** argv){
    Humanoid* humanoid = new Humanoid(argc, argv);
    
    signal(SIGINT, handler);
    float** bbArray;
    volatile int numBB;
    std::cin.ignore();
    char ch;

    float camCenterX;
    float camCenterY;

    /*struct {
        
        bool operator()(float* a, float* b) const {
        }
    } customLess;
      */   
 
    while((ch = std::cin.get()) != 27){
        bbArray = humanoid->detectnetController->GetBBArray();
        numBB = *humanoid->detectnetController->GetNumBB();
        std::array<float*, numBB> bbArraySorted = bbArray;
        printf("numBB %i\n:", numBB);
        /*for(int i=0; i< numBB; i++){
            float* bb = bbArray[i];
            printf("BB %i: %f, %f, %f, %f\n", i, bb[0], bb[1], bb[2], bb[3]);
        }*/

        std::sort(bbArraySorted.begin(), bbArraySorted.end(), [humanoid, camCenterX, camCenterY](float* a, float* b) {
            float centerX1 = humanoid->detectnetController->GetCenterX(a);
            float centerX2 = humanoid->detectnetController->GetCenterX(b);
            
            float centerY1 = humanoid->detectnetController->GetCenterY(a);
            float centerY2 = humanoid->detectnetController->GetCenterY(b);

            float hyp1 = hypotenuse(centerX1, centerY1, camCenterX, camCenterY);
            float hyp2 = hypotenuse(centerX2, centerY2, camCenterX, camCenterY);
            
            return hyp1 < hyp2;
        });
        for(auto a : bbArraySorted) {
            std::cout << a << " ";
        }
        std::cout << "\n";

        //std::cin.ignore();
    }
   

    humanoid->detectnetController->JoinDetect();
    std::cout << "exiting.." << std::endl;

    return 0;
}
