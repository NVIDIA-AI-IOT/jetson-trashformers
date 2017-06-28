#include "Humanoid.h"

#ifdef __cplusplus
extern "C" {
#endif
    #include "include/zigbee.h"
    #include "include/zgb_hal.h"
#ifdef __cplusplus
}
#endif
#define DEFAULT_DEVICEINDEX 1

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

}

int ConnectZigbee() {
    if(zgb_intialize(1) == 0) {
        printf("Failed to open Zig2Serial!\n");
        return 0;
    }
    return 1;
}

void CloseZigbee() {
    zgb_terminate();
}

int main() {
    Humanoid* humanoid = new Humanoid();
    if(ConnectZigbee()) {
        humanoid->WalkForward();
    } else {
        return 0;
    }
}
