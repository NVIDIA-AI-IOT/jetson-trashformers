#include "Humanoid.h"

#define DEFAULT_ZIGBEE_DEVICEINDEX 0

Humanoid::Humanoid(int bottomCamPort, int topCamPort, std::string model) { //CONSTRUCTOR

    serialHandler = new SerialHandler();
    zigb = serialHandler->GetZigbController();
    behaviorController = new BehaviorController(serialHandler);    
    arm = new Arm(serialHandler);
    detectnetController = new DetectNetController(bottomCamPort, topCamPort, model);
    keyboardController = new KeyboardController(zigb);
}

Humanoid::~Humanoid() {

}

void Humanoid::UseKeyboard(){
    keyboardController->Init();
    keyboardController->RunInput();
}


void Humanoid::UpdateState() {
    
    if(shouldSwitchCams){
        detectnetController->SwitchCameras();
        sleep(2);
    }
    
    //Tell detectNet to read one image
    detectnetController->SetDetectNetLoopLock(true);
    while(detectnetController->GetDetectNetLoopLock()){}
    //SortArray
    detectnetController->SortBBArrayByTargetDistance();

    areaTolerance = 0.6 * detectnetController->GetCameraWidth() * detectnetController->GetCameraHeight();
    switch(humanoidState) {
        default:
        case Humanoid::HumanoidState::SEARCHING:
            printf("STATE: SEARCHING\n");
            if(Searching()) {
                humanoidState = HumanoidState::POSITIONING;
            }
            break;
        case Humanoid::HumanoidState::POSITIONING:
            printf("STATE: POSITIONING\n");
           /* if(!detectnetController->IsCurrentCamBottomCam() && lowFrame) {
                lowFrame = false;
                detectnetController->SwitchCameras();
                printf("SWITCHING TO BOTTOM BC OF LOWFRAME IN SWITCH\n");
                //humanoidState = HumanoidState::SEARCHING;
            }*/
            if(!(detectnetController->IsCurrentCamBottomCam())){
                Position();
                break;
            }            

            if(targetClassID == DetectNetController::ClassID::CUP){
                Position((1.0/4.0) * detectnetController->GetCameraWidth());
            } else if(targetClassID == DetectNetController::ClassID::TRASHCAN){
                Position();
            }
            break;
        case Humanoid::HumanoidState::GRABBING:
            printf("STATE: GRABBING\n");
            Grab();
            break;
        case Humanoid::HumanoidState::RELEASING:
            printf("STATE: RELEASING\n");
            ReleaseCup();
            break;
    }
        printf("LOW FRAME: %i\n", lowFrame);
}

void Humanoid::Grab() {
    behaviorController->ChangeState(BehaviorController::ControllerState::DIAGONAL_LEFT);
    behaviorController->ChangeState(BehaviorController::ControllerState::STOP);
    behaviorController->ChangeState(BehaviorController::ControllerState::STRAFE_LEFT);
    printf("BEND DOWN\n"); 
    sleep(1);
    GrabVerticalCup();
    behaviorController->ChangeState(BehaviorController::ControllerState::STOP);
    humanoidState = Humanoid::HumanoidState::SEARCHING;
    targetClassID = DetectNetController::ClassID::TRASHCAN;
}

void Humanoid::GrabVerticalCup() { 
    arm->SetPose(Arm::ArmPose::READY);
    sleep(1);
    arm->SetPose(Arm::ArmPose::GRABBING);
    sleep(1);
    arm->SetPose(Arm::ArmPose::GRAB);
    sleep(2);
    arm->SetPose(Arm::ArmPose::STORE);
}

void Humanoid::ReleaseCup() {
    arm->SetPose(Arm::ArmPose::RELEASE);
    sleep(1);
    arm->SetPose(Arm::ArmPose::DEFAULT);
    sleep(1);
    
    for(int i=0; i < 4; i++) {
        Turn(1);
    }

    humanoidState = Humanoid::HumanoidState::SEARCHING;
    targetClassID = DetectNetController::ClassID::CUP;
}

void Humanoid::Position(){
    Position(0.0);
}

