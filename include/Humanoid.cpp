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


void Humanoid::UpdateState() {
    
    //Tell detectNet to read one image
    detectnetController->SetDetectNetLoopLock(true);
    while(detectnetController->GetDetectNetLoopLock()){}
    
    //SortArray
    detectnetController->SortBBArrayByTargetDistance();

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

    if(detectnetController->ConvertIntToClassID(detectnetController->GetTargetBB(targetClassID)[4]) == DetectNetController::ClassID::UNKNOWN){ //NO BB IS FOUND
        if(lowFrame && targetClassID == DetectNetController::ClassID::TRASHCAN) { //class ID of trashcan
            humanoidState = HumanoidState::RELEASING;
            lowFrame = false;
        } else if(lowFrame && targetClassID == DetectNetController::ClassID::CUP) {
            humanoidState = HumanoidState::GRABBING;
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
    
    sleep(1);
    
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
    Turn(1);

    if(detectnetController->ConvertIntToClassID(detectnetController->GetTargetBB(targetClassID)[4]) == DetectNetController::ClassID::UNKNOWN){
       return false; 
    } else {
       return true;
    }
}
