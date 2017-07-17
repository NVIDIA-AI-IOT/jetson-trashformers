#include "Head.h"

Head::Head(SerialHandler* serialHandler) {
    cameraServo = new Servo(1, serialHandler->GetDynamixelPortHandler());
    m_serialHandler = serialHandler;
}     

Head::~Head() {

}

void Head::moveHead(float dist, float bb_x, float bb_y, float bb_area, float camWidth, float camHeight) {

    m_serialHandler->OpenDynamixelPort(); 

    float errorX = camWidth/2.0 - bb_x;
    float errorY = camHeight/2.0 - bb_y;

    printf("hyp: %f, bb_x: %f, bb_y: %f, bb_area: %f, camWidth: %f, camHeight: %f", dist, bb_x, bb_y, bb_area, camWidth, camHeight);

}
