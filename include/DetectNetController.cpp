#include "DetectNetController.h"

DetectNetController::DetectNetController(std::string model){
    //Run the DetectNet Program
    m_model = model;
    
    SetCameraPort(0);
    detectNetThread = new std::thread(&DetectNetController::runThread, this);
}

DetectNetController::~DetectNetController(){

}

//THREAD FUNCTIONS
void DetectNetController::runThread(){
    runDetectNet(m_model);
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
std::vector<std::array<float, 5>> DetectNetController::SortBBArrayByTargetDistance(){ 
        bbArrayUnsorted = ReadUnsortedBBArray();
        numberOfDetectedBB = *ReadNumberOfDetectedBB();
        
        bbArraySorted.clear();
        
        printf("Found %i Bounding Boxes.\n", numberOfDetectedBB);
        
        int boxNum = 0; //used to keep track of which box we are on in the unsorted bb array 
        for(int i=0; i<numberOfDetectedBB * 4; i+=4){
            float* bb = bbArrayUnsorted[0];
            int classID = GetClassIDFromUnsortedBBNum(boxNum);
            std::array<float, 5> arr = { bb[i], bb[i+1], bb[i+2], bb[i+3], classID};
            //float* arrptr = arr;
            bbArraySorted.push_back(arr);
 
            printf("BB #%i: (X1: %f, Y1: %f), (X2:%f, Y2: %f), classID: %i\n", boxNum, arr[0], arr[1], arr[2], arr[3], classID);
            boxNum++;
        }

        if(numberOfDetectedBB > 0){
            //Sort array based on the bounding boxes' distances from center of camera
            std::sort(bbArraySorted.begin(), bbArraySorted.end(), [this](std::array<float, 5> a, std::array<float, 5> b) {
                float tmpCenterX1 = this->GetCenterXFromBB(a);
                float tmpCenterX2 = this->GetCenterXFromBB(b);
                
                float tmpCenterY1 = this->GetCenterYFromBB(a);
                float tmpCenterY2 = this->GetCenterYFromBB(b);

                float distance1 = this->GetDistanceFromTwoPoints(tmpCenterX1, tmpCenterY1, this->cameraCenterX, this->cameraCenterY);
                float distance2 = this->GetDistanceFromTwoPoints(tmpCenterX2, tmpCenterY2, this->cameraCenterX, this->cameraCenterY);
                
                return distance1 < distance2;
            });
        }        

        std::cout << std::endl;

        return bbArraySorted;
}

std::array<float, 5> DetectNetController::GetTargetBB(){
    std::vector< std::array<float, 5> > sortedArray = SortBBArrayByTargetDistance();
    if(sortedArray.size() > 0) return sortedArray[0];
    else return std::array<float, 5>();
}

float DetectNetController::GetAreaOfTargetBB(){
    if(bbArraySorted.size() < 1) return -1;
    std::array<float, 5> bb = bbArraySorted[0];
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

float DetectNetController::GetCenterXFromBB(std::array<float, 5> bb) {
    if(!bb.empty()){
        printf("GetCenterXFromBB: bb[0] = %0.0f, bb[2] = %0.0f \n", bb[0], bb[2]);
        return (bb[0] + bb[2]) / 2.0;
    }
    else return -1;
}

float DetectNetController::GetCenterYFromBB(std::array<float, 5> bb) {
    if(!bb.empty()){ 
        printf("GetCenterXFromBB: bb[1] = %0.0f, bb[3] = %0.0f \n", bb[1], bb[3]);
        return (bb[1] + bb[3]) / 2.0;   
    }
    else return -1;
}

float DetectNetController::GetErrorXOfTargetBB() {
   const float offset = (1.0/4.0) * (GetCameraWidth());
   if(bbArraySorted.size() < 1) return 0.0;
   float cX = GetCenterXFromBB(bbArraySorted[0]);
   if(cX == -1) return 0.0;
   return cX - GetCameraCenterX() - offset; 
}

float DetectNetController::GetErrorYOfTargetBB() {
   if(bbArraySorted.size() < 1) return 0.0;
   float cY = GetCenterYFromBB(bbArraySorted[0]);
   if(cY == -1) return 0.0;
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

int DetectNetController::GetClassIDFromUnsortedBBNum(int bbNum){
    float* confCPU = GetConfCPU();
    return (int)confCPU[bbNum*2+1];//process to acquire class # obtained from detectnet-camera.cpp
}

float* DetectNetController::GetConfCPU(){
    return getConfCPU();
}

DetectNetController::CupOrientation DetectNetController::GetCupOrientation(){
    std::array<float, 5> targetCup = GetTargetBB();
    if(targetCup.empty()) return CupOrientation::UKNOWN;
    float width = targetCup[2] - targetCup[0];
    float height = targetCup[3] - targetCup[1];
    if(width > height) return CupOrientation::HORIZONTAL;
    return CupOrientation::VERTICAL;
}
