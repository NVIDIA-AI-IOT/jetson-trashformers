#ifndef HUMANOID_H_
#define HUMANOID_H_

#include <stdio.h>
#include <iostream>

#include "ZigbController.h"
#include "KeyboardController.h"
#include "DetectNetController.h"
#include "Controls.h"
#include "Arm.h"
#include "Servo.h"
#include "SerialHandler.h"
#include "Head.h"
#include "BehaviorController.h"

class Humanoid {
    public:
        Humanoid(int argc, char** argv);
        virtual ~Humanoid();

        double GetCupCenterY();
        double GetCupCenterX();

        void UseKeyboard();

        SerialHandler* serialHandler;
        Arm* arm;
        DetectNetController* detectnetController;
        BehaviorController* behaviorController; 
    private:
        ZigbController* zigb;
        KeyboardController* keyboardController;
};

#endif // HUMANOID_H_
