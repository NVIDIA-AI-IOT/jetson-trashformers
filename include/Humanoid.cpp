#include "Humanoid.h"

#define DEFAULT_ZIGBEE_DEVICEINDEX 0

Humanoid::Humanoid(int argc, char** argv) { //CONSTRUCTOR

    serialHandler = new SerialHandler();
    zigb = serialHandler->GetZigbController();
    behaviorController = new BehaviorController(serialHandler);    
    arm = new Arm(serialHandler);
    detectnetController = new DetectNetController(argc, argv);
    keyboardController = new KeyboardController(zigb);
}

Humanoid::~Humanoid() {

}

void Humanoid::UseKeyboard(){
    keyboardController->Init();
    keyboardController->RunInput();
}
