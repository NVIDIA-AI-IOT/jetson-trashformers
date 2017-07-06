#ifndef DETECTNETCONTROLLER_H_
#define DETECTNETCONTROLLER_H_

#include <stdio.h>
#include <iostream>
#include <thread>
#include <stdint.h>
#include "../util/detectnet-camera.h"

class DetectNetController {
    public:
        DetectNetController(int argc, char** argv);
        virtual ~DetectNetController();
        
        int m_argc;
        char** m_argv;
        void runThread();
        void JoinDetect();
        std::thread* detectNetThread;

        float** GetBBArray();
        volatile int* GetNumBB();

        float GetCenterX(float* bbArray);
        float GetCenterY(float* bbArray);
        uint32_t GetCamWidth();
        uint32_t GetCamHeight();
        bool IsCameraLoaded();
        void SetCamPort(int source);
        
    private:
        float *boxes;
        
};

#endif

