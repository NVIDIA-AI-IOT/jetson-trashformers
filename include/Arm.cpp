#include "Arm.h"

#define SHOULDER_ID 1
#define    ELBOW_ID 3
#define    WRIST_ID 5
#define     CLAW_ID 7 

Arm::Arm(SerialHandler* serialHandler){
    m_serialHandler = serialHandler;
    dynamixel::PortHandler* portHandler = serialHandler->GetDynamixelPortHandler();
    shoulder = new Servo(SHOULDER_ID, portHandler);
    elbow    = new Servo(ELBOW_ID, portHandler);
    wrist    = new Servo(WRIST_ID, portHandler);
    claw     = new Servo(CLAW_ID, portHandler);
}

Arm::~Arm(){

}

void Arm::Set(int pos_shoulder, int pos_elbow, int pos_wrist, int pos_claw, int vel_setpoint){
    m_serialHandler->OpenDynamixelPort(); 
    SetShoulder(pos_shoulder, vel_setpoint);
    SetElbow(pos_elbow, vel_setpoint);
    SetWrist(pos_wrist, vel_setpoint);
    SetClaw(pos_claw, vel_setpoint);
}

void Arm::SetShoulder(int pos, int vel){
    m_serialHandler->OpenDynamixelPort();
    pos = pos > SHOULDER_MAX ? SHOULDER_MAX : pos;
    pos = pos < SHOULDER_MIN ? SHOULDER_MIN : pos;
    shoulder->SetVelocitySetpoint(vel);
    shoulder->SetPositionSetpoint(pos);
    pos_shoulder = pos;
}

void Arm::SetElbow(int pos, int vel){
    m_serialHandler->OpenDynamixelPort();
    pos = pos > ELBOW_MAX ? ELBOW_MAX : pos;
    pos = pos < ELBOW_MIN ? ELBOW_MIN : pos;
    elbow->SetVelocitySetpoint(vel);
    elbow->SetPositionSetpoint(pos);
    pos_elbow = pos;
}

void Arm::SetWrist(int pos, int vel){ 
    m_serialHandler->OpenDynamixelPort();
    pos = pos > WRIST_MAX ? WRIST_MAX : pos;
    pos = pos < WRIST_MIN ? WRIST_MIN : pos;
    wrist->SetVelocitySetpoint(vel);
    wrist->SetPositionSetpoint(pos);
    pos_elbow = pos;
}

void Arm::SetClaw(int pos, int vel){
    m_serialHandler->OpenDynamixelPort();
    pos = pos > CLAW_MAX ? CLAW_MAX : pos;
    pos = pos < CLAW_MIN ? CLAW_MIN : pos;    
    claw->SetVelocitySetpoint(vel);
    claw->SetPositionSetpoint(pos);
    pos_claw = pos;
}

void Arm::SetDefaultPose() {   
    Set(pose_default[0], pose_default[1], pose_default[2], pose_default[3], 200);
}

void Arm::SetReadyPose() {
    Set(pose_ready[0], pose_ready[1], pose_ready[2], pose_ready[3], 200);   
}

void Arm::SetGrabbingPose() {
    Set(pose_grabbing[0], pose_grabbing[1], pose_ready[2], pose_ready[3], 200);
}

void Arm::GrabCup() {
    SetWrist(pose_grabbing[2], 200);
    SetClaw(pose_grabbing[3], 800);
}

void Arm::SetStorePose() {
    Set(pose_store[0], pose_store[1], pose_store[2], pose_store[3], 200);
}

void Arm::SetReleasePose() {
    Set(pose_release[0], pose_release[1], pose_release[2], pose_release[3], 200);
}

void Arm::SetPose(ArmPose pose) {
    switch(pose) {
        default: 
        case ArmPose::DEFAULT:
            SetDefaultPose();
            break;
        case ArmPose::READY:
            SetReadyPose();
            break;
        case ArmPose::GRABBING:
            SetGrabbingPose();
            break;
        case ArmPose::GRAB:
            GrabCup();
            break;
        case ArmPose::STORE:
            SetStorePose();
            break;
        case ArmPose::RELEASE:
            SetReleasePose();
            break;
    }
}
