#ifndef ARM_H_
#define ARM_H_

#include <stdio.h>
#include <iostream>
#include "Servo.h"

class Arm {
    public:
        Arm();
        virtual ~Arm();

        void Set(int pos_shoulder, int pos_bicep, int pos_elbow, int pos_claw);

        void SetShoulder(int pos_shoulder);
        void SetBicep(int pos_bicep);
        void SetElbow(int pos_elbow);
        void SetClaw(int pos_claw);
        
    private:
        Servo *shoulder, *bicep, *elbow, *claw;
        int pos_shoulder, pos_bicep, pos_elbow, pos_claw;
        
};

#endif //ARM_H_
