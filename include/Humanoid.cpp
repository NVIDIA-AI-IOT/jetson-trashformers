#include "Humanoid.h"

#define DEFAULT_ZIGBEE_DEVICEINDEX 0

Humanoid::Humanoid(int argc, char** argv) { //CONSTRUCTOR

    serialHandler = new SerialHandler();
    zigb = serialHandler->GetZigbController();
    //motor_1 = new Servo(1, serialHandler->GetDynamixelPortHandler());
    behaviorController = new BehaviorController(serialHandler);    
    arm = new Arm(serialHandler);
    head = new Head(serialHandler);
    detectnetController = new DetectNetController(argc, argv);
    keyboardController = new KeyboardController(zigb);
}

Humanoid::~Humanoid() {

}

void Humanoid::UseKeyboard(){
    keyboardController->Init();
    keyboardController->RunInput();
}

void Humanoid::Stop(){
    zigb->Stop();
}

void Humanoid::WalkForward(){
    zigb->SendCommand(BUTTON_WALK_FORWARD);
}
void Humanoid::WalkBackward(){
    zigb->SendCommand(BUTTON_WALK_BACKWARD);
}


void Humanoid::TurnLeft(){
    zigb->SendCommand(BUTTON_TURN_LEFT);
}
void Humanoid::TurnRight(){
    zigb->SendCommand(BUTTON_TURN_RIGHT);
}


void Humanoid::WalkForwardLeft(){
    zigb->SendCommand(BUTTON_WALK_FORWARD_LEFT);
}
void Humanoid::WalkForwardRight(){
    zigb->SendCommand(BUTTON_WALK_FORWARD_RIGHT);
}


void Humanoid::SidestepLeft(){
    zigb->SendCommand(BUTTON_SIDESTEP_LEFT);
}
void Humanoid::SidestepRight(){
    zigb->SendCommand(BUTTON_SIDESTEP_RIGHT);
}


void Humanoid::FastSidestepLeft(){
    zigb->SendCommand(BUTTON_SIDESTEP_FAST_LEFT);
}
void Humanoid::FastSidestepRight(){
    zigb->SendCommand(BUTTON_SIDESTEP_FAST_RIGHT);
}


void Humanoid::StepDiagonalFrontalLeft(){
    zigb->SendCommand(BUTTON_DIAGONAL_FRONTAL_LEFT);
}
void Humanoid::StepDiagonalFrontalRight(){
    zigb->SendCommand(BUTTON_DIAGONAL_FRONTAL_RIGHT);
}


void Humanoid::StepDiagonalDorsalLeft(){
    zigb->SendCommand(BUTTON_DIAGONAL_DORSAL_LEFT);
}
void Humanoid::StepDiagonalDorsalRight(){
    zigb->SendCommand(BUTTON_DIAGONAL_DORSAL_RIGHT);
}


void Humanoid::GetUpFacingUp(){
    zigb->SendCommand(BUTTON_GET_UP_FACING_UP);
}
void Humanoid::GetUpFacingDown(){
    zigb->SendCommand(BUTTON_GET_UP_FACING_DOWN);
}
