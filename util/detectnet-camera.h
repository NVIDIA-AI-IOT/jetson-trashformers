#ifndef DETECTNETCAMERA_H_
#define DETECTNETCAMERA_H_

#include <stdint.h>
#include <string>

void sig_handler(int signo);
int main( int argc, char** argv );
int runDetectNet(std::string modelNum);
float** getBoundingBoxArray();
int* getNumBoundingBox();
bool getStopSignal();
float* getConfCPU();

bool getLoopLock();
void setLoopLock(bool lockState);

uint32_t getCameraHeight();
uint32_t getCameraWidth();
bool isCameraLoaded();
void setCameraPort(int source);




#endif
