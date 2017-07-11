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

        //Structure of Bounding Box: [x1][y1][x2][y2] (bottom left: x1, y1; top right: x2, y2)
        std::vector<float*> SortBBArrayByTargetDistance();
        std::vector<float*> bbArraySorted;
        
        //Thread Control Functions 
        void JoinDetectThread();

        //Functions that read values from detectnet-controller.cpp
        void ReadCameraResolution();
        float** ReadUnsortedBBArray();
        volatile int* ReadNumberOfDetectedBB();

        float GetCenterXFromBB(float* bb);
        float GetCenterYFromBB(float* bb);
        bool IsDetectNetReady();
        void SetCameraPort(int source);

        float GetCameraWidth();
        float GetCameraHeight();
        float GetCameraCenterX();
        float GetCameraCenterY();

        float* GetTargetBB();
        float GetAreaOfTargetBB();
        float GetErrorXOfTargetBB();
        float GetErrorYOfTargetBB();

        float camCenterX;
        float camCenterY;
        float hypotenuse(float x1, float y1, float x2, float y2);

	    //static const int VERTICAL = 0;
	    //static const int HORIZONTAL = 1;
                
        enum class CupOrientation {
            VERTICAL=0,
            HORIZONTAL=1,
            UKNOWN=2
        };
    
        DetectNetController::CupOrientation GetCupOrientation();

    private:
        float** bbArrayUnsorted;
        volatile int numberOfDetectedBB;

        float cameraCenterX;
        float cameraCenterY;
        float cameraWidth;
        float cameraHeight;


        float GetDistanceFromTwoPoints(float x1, float y1, float x2, float y2);

        //Thread Control
        void runThread();
        std::thread* detectNetThread;

        //Arguments
        int m_argc;
        char** m_argv;
};

#endif

