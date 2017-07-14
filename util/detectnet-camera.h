#ifndef DETECTNETCAMERA_H_
#define DETECTNETCAMERA_H_

#include <stdint.h>

void sig_handler(int signo);
int main( int argc, char** argv );
int runDetectNet(int argc, char** argv);
float** getBoundingBoxArray();
int* getNumBoundingBox();
bool getStopSignal();

uint32_t getCameraHeight();
uint32_t getCameraWidth();
bool isCameraLoaded();
void setCameraPort(int source);




#endif
