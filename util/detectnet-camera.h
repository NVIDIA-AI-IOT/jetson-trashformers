#ifndef DETECTNETCAMERA_H_
#define DETECTNETCAMERA_H_

void sig_handler(int signo);
int main( int argc, char** argv );
int runDetectNet(int argc, char** argv);
float** getBoundingBoxArray();
int* getNumBoundingBox();

unsigned int getCameraHeight();
unsigned int getCameraWidth();
bool isCameraLoaded();




#endif
