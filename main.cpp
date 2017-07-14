#include "include/Humanoid.h"
#include "include/BehaviorController.h"
#include "include/Arm.h"
#include <iostream>
#include <signal.h>
#include <thread>

int main (int argc, char** argv){
    Humanoid* humanoid = new Humanoid(argc, argv);
    int inputChar; 
       
    //Send STOP command to init zigbeecontroller
    humanoid->behaviorController->ChangeState(BehaviorController::ControllerState::STOP);
    
    humanoid->arm->SetPose(Arm::ArmPose::DEFAULT);
    //do nothing until detectNet is ready
    while(!humanoid->detectnetController->IsDetectNetReady()) {
    }


    humanoid->detectnetController->ReadCameraResolution();

    //Define acceptable distance tolerance where robot will no longer react and try to turn
    int xReactionTolerance = 0.10 * humanoid->detectnetController->GetCameraWidth();
    int areaTolerance = 0.50 * humanoid->detectnetController->GetCameraWidth() * humanoid->detectnetController->GetCameraHeight();


    bool bendDown = false;
    //while((inputChar = getchar()) != 27){
    while(!humanoid->detectnetController->ReadStopSignal()){
        humanoid->detectnetController->SortBBArrayByTargetDistance();
        printf("Orientation: %i\n", humanoid->detectnetController->GetCupOrientation());
        
        float xError = humanoid->detectnetController->GetErrorXOfTargetBB();
        float bbArea = humanoid->detectnetController->GetAreaOfTargetBB(); 

        printf("AREA: %f\n", bbArea);
        if(xError == NULL || bbArea == -1) {
            if(bendDown){
                humanoid->behaviorController->ChangeState(BehaviorController::ControllerState::WALK_FORWARD);
                humanoid->behaviorController->ChangeState(BehaviorController::ControllerState::STOP);
                humanoid->behaviorController->ChangeState(BehaviorController::ControllerState::STRAFE_LEFT);
                printf("XERROR DNE | BEND DOWN\n"); 
                sleep(1);
                humanoid->arm->SetPose(Arm::ArmPose::READY);
                sleep(1);
                humanoid->arm->SetPose(Arm::ArmPose::GRABBING);
                sleep(1);
                humanoid->arm->SetPose(Arm::ArmPose::GRAB);
                break;
            }
            else {
               printf("XERROR DNE | STOP\n"); 
               humanoid->behaviorController->ChangeState(BehaviorController::ControllerState::STOP);
            }
        } else if(xError >= xReactionTolerance) {
            printf("YERROR: %f | TURNING RIGHT\n", xError);
            humanoid->behaviorController->ChangeState(BehaviorController::ControllerState::STRAFE_RIGHT);
        } else if(xError <= (xReactionTolerance)*-1) {
            printf("XERROR: %f | TURNING LEFT\n", xError);
            humanoid->behaviorController->ChangeState(BehaviorController::ControllerState::STRAFE_LEFT);
        } else if(bbArea <= areaTolerance){
            printf("ERROR: %f | WALKING FORWARD\n", bbArea);
            humanoid->behaviorController->ChangeState(BehaviorController::ControllerState::WALK_FORWARD);
            humanoid->behaviorController->ChangeState(BehaviorController::ControllerState::STOP);
        } else {
            printf("ERROR: %f | STOP DUE TO LARGE AREA\n", xError);
            humanoid->behaviorController->ChangeState(BehaviorController::ControllerState::STOP);
        } 

        if(humanoid->detectnetController->bbArraySorted.size() < 1){
            bendDown = false; 
            printf("SETTING FALSE");
        }
        else if( humanoid->detectnetController->GetCenterYFromBB(humanoid->detectnetController->bbArraySorted[0]) > ((2.0/3.0) * humanoid->detectnetController->GetCameraHeight()) ){
            bendDown = true; 
            printf("SETTING TRUE");
            printf("CENTER Y of BB: %f\n", humanoid->detectnetController->GetCenterYFromBB(humanoid->detectnetController->bbArraySorted[0]) );
            printf("image threshold: %f\n", ((2.0/3.0) * humanoid->detectnetController->GetCameraHeight()) );
        }
        else {
        }

        sleep(1);
    }

    humanoid->detectnetController->JoinDetectThread();
    printf("Exiting..");

    return 0;
}
