#include "include/Humanoid.h"
#include <iostream>

int main (int argc, char** argv){
    Humanoid* humanoid = new Humanoid(argc, argv);

    int c; 
       
    humanoid->behaviorController->ChangeState(humanoid->behaviorController->ControllerState::STOP);
    //while camera is not loaded, do nothing
    while(!humanoid->detectnetController->IsCameraLoaded()) {

    }

    humanoid->detectnetController->Init();

    int tolerance = 0.05 * humanoid->detectnetController->GetCamWidth();
    printf("TOLERANCE %i\n", tolerance);
    while((c = getchar()) != 27){
        //humanoid->detectnetController->GetTargetBB();
        float xError = humanoid->detectnetController->GetErrorX();
        if(xError == NULL) {
            printf("ERROR DNE\n"); 
            humanoid->behaviorController->ChangeState(humanoid->behaviorController->ControllerState::STOP);
        } else if(xError >= tolerance) {
            printf("ERROR: %f | TURNING RIGHT\n", xError);
            humanoid->behaviorController->ChangeState(humanoid->behaviorController->ControllerState::STRAFE_RIGHT);
        } else if(xError <= (tolerance)*-1) {
            printf("ERROR: %f | TURNING LEFT\n", xError);
            humanoid->behaviorController->ChangeState(humanoid->behaviorController->ControllerState::STRAFE_LEFT);
        } else {
            printf("ERROR: %f | STOPPING\n", xError);
            humanoid->behaviorController->ChangeState(humanoid->behaviorController->ControllerState::STOP);
        }
    }

    //humanoid->detectnetController->JoinDetectThread();
    std::cout << "exiting.." << std::endl;

    return 0;
}
