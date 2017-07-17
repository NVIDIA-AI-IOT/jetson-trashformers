#include "DetectNetController.h"

DetectNetController::DetectNetController(int argc, char** argv){
    //Run the DetectNet Program
    m_argc = argc;
    m_argv = argv;

    SetCameraPort(0);
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

void DetectNetController::ReadCameraResolution(){ 
    cameraCenterX = (float)(getCameraWidth()) / 2.0;
    cameraCenterY = (float)(getCameraHeight()) / 2.0;
    cameraWidth = getCameraWidth();
    cameraHeight = getCameraHeight();

    //print camera dimensions
    std::cout << "CAM_CENTER_X" << cameraCenterX << std::endl;
    std::cout << "CAM_CENTER_Y" << cameraCenterY << std::endl;
}

//ARRAY SORTING
std::vector<float*> DetectNetController::SortBBArrayByTargetDistance(){ 
    bbArrayUnsorted = ReadUnsortedBBArray();
    numberOfDetectedBB = *ReadNumberOfDetectedBB();

    bbArraySorted.clear();

    printf("Found %i Bounding Boxes.\n", numberOfDetectedBB);

    for(int i=0; i<numberOfDetectedBB; i++){
        float* bb = bbArrayUnsorted[i];
        bbArraySorted.push_back(bb);

        printf("BB #%i: (X1: %f, Y1: %f), (X2:%f, Y2: %f)\n", i, bb[0], bb[1], bb[2], bb[3]);
    }

    if(numberOfDetectedBB > 0){
        //Sort array based on the bounding boxes' distances from center of camera
        std::sort(bbArraySorted.begin(), bbArraySorted.end(), [this](float* a, float* b) {
            float tmpCenterX1 = this->GetCenterXFromBB(a);
            float tmpCenterX2 = this->GetCenterXFromBB(b);

            float tmpCenterY1 = this->GetCenterYFromBB(a);
            float tmpCenterY2 = this->GetCenterYFromBB(b);

            float distance1 = this->GetDistanceFromTwoPoints(tmpCenterX1, tmpCenterY1, this->cameraCenterX, this->cameraCenterY);
            float distance2 = this->GetDistanceFromTwoPoints(tmpCenterX2, tmpCenterY2, this->cameraCenterX, this->cameraCenterY);

            return distance1 < distance2;
        });
    }

    //Print distance to center of all detected bounding boxes
    for(auto a : bbArraySorted) {
        float tmpCenterX = GetCenterXFromBB(a);
        float tmpCenterY = GetCenterYFromBB(a);

        float tmpDistance = GetDistanceFromTwoPoints(tmpCenterX, tmpCenterY, cameraCenterX, cameraCenterY);

        std::cout << tmpDistance << " ";
    }
    std::cout << std::endl;

    return bbArraySorted;
}

float* DetectNetController::GetTargetBB(){
    std::vector<float*> sortedArray = SortBBArrayByTargetDistance();
    if(sortedArray.size() > 0) return sortedArray[0];
    else return nullptr;
}

float DetectNetController::GetAreaOfTargetBB(){
    if(bbArraySorted.size() < 1) return -1;
    float* bb = bbArraySorted[0];
    return (bb[2]-bb[0]) * (bb[3]-bb[1]);
}

float DetectNetController::GetDistanceFromTwoPoints(float x1, float y1, float x2, float y2) {
    return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}

//RETURN FUNCTIONS FOR detectnet-camera.cpp 
float** DetectNetController::ReadUnsortedBBArray(){
    return getBoundingBoxArray();
}

volatile int* DetectNetController::ReadNumberOfDetectedBB(){
    return getNumBoundingBox();
}

/**
 * Returns true if CTRL + C is pressed
 */
bool DetectNetController::ReadStopSignal(){
    return getStopSignal();
}

float DetectNetController::GetCenterXFromBB(float* bb) {
    if(bb) return (bb[0] + bb[2]) / 2.0;
    else return -1;
}

float DetectNetController::GetCenterYFromBB(float* bb) {
    if(bb) return (bb[1] + bb[3]) / 2.0;
    else return -1;
}

float DetectNetController::GetErrorXOfTargetBB() {
    const float offset = (1.0/4.0) * (GetCameraWidth());
    if(bbArraySorted.size() < 1) return NULL;
    float cX = GetCenterXFromBB(bbArraySorted[0]);
    if(cX == -1) return NULL;
    return cX - GetCameraCenterX() - offset; 
}

float DetectNetController::GetErrorYOfTargetBB() {
    if(bbArraySorted.size() < 1) return NULL;
    float cY = GetCenterYFromBB(bbArraySorted[0]);
    if(cY == -1) return NULL;
    return cY - GetCameraCenterY(); 
}

bool DetectNetController::IsDetectNetReady(){
    return isCameraLoaded();
}

void DetectNetController::SetCameraPort(int usbSource){
    //command to read video devices: ls -ltrh /dev/video*
    setCameraPort(usbSource);
}

float DetectNetController::GetCameraWidth(){
    return cameraWidth;
}

float DetectNetController::GetCameraHeight(){
    return cameraHeight;
}

float DetectNetController::GetCameraCenterX(){
    return cameraCenterX;
}

float DetectNetController::GetCameraCenterY(){
    return cameraCenterY;
}

DetectNetController::CupOrientation DetectNetController::GetCupOrientation(){
    float* targetCup = GetTargetBB();
    if(targetCup == NULL) return CupOrientation::UKNOWN;
    float width = targetCup[2] - targetCup[0];
    float height = targetCup[3] - targetCup[1];
    if(width > height) return CupOrientation::HORIZONTAL;
    return CupOrientation::VERTICAL;
}
