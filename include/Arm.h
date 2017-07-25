#ifndef ARM_H_
#define ARM_H_

#include <stdio.h>
#include <iostream>
#include "Servo.h"
#include "dynamixel_sdk.h"
#include "SerialHandler.h"

#define SHOULDER_MAX 800
#define SHOULDER_MIN 150

#define ELBOW_MAX 1023
#define ELBOW_MIN 350

#define WRIST_MAX 762
#define WRIST_MIN 250

#define CLAW_MAX 610
#define CLAW_MIN 220

class Arm {     
    public:
        Arm(SerialHandler* serialHandler);
        virtual ~Arm();


        enum class ArmPose {
            DEFAULT,
            READY,
            GRABBING, 
            GRAB,
            STORE
        };

        void Set(int pos_shoulder, int pos_elbow, int pos_wrist, int pos_claw, int vel_setpoint);

        void SetShoulder(int pos_shoulder, int vel);
        void SetElbow(int pos_elbow, int vel);
        void SetWrist(int pos_wrist, int vel);
        void SetClaw(int pos_claw, int vel);

        void SetPose(ArmPose pose);
       
    private:
        SerialHandler* m_serialHandler;
        Servo *shoulder, *elbow, *wrist, *claw;
        int pos_shoulder, pos_elbow, pos_wrist, pos_claw;
        int pose_default[4] = {342, 572, 762, 610};   
        int pose_ready[4] = {650, 700, 350, 220};
        int pose_grabbing[4] = {650, 480, 250, 540};
        int pose_store[4] = {342, 572, 660, 540};
        
        void SetDefaultPose();
        void SetReadyPose();
        void SetGrabbingPose();
        void GrabCup(); 
        void SetStorePose();

};

#endif //ARM_H_
