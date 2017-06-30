#include "ZigbController.h"

ZigbController::ZigbController(){
    m_device_index = 0; //default to device index of 0 if an index is not given
}

ZigbController::ZigbController(int device_index){
    m_device_index = device_index;
}

ZigbController::~ZigbController(){
}

int ZigbController::SendCommand(int data){
    if(zgb_tx_data(data) == 0) {
        printf("ZIGB: Failed to transmit command %d!\n", data);
        return -1;
    } else {
        //printf("ZIGB: Succeeded to transmit to %d\n", data);
        return 0;
    }
}

int ZigbController::Stop(){
    return SendCommand(0);
}

int ZigbController::ConnectZigbee(){
    if(zgb_initialize(m_device_index) == 0){
        printf("ZIGB: Failed to initialize Zig2Serial to device index %d!\n", m_device_index);
        return -1;
    } else {
        printf("ZIGB: Successfully initialized Zig2Serial at device index %d\n", m_device_index);
        return 0;
    }
}

void ZigbController::CloseZigbee(){
    printf("ZIGB: Terminating...\n");
    zgb_terminate();
}
