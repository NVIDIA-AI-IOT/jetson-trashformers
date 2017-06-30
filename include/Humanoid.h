#ifndef HUMANOID_H_
#define HUMANOID_H_

#include <stdio.h>
#include <iostream>

#include "ZigbController.h"
#include "KeyboardController.h"
#include "Controls.h"

class Humanoid {
    public:
        Humanoid();
        virtual ~Humanoid();
        
        double GetCupCenterY();
        double GetCupCenterX();

        //Movement commands through Zigbee
        void Stop();
        
        void WalkForward();
        void WalkBackward();

        void TurnLeft();
        void TurnRight();

        void WalkForwardLeft();
        void WalkForwardRight();

        void SidestepLeft();
        void SidestepRight();

        void FastSidestepLeft();
        void FastSidestepRight();

        void StepDiagonalFrontalLeft();
        void StepDiagonalFrontalRight();

        void StepDiagonalDorsalLeft();
        void StepDiagonalDorsalRight();

        void GetUpFacingUp();
        void GetUpFacingDown();

    private:
        ZigbController* zigb;
        KeyboardController* keyboardController;
        
};

#endif // HUMANOID_H_
