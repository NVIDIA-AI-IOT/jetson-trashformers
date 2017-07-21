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
#include "BehaviorController.h"

class Humanoid {
    public:
        Humanoid(int camPort, std::string model);
        virtual ~Humanoid();

        double GetCupCenterY();
        double GetCupCenterX();

        void UseKeyboard();

        void UpdateState(int xReactionTolerance, int areaTolerance);
        
        void GrabVerticalCup();
        
        SerialHandler* serialHandler;
        Arm* arm;
        DetectNetController* detectnetController;
        BehaviorController* behaviorController; 
    private:
        ZigbController* zigb;
        KeyboardController* keyboardController;
        bool grab = false;
};

#endif // HUMANOID_H_
