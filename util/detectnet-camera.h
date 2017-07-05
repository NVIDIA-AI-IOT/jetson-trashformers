#ifndef DETECTNETCAMERA_H_
#define DETECTNETCAMERA_H_

void sig_handler(int signo);
int main( int argc, char** argv );
int runDetectNet(int argc, char** argv);
float* getBoundingBoxArray();



#endif
