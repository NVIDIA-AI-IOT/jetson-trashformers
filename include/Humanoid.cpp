#include "Humanoid.h"

#define DEFAULT_DEVICEINDEX 0

Humanoid::Humanoid() { //CONSTRUCTOR
    ZigbController* zigb = new ZigbController(DEFAULT_DEVICEINDEX);
    zigb->ConnectZigbee();
}

Humanoid::~Humanoid() {

}

double Humanoid::GetCupCenterY(){
    return 0.0;
}

void Humanoid::WalkForward(){
    zigb->SendCommand(1);
}

void Humanoid::Stop(){
    zigb->Stop();
}
