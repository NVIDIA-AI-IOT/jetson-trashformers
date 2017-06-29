#include "Humanoid.h"
#include "dynamixel_sdk.h"

#ifdef __cplusplus
extern "C" {
#endif
    #include "include/zigbee.h"
    #include "include/zgb_hal.h"
#ifdef __cplusplus
}
#endif
#define DEFAULT_DEVICEINDEX 0
#define ADDR_MX_TORQUE_ENABLE 24
#define ADDR_MX_GOAL_POSITION 30
#define ADDR_MX_PRESENT_POSITION 36

#define PROTOCOL VERSION 1.0

#define DXL_ID 8
#define BAUDRATE 1000000
#define DEVICENAME "/dev/ttyUSB0"

#define TORQUE_ENABLE 1
#define TORQUE_DISABLE 0
#define DXL_MIN_POSITION_VALUE 100
#define DXL_MAX_POSITION_VALUE 400

#define DXL_MOVING_STATUS_THRESHOLD 10


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
    if(zgb_initialize(DEFAULT_DEVICEINDEX) == 0) {
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
