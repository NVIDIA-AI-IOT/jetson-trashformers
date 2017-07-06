#include "DetectNetController.h"

DetectNetController::DetectNetController(int argc, char** argv){
    //Run the DetectNet Program
    m_argc = argc;
    m_argv = argv;
    
    SetCamPort(-1);
    detectNetThread = new std::thread(&DetectNetController::runThread, this);
    
}

DetectNetController::~DetectNetController(){

}

//THREAD FUNCTION
void DetectNetController::runThread(){
    runDetectNet(m_argc, m_argv);
}

void DetectNetController::JoinDetect(){
    detectNetThread->join();
}

float** DetectNetController::GetBBArray(){
    return getBoundingBoxArray();
}

volatile int* DetectNetController::GetNumBB(){
    return getNumBoundingBox();
}

float DetectNetController::GetCenterX(float* bbArray) {
    return (bbArray[0] + bbArray[2]) / 2.0;
}

float DetectNetController::GetCenterY(float* bbArray) {
    return (bbArray[1] + bbArray[3]) / 2.0;
}

uint32_t DetectNetController::GetCamWidth(){
    return getCameraWidth();
}

uint32_t DetectNetController::GetCamHeight(){
    return getCameraHeight();
}

bool DetectNetController::IsCameraLoaded(){
    return isCameraLoaded();
}

void DetectNetController::SetCamPort(int source){
    setCameraPort(source);
}
