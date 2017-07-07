#include "include/Humanoid.h"
#include <iostream>
#include <math.h>
#include <algorithm>
#include <functional>
#include <array>
#include <vector>

float hypotenuse(float x1, float y1, float x2, float y2) {
    return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}


int main (int argc, char** argv){
    Humanoid* humanoid = new Humanoid(argc, argv);
    
   // humanoid->serialHandler->OpenZigbPort();
   // humanoid->Stop();
   // humanoid->WalkForward();
    
   // humanoid->behaviorController->ChangeState(humanoid->behaviorController->ControllerState::WALK_FORWARD);
    /*        
    float** bbArray;
    std::vector<float*> bbArraySorted;
    volatile int numBB;
    char ch;

    while(!humanoid->detectnetController->IsCameraLoaded()) {

    }

    float camCenterX = (float)(humanoid->detectnetController->GetCamWidth()) / 2.0;
    float camCenterY = (float)(humanoid->detectnetController->GetCamHeight()) / 2.0;

    std::cin.ignore();
    std::cout << "CAM_CENTER_X" << camCenterX << std::endl;
    std::cout << "CAM_CENTER_Y" << camCenterY << std::endl;

    /*struct {
        
        bool operator()(float* a, float* b) const {
        }
    } customLess;
      */   
    /*
    int c; 
    while((c = getchar()) != 27){
        bbArraySorted.clear();
        bbArray = humanoid->detectnetController->GetBBArray();
        numBB = *humanoid->detectnetController->GetNumBB();
        //bbArraySorted = bbArray;
        //std::array<float*, numBB> bbArraySorted = bbArray;
        printf("numBB %i\n:", numBB);
        for(int i=0; i< numBB; i++){
            float* bb = bbArray[i];
            bbArraySorted.push_back(bb);
            printf("BB %i: %f, %f, %f, %f\n", i, bb[0], bb[1], bb[2], bb[3]);
        }

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
            float cX = humanoid->detectnetController->GetCenterX(a);
            float cY = humanoid->detectnetController->GetCenterY(a);

            float hyp = hypotenuse(cX, cY, camCenterX, camCenterY);

            std::cout << hyp << " ";
        }
        std::cout << "\n";

        //std::cin.ignore();
    }*/
     

//    humanoid->detectnetController->JoinDetect();
    std::cout << "exiting.." << std::endl;

    return 0;
}
