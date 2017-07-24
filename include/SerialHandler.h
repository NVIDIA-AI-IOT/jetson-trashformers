#ifndef SERIAL_HANDLER_H
#define SERIAL_HANDLER_H

#include "ZigbController.h"
#include "../util/dynamixel_sdk.h"

#define DEVICENAME_DEFAULT "/dev/ttyACM0"

class SerialHandler {

    public:

        SerialHandler();
        virtual ~SerialHandler();

        int OpenZigbPort();
        int OpenDynamixelPort();

        ZigbController* GetZigbController();
        dynamixel::PortHandler* GetDynamixelPortHandler();

    private:

        ZigbController* zigb;
        dynamixel::PortHandler* portHandler;

};
#endif
