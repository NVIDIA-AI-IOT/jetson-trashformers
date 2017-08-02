#include "include/Humanoid.h"
#include "include/BehaviorController.h"
#include "include/Arm.h"
#include <iostream>
#include <thread>

#define DEFAULT_BOTTOM_CAMERA_PORT 1
#define DEFAULT_TOP_CAMERA_PORT 0
std::string DEFAULT_MODEL ("84");

int main (int argc, char** argv){
//args: int camPort, char* modelNum
    int bottomCamPort = DEFAULT_BOTTOM_CAMERA_PORT;
    int topCamPort    = DEFAULT_TOP_CAMERA_PORT;
    std::string modelNum;
    
    //Parse arguments
    switch(argc){
        default: 
            bottomCamPort = DEFAULT_BOTTOM_CAMERA_PORT;
            modelNum = DEFAULT_MODEL;
            break;
        case 2: 
            bottomCamPort = atoi(argv[1]);
            modelNum = DEFAULT_MODEL;
            break;
        case 3: 
            bottomCamPort = atoi(argv[1]);
            modelNum.assign(argv[2]);
            break;
    }
    
    //Init Humanoid
    Humanoid* humanoid = new Humanoid(bottomCamPort, topCamPort, modelNum);

    //Send STOP command to init zigbeecontroller
    humanoid->behaviorController->ChangeState(BehaviorController::ControllerState::STOP);
    
    //Set arm to default pose
    humanoid->arm->SetPose(Arm::ArmPose::DEFAULT);

    //do nothing until detectNet is ready
    while(!humanoid->detectnetController->IsDetectNetReady()) {
        if(humanoid->detectnetController->ReadStopSignal()){
            return 1; //CTRL ^C has been pressed
        }
    }

    //Read camera information from detectNet
    humanoid->detectnetController->ReadCameraResolution();

    //While CTRL^C has not been pressed, run main humanoid loop
    while(!humanoid->detectnetController->ReadStopSignal()){
        humanoid->UpdateState();
    }

    //Merge threads and exit
    humanoid->detectnetController->JoinDetectThread();
    printf("Exiting..");

    return 0;
}
