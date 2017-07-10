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
    int xReactionTolerance = 0.10 * humanoid->detectnetController->GetCameraWidth();
    int areaTolerance = 0.20 * humanoid->detectnetController->GetCameraWidth() * humanoid->detectnetController->GetCameraHeight();

    printf("TOLERANCE %i\n", xReactionTolerance);
    while((inputChar = getchar()) != 27){
        humanoid->detectnetController->SortBBArrayByTargetDistance();

        float xError = humanoid->detectnetController->GetErrorXOfTargetBB();
        float bbArea = humanoid->detectnetController->GetAreaOfTargetBB(); 
        printf("AREA: %f\n", bbArea);
        if(xError == NULL || bbArea == -1) {
            printf("XERROR DNE\n"); 
            humanoid->behaviorController->ChangeState(BehaviorController::ControllerState::STOP);
        } else if(xError >= xReactionTolerance) {
            printf("YERROR: %f | TURNING RIGHT\n", xError);
            humanoid->behaviorController->ChangeState(BehaviorController::ControllerState::STRAFE_RIGHT);
        } else if(xError <= (xReactionTolerance)*-1) {
            printf("XERROR: %f | TURNING LEFT\n", xError);
            humanoid->behaviorController->ChangeState(BehaviorController::ControllerState::STRAFE_LEFT);
        } else if(bbArea <= areaTolerance){
            printf("ERROR: %f | WALKING FORWARD\n", bbArea);
            humanoid->behaviorController->ChangeState(BehaviorController::ControllerState::WALK_FORWARD);
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
