#ifndef DETECTNETCONTROLLER_H_
#define DETECTNETCONTROLLER_H_

#include <stdio.h>
#include <iostream>
#include <thread>
#include <stdint.h>
#include <math.h>
#include <algorithm>
#include <functional>
#include <array>
#include <vector>
#include "../util/detectnet-camera.h"

class DetectNetController {
    public:
        DetectNetController(int argc, char** argv);
        virtual ~DetectNetController();

        
        //Thread Control Functions 
        void JoinDetectThread();

        //Functions that read values from detectnet-controller.cpp
        void ReadCameraResolution();
        float** ReadUnsortedBBArray();
        volatile int* ReadNumberOfDetectedBB();

        float GetCenterXFromBB(float* bb);
        float GetCenterYFromBB(float* bb);
        float GetErrorXOfTargetBB();
        float GetErrorYOfTargetBB();
        bool IsDetectNetReady();
        void SetCameraPort(int source);

        float GetCameraWidth();
        float GetCameraHeight();
        float GetCameraCenterX();
        float GetCameraCenterY();

        float* GetBBNearestToCenter();

    private:
        float** bbArrayUnsorted;
        volatile int numberOfDetectedBB;

        float cameraCenterX;
        float cameraCenterY;
        float cameraWidth;
        float cameraHeight;

        std::vector<float*> SortBBArrayByTargetDistance();

        float GetDistanceFromTwoPoints(float x1, float y1, float x2, float y2);

        //Thread Control
        void runThread();
        std::thread* detectNetThread;

        //Arguments
        int m_argc;
        char** m_argv;
};

#endif

