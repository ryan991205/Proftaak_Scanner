#include <iostream>
#include <stdexcept>

#include "Camera.h"
#include "ImageImporter.h"
#include "ConnectionManager.h"

#define CONNECTION_MANAGER_SLEEP_TIME_IN_MILLIS 500
#define PRINTER_SLEEP_TIME_IN_MILLIS 500


Camera* GetNewCam()
{
    return NULL;
}

int main()
{
    ConnectionManager* connectionManager = new ConnectionManager(CONNECTION_MANAGER_SLEEP_TIME_IN_MILLIS, PRINTER_SLEEP_TIME_IN_MILLIS);
    //ConnectionManager& connectionManager;
    Camera* cam = NULL;

    //ImageConverter converter;

    bool bContinue = true;
    while(bContinue)
    {

    }

    if(cam != NULL)
    {
        delete cam;
    }

    delete connectionManager;


    return 0;
}

// important note!: Make sure you have OpenCV installed.
//                  linux: www.codebind.com/cpp-tutorial/install-opencv-ubuntu-cpp/

// To Do:
//          - Install OpenCV
//
//          - Main:                 include openCV
//
//          - ICamera:              include OpenCV
//          - ICamera:              CaptureImage function implementation
//
//          - Camera:               include OpenCV
//          - Camera:               CaptureImage function implementation
//
//          - ImageImporter:        include OpenCV
//          - ImageImporter:        Import function implementation
//
//          - ImageExporter:        include OpenCV
//          - ImageExporter:        Export function implementation
//
//          - ImageConverter:       include OpenCv
//          - ImageConverter:       Convert function implementation
//
//          - MazeSolver:           include OpenCV
//          - MazeSolver:           Solve function implementation
//
//          - Broadcaster:          Broadcast function implementation
//
//          - Printer:              Constructor starts Loop function on seperate thread
//          - Printer:              Destructor stops Loop function on seperate thread
//          - Printer:              RequestNrOfJobs function implementation
//          - Printer:              HandleMessages function implementation
//          - Printer:              SendJob function implementation
//
//          - ConnectionManager:    Constructor starts Loop function on seperate thread
//          - ConnectionManager:    Destructor stops Loop function on seperate thread
//          - ConnectionManager:    make sure that vector printers is locked by thread when in use
//          - ConnectionManager:    HandleMessages function implementation