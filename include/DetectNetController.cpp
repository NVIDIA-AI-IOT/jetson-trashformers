#include "DetectNetController.h"

DetectNetController::DetectNetController(int argc, char** argv){
    //Run the DetectNet Program
    m_argc = argc;
    m_argv = argv;
    
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

unsigned int DetectNetController::GetCamWidth(){
    return getCameraWidth();
}

unsigned int DetectNetController::GetCamHeight(){
    return getCameraHeight();
}

bool DetectNetController::IsCameraLoaded(){
    return isCameraLoaded();
}
