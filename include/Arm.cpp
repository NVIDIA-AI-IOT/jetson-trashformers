#include "Arm.h"

#define SHOULDER_ID 0
#define    BICEP_ID 1
#define    ELBOW_ID 2
#define     CLAW_ID 3 

Arm::Arm(){
    shoulder = new Servo(SHOULDER_ID);
    bicep    = new Servo(BICEP_ID);
    elbow    = new Servo(ELBOW_ID);
    claw     = new Servo(CLAW_ID);
}

Arm::~Arm(){

}

void Arm::Set(int pos_shoulder, int pos_bicep, int pos_elbow, int pos_claw){
    SetShoulder(pos_shoulder);
    SetBicep(pos_bicep);
    SetElbow(pos_elbow);
    SetClaw(pos_claw);
}

void Arm::SetShoulder(int pos){
    shoulder->SetSetpoint(pos);
    pos_shoulder = pos;
}

void Arm::SetBicep(int pos){
    bicep->SetSetpoint(pos);
    pos_bicep = pos;
}

void Arm::SetElbow(int pos){
    elbow->SetSetpoint(pos);
    pos_elbow = pos;
}

void Arm::SetClaw(int pos){
    claw->SetSetpoint(pos);
    pos_claw = pos;
}
