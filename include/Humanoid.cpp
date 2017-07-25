#include "Humanoid.h"

#define DEFAULT_ZIGBEE_DEVICEINDEX 0

Humanoid::Humanoid(int camPort, std::string model) { //CONSTRUCTOR

    serialHandler = new SerialHandler();
    zigb = serialHandler->GetZigbController();
    behaviorController = new BehaviorController(serialHandler);    
    arm = new Arm(serialHandler);
    detectnetController = new DetectNetController(camPort, model);
    keyboardController = new KeyboardController(zigb);
}

Humanoid::~Humanoid() {

}

void Humanoid::UseKeyboard(){
    keyboardController->Init();
    keyboardController->RunInput();
}
        
void Humanoid::UpdateState(int xReactionTolerance, int areaTolerance) {
    
    detectnetController->SetDetectNetLoopLock(true);
    while(detectnetController->GetDetectNetLoopLock()){}
    
    detectnetController->SortBBArrayByTargetDistance();
    float xError = detectnetController->GetErrorXOfTargetBB();
    float bbArea = detectnetController->GetAreaOfTargetBB(); 

    if(bbArea == -1) {
        if(grab){
            behaviorController->ChangeState(BehaviorController::ControllerState::WALK_FORWARD);
            behaviorController->ChangeState(BehaviorController::ControllerState::STOP);
            behaviorController->ChangeState(BehaviorController::ControllerState::STRAFE_LEFT);
            printf("BEND DOWN\n"); 
            sleep(1);
            GrabVerticalCup();
            behaviorController->ChangeState(BehaviorController::ControllerState::STOP);
            grab = false; 
        }
        else {
           printf("STOP\n"); 
           behaviorController->ChangeState(BehaviorController::ControllerState::STOP);
        }
    } else if(xError >= xReactionTolerance) {
        printf("TURNING RIGHT\n");
        behaviorController->ChangeState(BehaviorController::ControllerState::STRAFE_RIGHT);
    } else if(xError <= (xReactionTolerance)*-1) {
        printf("TURNING LEFT\n");
        behaviorController->ChangeState(BehaviorController::ControllerState::STRAFE_LEFT);
    } else if(bbArea <= areaTolerance){
        printf("WALKING FORWARD\n");
        behaviorController->ChangeState(BehaviorController::ControllerState::WALK_FORWARD);
        behaviorController->ChangeState(BehaviorController::ControllerState::STOP);
    } else {
        printf("STOP DUE TO LARGE AREA\n");
        behaviorController->ChangeState(BehaviorController::ControllerState::STOP);
    } 

    if(detectnetController->bbArraySorted.size() < 1){
        grab = false; 
        printf("GRAB: NO CUP\n");
    }
    else if( detectnetController->GetCenterYFromBB(detectnetController->bbArraySorted[0]) > ((2.0/3.0) * detectnetController->GetCameraHeight()) ){
        grab = true; 
        printf("GRAB: TRUE\n");
        printf("CENTER Y of BB: %f\n", detectnetController->GetCenterYFromBB(detectnetController->bbArraySorted[0]) );
        printf("image threshold: %f\n", ((2.0/3.0) * detectnetController->GetCameraHeight()) );
    }
    else {
        grab = false; 
        printf("GRAB: TOO HIGH\n");
        printf("CENTER Y of BB: %f\n", detectnetController->GetCenterYFromBB(detectnetController->bbArraySorted[0]) );
        printf("image threshold: %f\n", ((2.0/3.0) * detectnetController->GetCameraHeight()) );
        printf("CENTER X of BB: %f\n", detectnetController->GetCenterXFromBB(detectnetController->bbArraySorted[0]) );
        std::cout << (detectnetController->bbArraySorted[0])[0] << std::endl;
    }
    sleep(1);

}

void Humanoid::GrabVerticalCup() { 
    arm->SetPose(Arm::ArmPose::READY);
    sleep(1);
    arm->SetPose(Arm::ArmPose::GRABBING);
    sleep(1);
    arm->SetPose(Arm::ArmPose::GRAB);
    sleep(2);
    arm->SetPose(Arm::ArmPose::DEFAULT);
}
