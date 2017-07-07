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
        
        void JoinDetectThread();

        float** GetBBArray();
        volatile int* GetNumBB();

        float GetCenterX(float* bbArray);
        float GetCenterY(float* bbArray);
        float GetErrorX();
        float GetErrorY();
        float GetHypotenuse();
        uint32_t GetCamWidth();
        uint32_t GetCamHeight();
        bool IsCameraLoaded();
        void SetCamPort(int source);

        void Init();
        std::vector<float*> GetSortedBBArray();
        float* GetTargetBB();

        float camCenterX;
        float camCenterY;
        float hypotenuse(float x1, float y1, float x2, float y2);
        
    private:
        float** bbArray;
        std::vector<float*> bbArraySorted;
        volatile int numBB;

        int iterate;


        //float *boxes;
        void runThread();
        int m_argc;
        char** m_argv;
        std::thread* detectNetThread;
};

#endif

