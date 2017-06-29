#include "Humanoid.h"
#include "dynamixel_sdk.h"
#include <iostream>

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

#define PROTOCOL_VERSION 1.0

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
    if( zgb_tx_data(0) == 0) {
        printf("Failed to transmit\n");
    } else {
        printf("Succeeded to transmit\n");
    }
}

int ConnectZigbee() {
    if(zgb_initialize(DEFAULT_DEVICEINDEX) == 0) {
        printf("Failed to open Zig2Serial!\n");
        return 0;
    }
    return 1;
}

void CloseZigbee() {
    printf("Closing\n");
    zgb_terminate();
}

int OpenDynamixel() {
    dynamixel::PortHandler *portHandler = dynamixel::PortHandler::getPortHandler(DEVICENAME);
    
    if(portHandler->openPort()) {
        printf("Succeeded to open the port!\n");
    } else {
        printf("Failed to open the port!\n");
        return 0;
    }

    if(portHandler->setBaudRate(BAUDRATE)) {
        printf("Changed baudrate!\n");
    } else {
        printf("Failed to change baudrate!\n");
        return 0;
    }

    return 0;    
}

 
int main() {
    Humanoid* humanoid = new Humanoid();
    //OpenDynamixel();   

    int dxl_comm_result = COMM_TX_FAIL;
    uint8_t dxl_error = 0;                          // Dynamixel error
    uint16_t dxl_present_position = 0;              // Present position


    dynamixel::PortHandler *portHandler = dynamixel::PortHandler::getPortHandler(DEVICENAME);
    
    if(portHandler->openPort()) {
        printf("Succeeded to open the port!\n");
    } else {
        printf("Failed to open the port!\n");
        return 0;
    }

    if(portHandler->setBaudRate(BAUDRATE)) {
        printf("Changed baudrate!\n");
    } else {
        printf("Failed to change baudrate!\n");
        return 0;
    }
    
    dynamixel::PacketHandler *packetHandler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);

          
    dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, DXL_ID, ADDR_MX_TORQUE_ENABLE, TORQUE_ENABLE, &dxl_error);
    if (dxl_comm_result != COMM_SUCCESS) {
       packetHandler->printTxRxResult(dxl_comm_result);
    }
    else if (dxl_error != 0) {
        packetHandler->printRxPacketError(dxl_error);
    }
    else {
        printf("Dynamixel has been successfully connected \n");
    }

    dxl_comm_result = packetHandler->write2ByteTxRx(portHandler, DXL_ID, ADDR_MX_GOAL_POSITION, DXL_MIN_POSITION_VALUE, &dxl_error);
    if (dxl_comm_result != COMM_SUCCESS)
    {
      packetHandler->printTxRxResult(dxl_comm_result);
    }
    else if (dxl_error != 0)
    {
      packetHandler->printRxPacketError(dxl_error);
    }

    

    return 0;    
     /*if(ConnectZigbee()) {
        humanoid->WalkForward();
        std::cin.ignore();
        humanoid->Stop();    
    } else {
        return 0;
    }*/
}
