#include "include/Humanoid.h"
#include "include/BehaviorController.h"
#include <iostream>

int main (int argc, char** argv){
    Humanoid* humanoid = new Humanoid(argc, argv);
    int inputChar; 
       
    //Send STOP command to init zigbeecontroller
    humanoid->behaviorController->ChangeState(BehaviorController::ControllerState::STOP);

    //do nothing until detectNet is ready
    while(!humanoid->detectnetController->IsDetectNetReady()) {
    }

    humanoid->detectnetController->ReadCameraResolution();

    //Define acceptable distance tolerance where robot will no longer react and try to turn
    int reactionTolerance = 0.10 * humanoid->detectnetController->GetCameraWidth();

    printf("TOLERANCE %i\n", reactionTolerance);
    while((inputChar = getchar()) != 27){
        float xError = humanoid->detectnetController->GetErrorXOfTargetBB();
        if(xError == NULL) {
            printf("ERROR DNE\n"); 
            humanoid->behaviorController->ChangeState(BehaviorController::ControllerState::STOP);
        } else if(xError >= reactionTolerance) {
            printf("ERROR: %f | TURNING RIGHT\n", xError);
            humanoid->behaviorController->ChangeState(BehaviorController::ControllerState::STRAFE_RIGHT);
        } else if(xError <= (reactionTolerance)*-1) {
            printf("ERROR: %f | TURNING LEFT\n", xError);
            humanoid->behaviorController->ChangeState(BehaviorController::ControllerState::STRAFE_LEFT);
        } else {
            printf("ERROR: %f | STOPPING\n", xError);
            humanoid->behaviorController->ChangeState(BehaviorController::ControllerState::STOP);
        }
    }

    //
    //humanoid->detectnetController->JoinDetectThread();
    printf("Exiting..");

    return 0;
}
