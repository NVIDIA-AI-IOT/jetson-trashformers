/*
 * http://github.com/dusty-nv/jetson-inference
 */

#include "detectnet-camera.h"
#include "gstCamera.h"

#include "glDisplay.h"
#include "glTexture.h"

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string>

#include "cudaMappedMemory.h"
#include "cudaNormalize.h"
#include "cudaFont.h"

#include "detectNet.h"

//#define DEFAULT_CAMERA 2  // -1 for onboard camera, or change to index of /dev/video V4L2 camera (>=0)	

		
bool signal_recieved = false;
float* bb = NULL;
float** boxes = NULL;
int numBoundingBoxes = 0;
float* currentConfCPU = NULL;
int actualNumBB = 0;
uint32_t camera_Height = 0;
uint32_t camera_Width = 0;
bool cameraIsLoaded = false;
int camera_source = -1;

bool loopLock = false;

void sig_handler(int signo)
{
	if( signo == SIGINT )
	{
		printf("received SIGINT\n");
		signal_recieved = true;
	}
}

bool getStopSignal(){
   return signal_recieved; 
}

void setCameraPort(int source){
    camera_source = source;
}

bool getLoopLock(){
    return loopLock; 
}

void setLoopLock(bool lockState){
    loopLock = lockState;
}

float** getBoundingBoxArray(){
    return boxes;
}

float* getConfCPU(){
    return currentConfCPU;
}

int *getNumBoundingBox(){
    return &actualNumBB;
}

bool isCameraLoaded(){
    return cameraIsLoaded;
}

uint32_t getCameraHeight(){
    return camera_Height;
}

uint32_t getCameraWidth(){
    return camera_Width;
}

int main(int argc, char** argv){
    //runDetectNet(argc);
}


