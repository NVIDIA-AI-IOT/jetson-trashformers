#include "Humanoid.h"

#define DEFAULT_DEVICEINDEX 0

Humanoid::Humanoid() { //CONSTRUCTOR

}

Humanoid::~Humanoid() {

}

double Humanoid::GetCupCenterY(){
    return 0.0;
}

void Humanoid::WalkForward(){
    if( zgb_tx_data(1) == 0 ) {
        printf("Failed to transmit\n");
    } else {
        printf("Succeeded to transmit\n");
    }
}

void Humanoid::Stop(){
    if( zgb_tx_data(0) == 0) {
        printf("Failed to transmit\n");
    } else {
        printf("Succeeded to transmit\n");
    }
}

int Humanoid::ConnectZigbee() {
    if(zgb_initialize(DEFAULT_DEVICEINDEX) == 0) {
        printf("Failed to open Zig2Serial!\n");
        return 0;
    }
    return 1;
}

void Humanoid::CloseZigbee() {
    printf("Closing\n");
    zgb_terminate();
}
