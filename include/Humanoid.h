#ifndef HUMANOID_H_
#define HUMANOID_H_

#include <stdio.h>
#include <iostream>

#include "../util/zigbee.h"
#include "../util/zgb_hal.h"

class Humanoid {
    public:
        Humanoid();
        virtual ~Humanoid();
        
        double GetCupCenterY();
        double GetCupCenterX();

        void WalkForward();
        void Stop();
        
        int ConnectZigbee();
        void CloseZigbee();

    private:
        
};

#endif

