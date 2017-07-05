#include "DetectNetController.h"

DetectNetController::DetectNetController(int argc, char** argv){
    //Run the DetectNet Program
    m_argc = argc;
    m_argv = argv;
    
    std::thread detectNetThread(&DetectNetController::runThread, this);
    
    printf("CUSTOM\n");
    printf("CUSTOM\n");
    printf("CUSTOM\n");
    printf("CUSTOM\n");
    printf("CUSTOM\n");
    printf("CUSTOM\n");
    printf("CUSTOM\n");
    detectNetThread.join();
    
}

DetectNetController::~DetectNetController(){

}

//THREAD FUNCTION
void DetectNetController::runThread(){
    runDetectNet(m_argc, m_argv);
}
