#ifndef DETECTNETCONTROLLER_H_
#define DETECTNETCONTROLLER_H_

#include <stdio.h>
#include <iostream>
#include <thread>
#include <algorithm>
#include <vector>
#include <string>
#include "../util/detectnet-camera.h"

class DetectNetController {
    public:
        DetectNetController(int camPort, std::string model);
        virtual ~DetectNetController();

        //Structure of Unsorted Bounding Box: [x1][y1][x2][y2] (bottom left: x1, y1; top right: x2, y2)

        //Structure of Sorted Bounding Box: [x1][y1][x2][y2] (bottom left: x1, y1; top right: x2, y2), ClassID
        std::vector<std::array<float, 5>> SortBBArrayByTargetDistance();
        std::vector<std::array<float, 5>> bbArraySorted;

        //Thread Control Functions 
        void JoinDetectThread();

        //Functions that read values from detectnet-controller.cpp
        void ReadCameraResolution();
        float** ReadUnsortedBBArray();
        volatile int* ReadNumberOfDetectedBB();
        bool ReadStopSignal();

        float GetCenterXFromBB(std::array<float, 5> bb);
        float GetCenterYFromBB(std::array<float, 5> bb);
        bool IsDetectNetReady();
        void SetCameraPort(int source);

        float GetCameraWidth();
        float GetCameraHeight();
        float GetCameraCenterX();
        float GetCameraCenterY();

        std::array<float, 5> GetTargetBB();
        float GetAreaOfTargetBB();
        float GetErrorXOfTargetBB();
        float GetErrorYOfTargetBB();
        int GetClassIDFromUnsortedBBNum(int bbNum);
    

        enum class CupOrientation {
                VERTICAL=0,
                HORIZONTAL=1,
                UKNOWN=2
        };

        DetectNetController::CupOrientation GetCupOrientation();

    private:
        float* GetConfCPU();

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
        std::string m_model;
};

#endif

