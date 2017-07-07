#ifndef HEAD_H_
#define HEAD_H_

#include "dynamixel_sdk.h"
#include "Servo.h"
#include "SerialHandler.h"

class Head {

    public:
        
        Head(SerialHandler* serialHandler);
        virtual ~Head();

        void moveHead(float dist, float bb_x, float bb_y, float bb_area, float camWidth, float camHeight); 
        

    private:
        Servo* cameraServo;
        SerialHandler* m_serialHandler;

};

#endif