int runDetectNet( std::string modelNum )
{
/*	printf("detectnet-camera\n  args (%i):  ", argc);

	for( int i=0; i < argc; i++ )
		printf("%i [%s]  ", i, argv[i]);
		
	printf("\n\n");
	

	*//*
	 * parse network type from CLI arguments
	 */
	/*detectNet::NetworkType networkType = detectNet::PEDNET_MULTI;

	if( argc > 1 )
	{
		if( strcmp(argv[1], "multiped") == 0 || strcmp(argv[1], "pednet") == 0 || strcmp(argv[1], "multiped-500") == 0 )
			networkType = detectNet::PEDNET_MULTI;
		else if( strcmp(argv[1], "ped-100") == 0 )
			networkType = detectNet::PEDNET;
		else if( strcmp(argv[1], "facenet") == 0 || strcmp(argv[1], "facenet-120") == 0 || strcmp(argv[1], "face-120") == 0 )
			networkType = detectNet::FACENET;
	}*/
	
	if( signal(SIGINT, sig_handler) == SIG_ERR )
		printf("\ncan't catch SIGINT\n");


	/*
	 * create the camera device
	 */
	gstCamera* camera = gstCamera::Create(camera_source);
	
	if( !camera )
	{
		printf("\ndetectnet-camera:  failed to initialize video device\n");
		return 0;
	}
	

	printf("\ndetectnet-camera:  successfully initialized video device\n");
	printf("    width:  %u\n", camera->GetWidth());
	printf("   height:  %u\n", camera->GetHeight());
	printf("    depth:  %u (bpp)\n\n", camera->GetPixelDepth());
	
    std::string network = "networks/snapshot_iter_" + modelNum + ".caffemodel"; 
	/*
	 * create detectNet
	 */
	detectNet* net = detectNet::Create("networks/deploy.prototxt", network.c_str(), "networks/mean.binaryproto");
	
	if( !net )
	{
		printf("detectnet-camera:   failed to initialize imageNet\n");
		return 0;
	}


	/*
	 * allocate memory for output bounding boxes and class confidence
	 */
	const uint32_t maxBoxes = net->GetMaxBoundingBoxes();		printf("maximum bounding boxes:  %u\n", maxBoxes);
	const uint32_t classes  = net->GetNumClasses();
	
	float* bbCPU    = NULL;
	float* bbCUDA   = NULL;
	float* confCPU  = NULL;
	float* confCUDA = NULL;
	
	if( !cudaAllocMapped((void**)&bbCPU, (void**)&bbCUDA, maxBoxes * sizeof(float4)) ||
	    !cudaAllocMapped((void**)&confCPU, (void**)&confCUDA, maxBoxes * classes * sizeof(float)) )
	{
		printf("detectnet-console:  failed to alloc output memory\n");
		return 0;
	}
	

	/*
	 * create openGL window
	 */
	glDisplay* display = glDisplay::Create();
	glTexture* texture = NULL;
	
	if( !display ) {
		printf("\ndetectnet-camera:  failed to create openGL display\n");
	}
	else
	{
		texture = glTexture::Create(camera->GetWidth(), camera->GetHeight(), GL_RGBA32F_ARB/*GL_RGBA8*/);

		if( !texture )
			printf("detectnet-camera:  failed to create openGL texture\n");
	}
	
	
	/*
	 * create font
	 */
	cudaFont* font = cudaFont::Create();
	

	/*
	 * start streaming
	 */
	if( !camera->Open() )
	{
		printf("\ndetectnet-camera:  failed to open camera for streaming\n");
		return 0;
	}
	
	printf("\ndetectnet-camera:  camera open for streaming\n");
	
    //ADDED CAMERA FOR FUNCTIONS --MICHAEL
    cameraIsLoaded = true;
    camera_Width = camera->GetWidth();
    camera_Height = camera->GetHeight();
	
	/*
	 * processing loop
	 */
	float confidence = 0.0f;
	
	while( !signal_recieved )
	{
        while(!loopLock){}

		void* imgCPU  = NULL;
		void* imgCUDA = NULL;
		
		// get the latest frame
		if( !camera->Capture(&imgCPU, &imgCUDA, 1000) )
			printf("\ndetectnet-camera:  failed to capture frame\n");

		// convert from YUV to RGBA
		void* imgRGBA = NULL;
		
		if( !camera->ConvertRGBA(imgCUDA, &imgRGBA) )
			printf("detectnet-camera:  failed to convert from NV12 to RGBA\n");

		// classify image with detectNet
		numBoundingBoxes = maxBoxes;
         
		if( net->Detect((float*)imgRGBA, camera->GetWidth(), camera->GetHeight(), bbCPU, &numBoundingBoxes, confCPU))
		{
		//	printf("%i bounding boxes detected EDITED\n", numBoundingBoxes);
            actualNumBB = numBoundingBoxes;
            currentConfCPU = confCPU;
		
			int lastClass = 0;
			int lastStart = 0;
			
            boxes = new float* [numBoundingBoxes];

			for( int n=0; n < numBoundingBoxes; n++ )
			{
				const int nc = confCPU[n*2+1];
				bb = bbCPU + (n * 4);
				
                boxes[n] = bb;
		//		printf("bounding box EDITEDAGAIN %i   (%f, %f)  (%f, %f)  w=%f  h=%f\n", n, bb[0], bb[1], bb[2], bb[3], bb[2] - bb[0], bb[3] - bb[1]); 

				if( nc != lastClass || n == (numBoundingBoxes - 1) )
				{
					if( !net->DrawBoxes((float*)imgRGBA, (float*)imgRGBA, camera->GetWidth(), camera->GetHeight(), 
						                        bbCUDA + (lastStart * 4), (n - lastStart) + 1, lastClass) )
						printf("detectnet-console:  failed to draw boxes\n");
						
					lastClass = nc;
					lastStart = n;

					CUDA(cudaDeviceSynchronize());
				}
			}
		
			/*if( font != NULL )
			{
				char str[256];
				sprintf(str, "%05.2f%% %s", confidence * 100.0f, net->GetClassDesc(img_class));
				
				font->RenderOverlay((float4*)imgRGBA, (float4*)imgRGBA, camera->GetWidth(), camera->GetHeight(),
								    str, 10, 10, make_float4(255.0f, 255.0f, 255.0f, 255.0f));
			}*/
			
			if( display != NULL )
			{
				char str[256];
				sprintf(str, "TensorRT build %x | %s | %04.1f FPS", NV_GIE_VERSION, net->HasFP16() ? "FP16" : "FP32", display->GetFPS());
				//sprintf(str, "GIE build %x | %s | %04.1f FPS | %05.2f%% %s", NV_GIE_VERSION, net->GetNetworkName(), display->GetFPS(), confidence * 100.0f, net->GetClassDesc(img_class));
				display->SetTitle(str);	
			}	
		}	


		// update display
		if( display != NULL )
		{
			display->UserEvents();
			display->BeginRender();

			if( texture != NULL )
			{
				// rescale image pixel intensities for display
				CUDA(cudaNormalizeRGBA((float4*)imgRGBA, make_float2(0.0f, 255.0f), 
								   (float4*)imgRGBA, make_float2(0.0f, 1.0f), 
		 						   camera->GetWidth(), camera->GetHeight()));

				// map from CUDA to openGL using GL interop
				void* tex_map = texture->MapCUDA();

				if( tex_map != NULL )
				{
					cudaMemcpy(tex_map, imgRGBA, texture->GetSize(), cudaMemcpyDeviceToDevice);
					texture->Unmap();
				}

				// draw the texture
				texture->Render(100,100);		
			}
    
			display->EndRender();
		}
       loopLock = false;
	}
	
	printf("\ndetectnet-camera:  un-initializing video device\n");
	
	
	/*
	 * shutdown the camera device
	 */
	if( camera != NULL )
	{
		delete camera;
		camera = NULL;
	}

	if( display != NULL )
	{
		delete display;
		display = NULL;
	}
	
	printf("detectnet-camera:  video device has been un-initialized.\n");
	printf("detectnet-camera:  this concludes the test of the video device.\n");
	return 0;
}