void Humanoid::Position(float xOffset){
    float xReactionTolerance = 0.10 * detectnetController->GetCameraWidth(); 
    float xError = detectnetController->GetErrorXOfTargetBB(xOffset);
    float bbArea = detectnetController->GetAreaOfTargetBB(targetClassID);
    printf("BBAREA: %f", bbArea);
    printf("AREA TOLERANCE: %f", areaTolerance);

    if(detectnetController->ConvertIntToClassID(detectnetController->GetTargetBB(targetClassID)[4]) == DetectNetController::ClassID::UNKNOWN){ //NO BB IS FOUND
       /* if(detectnetController->IsCurrentCamBottomCam() && lowFrame && targetClassID == DetectNetController::ClassID::TRASHCAN) { //class ID of trashcan
            humanoidState = HumanoidState::RELEASING;
            lowFrame = false;
        } else*/ if(detectnetController->IsCurrentCamBottomCam() && lowFrame && (targetClassID == DetectNetController::ClassID::CUP)) {
            humanoidState = HumanoidState::GRABBING;
            lowFrame = false;
        } else if(!detectnetController->IsCurrentCamBottomCam() && lowFrame && (targetClassID == DetectNetController::ClassID::CUP)){
            lowFrame = false;
            printf("LOW FRAME TRIGGERED IN TOP CAM\n");
            behaviorController->ChangeState(BehaviorController::ControllerState::DIAGONAL_LEFT);
            behaviorController->ChangeState(BehaviorController::ControllerState::STOP);
            printf("WALKING FORWARD BECUASE LOW FRAME IN TOP CAM\n");
            sleep(1);
            humanoidState = HumanoidState::SEARCHING;
            return;
        } else if(!detectnetController->IsCurrentCamBottomCam() && lowFrame && (targetClassID == DetectNetController::ClassID::TRASHCAN)){
            printf("TOP CAM LOW FRAME TRIGGERED -- RELEASING\n");
            humanoidState = HumanoidState::RELEASING;
            lowFrame = false;
        }
        else {
            humanoidState = HumanoidState::SEARCHING;
            lowFrame = false;
        }
    } else if(xError >= xReactionTolerance) {
        printf("TURNING RIGHT\n");
        behaviorController->ChangeState(BehaviorController::ControllerState::STRAFE_RIGHT);
    } else if(xError <= (xReactionTolerance)*-1.0){
        printf("TURNING LEFT\n");
        behaviorController->ChangeState(BehaviorController::ControllerState::STRAFE_LEFT);
        if(!detectnetController->IsCurrentCamBottomCam()){
            sleep(1);
            behaviorController->ChangeState(BehaviorController::ControllerState::DIAGONAL_DORSAL_LEFT);
            behaviorController->ChangeState(BehaviorController::ControllerState::STOP);
        }
    } else if(bbArea > areaTolerance){
        printf("RELEASE DUE TO LARGE AREA\n");
        behaviorController->ChangeState(BehaviorController::ControllerState::STOP);
        humanoidState = HumanoidState::RELEASING;
    } else {
        printf("WALKING FORWARD\n");
        behaviorController->ChangeState(BehaviorController::ControllerState::DIAGONAL_LEFT);
        behaviorController->ChangeState(BehaviorController::ControllerState::STOP);
    }

    if(detectnetController->ConvertIntToClassID(detectnetController->GetTargetBB(targetClassID)[4]) == DetectNetController::ClassID::UNKNOWN){
        //Don't change variables
    } else if( detectnetController->GetCenterYFromBB(detectnetController->GetTargetBB(targetClassID)) > ((2.0/3.0) * detectnetController->GetCameraHeight()) ){
        printf("CLASS ID: %i\n", (int)targetClassID);
        lowFrame = true;
    }
    else {
        lowFrame = false; 
    }
    
    sleep(2);
}

void Humanoid::Turn(int sleepTime){
    behaviorController->ChangeState(BehaviorController::ControllerState::DIAGONAL_FRONTAL_LEFT);
    behaviorController->ChangeState(BehaviorController::ControllerState::STOP);
    sleep(sleepTime);
    behaviorController->ChangeState(BehaviorController::ControllerState::DIAGONAL_DORSAL_RIGHT);
    behaviorController->ChangeState(BehaviorController::ControllerState::STOP);
    sleep(sleepTime);
}
        
bool Humanoid::Searching() {

    printf("SHOULDSWITCHCAMS: %i\n", shouldSwitchCams);
    printf("IS BOTTOM CAMERA: %i\n", detectnetController->IsCurrentCamBottomCam());
    if(shouldSwitchCams && !detectnetController->IsCurrentCamBottomCam()){
        printf("TURNING!\n"); 
        Turn(1);
    }
    shouldSwitchCams = false;

    bool found;
    if(detectnetController->ConvertIntToClassID(detectnetController->GetTargetBB(targetClassID)[4]) == DetectNetController::ClassID::UNKNOWN){
       found = false;
       shouldSwitchCams = true;
    } else {
       found = true;
       shouldSwitchCams = false;
    }

    printf("CAM X: %f\n", detectnetController->GetCenterXFromBB(detectnetController->GetTargetBB(targetClassID)));
    printf("CAM Y: %f\n", detectnetController->GetCenterYFromBB(detectnetController->GetTargetBB(targetClassID)));
    //printf("IS BOTTOM CAMERA: %i\n", detectnetController->IsCurrentCamBottomCam());

    return found;
}
