#ifndef ZIGBCONTROLLER_H_
#define ZIGBCONTROLLER_H_

#include <stdio.h>
#include <iostream>
#include <string.h>

#include "../util/zigbee.h"
#include "../util/zgb_hal.h"

class ZigbController {
    public:
        ZigbController();
        ZigbController(int device_index);
        virtual ~ZigbController();
        
        int ConnectZigbee();
        int SendCommand(int data);
        int Stop();
        void CloseZigbee();

    private:
        int m_device_index;
        
};

#endif

