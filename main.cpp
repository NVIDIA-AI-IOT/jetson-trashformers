#include "include/Humanoid.h"
#include "include/BehaviorController.h"
#include "include/Arm.h"
#include <iostream>
#include <thread>

#define DEFAULT_CAMERA_PORT 0
std::string DEFAULT_MODEL ("84");

int main (int argc, char** argv){
//args: int camPort, char* modelNum
    int camPort;
    std::string modelNum;
    
    //Parse arguments
    switch(argc){
        default: 
            camPort = DEFAULT_CAMERA_PORT;
            modelNum = DEFAULT_MODEL;
            break;
        case 2: 
            camPort = atoi(argv[1]);
            modelNum = DEFAULT_MODEL;
            break;
        case 3: 
            camPort = atoi(argv[1]);
            modelNum.assign(argv[2]);
            break;
    }
    
    Humanoid* humanoid = new Humanoid(camPort, modelNum);

    //Send STOP command to init zigbeecontroller
    humanoid->behaviorController->ChangeState(BehaviorController::ControllerState::STOP);
    
    humanoid->arm->SetPose(Arm::ArmPose::DEFAULT);
    //do nothing until detectNet is ready
    while(!humanoid->detectnetController->IsDetectNetReady()) {
        if(humanoid->detectnetController->ReadStopSignal()){
            return 1; //CTRL ^C has been pressed
        }
    }


    humanoid->detectnetController->ReadCameraResolution();

    //Define acceptable distance tolerance where robot will no longer react and try to turn
    int xReactionTolerance = 0.10 * humanoid->detectnetController->GetCameraWidth();
    int areaTolerance = 2.00 * humanoid->detectnetController->GetCameraWidth() * humanoid->detectnetController->GetCameraHeight();

    while(!humanoid->detectnetController->ReadStopSignal()){
        humanoid->UpdateState(xReactionTolerance, areaTolerance);
    }

    humanoid->detectnetController->JoinDetectThread();
    printf("Exiting..");

    return 0;
}
