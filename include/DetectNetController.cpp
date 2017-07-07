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

//THREAD FUNCTIONS
void DetectNetController::runThread(){
    runDetectNet(m_argc, m_argv);
}

void DetectNetController::JoinDetectThread(){
    detectNetThread->join();
}

//ARRAY SORTING
void DetectNetController::Init(){ 
    camCenterX = (float)(GetCamWidth()) / 2.0;
    camCenterY = (float)(GetCamHeight()) / 2.0;
    std::cout << "CAM_CENTER_X" << camCenterX << std::endl;
    std::cout << "CAM_CENTER_Y" << camCenterY << std::endl;
}

std::vector<float*> DetectNetController::GetSortedBBArray(){ 
        bbArraySorted.clear();
        bbArray = GetBBArray();
        numBB = *GetNumBB();
        //bbArraySorted = bbArray;
        //std::array<float*, numBB> bbArraySorted = bbArray;
        printf("numBB %i:\n", numBB);
        for(int i=0; i<numBB; i++){
            float* bb = bbArray[i];
            bbArraySorted.push_back(bb);
            printf("BB %i: %f, %f, %f, %f\n", i, bb[0], bb[1], bb[2], bb[3]);
        }

        if(numBB != 0){
            std::sort(bbArraySorted.begin(), bbArraySorted.end(), [this](float* a, float* b) {
                float centerX1 = this->GetCenterX(a);
                float centerX2 = this->GetCenterX(b);
                
                float centerY1 = this->GetCenterY(a);
                float centerY2 = this->GetCenterY(b);

                float hyp1 = this->hypotenuse(centerX1, centerY1, this->camCenterX, this->camCenterY);
                float hyp2 = this->hypotenuse(centerX2, centerY2, this->camCenterX, this->camCenterY);
                
                return hyp1 < hyp2;
            });
        }

        for(auto a : bbArraySorted) {
            float cX = GetCenterX(a);
            float cY = GetCenterY(a);

            float hyp = hypotenuse(cX, cY, camCenterX, camCenterY);

            std::cout << hyp << " ";
        }
        std::cout << "\n";
        //std::cin.ignore();
        return bbArraySorted;
}

float* DetectNetController::GetTargetBB(){
    std::vector<float*> sortedArray = GetSortedBBArray();
    if(0 < sortedArray.size()) return sortedArray[0];
    else return nullptr;
}

float DetectNetController::hypotenuse(float x1, float y1, float x2, float y2) {
    return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}

//RETURN FUNCTIONS FOR detectnet-camera.cpp 
float** DetectNetController::GetBBArray(){
    return getBoundingBoxArray();
}

volatile int* DetectNetController::GetNumBB(){
    return getNumBoundingBox();
}

float DetectNetController::GetCenterX(float* bbArray) {
    if(bbArray) return (bbArray[0] + bbArray[2]) / 2.0;
    else return -1;
}

float DetectNetController::GetCenterY(float* bbArray) {
    if(bbArray) return (bbArray[1] + bbArray[3]) / 2.0;
    else return -1;
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
