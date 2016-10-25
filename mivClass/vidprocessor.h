#ifndef VIDPROCESSOR_H
#define VIDPROCESSOR_H

#include <typeinfo>

#include <QDesktopWidget>
#include <QtCore>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>

#include "mivbgslib.h"
#include "mivuttil.h"
#include "dialogrange.h"
#include "groundplane.h"
#include "tools.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

namespace miv {
    class vidProcessor
    {


    private:
        cv::VideoCapture capture;   // the OpenCV video capture object
        cv::Ptr<IBGS> metBG;    /// ALGORITHM PROCESSOR
        timeCounter timer;  /// Timer object

        bool callIt;    // determine if the processing or not
        bool processOnGray; // determine if Input color must be convert to gray
        bool stop;  // to stop the processing
        bool writeImageOutput = false;  //// Write Image result flag

        cv::Mat iniFrame,gray;   // buffer frame for initial the selected method

        int delay;  // delay between each frame processing
        int processedFrameRate; // number of frame rate
        int fnumber;    // number of processed frames
        int frameToStop;     // stop at this frame number
        int scrWidth=0,scrHeight=0; //// Screen Resolution

        double processedTime;

        cv::Size_<int> camRes;

        string windowNameInput;    // Input display window name
        string windowNameOutput;   // Output display window name
        string srcInputName;    //// Keep Video Input name
        string saveOutputPath;  //// Full Path Save Image Output with Name
        string saveOutputDirPath;   //// Full Path Save Image Output
        string methodName;  //// Selected Method Name
        string prefName = "f_"; //// Prefix save file name
        string extOutput = "."; //// Format save file name

        bool readNextFrame(cv::Mat& frame);
        void writeImageToDisk(cv::Mat &out); /// Write image output to disk
        void setMethodName(string strMethod); // Utility srcipt when before processing get selected method name

    public:
        vidProcessor();
        ~vidProcessor();

        void setMethodProcessor(cv::Ptr<IBGS>const &metProcessorPtr);   // set the instance of the class that implements the BGSLib interface
        void setMethodProcessor(bool&); /// No processing , Preview Only
        void callProcess(); // process callback to be called
        void convertColorSpace();
        bool setInput(const string &filename);  // set the name of the video file or sequence images
        bool setInput(int &id);  // set the camera ID
        void displayInput(string wn);   // to display the input frames
        void displayOutput(string wn);  // to display the processed frames
        bool run(); // to grab (and process) the frames of the sequence
        bool stopIt();  // Stop the processing
        bool isStopped();   // Is the process stopped?
        bool isOpened();    // Is a capture device opened?
        void setDelay(int d);   // set a delay between each frame 0 means wait at each frame negative means no delay
        long getFrameNumber();   // return the frame number of the next frame
        double getFrameRate(); // return the frame rate
        int getProcessedFrameRate();
        void setWriteImageToDisk(bool flag);
        string setSaveOutputPath(string &outputPath, string &outputFormat); /// Set Path for saving Image output
        string getSaveOutputDirPath();
        void setCamRes(Size_<int> &inputRes);

        DialogRange dr;
        cv::Ptr<GroundPlane> gp;
        bool p,s;
        //static void CallBackFunc(int event, int x, int y, int flags, void* userdata);

        bool runVTesting();
        static Point testingLow;
        bool usingFeature,useEdge;
        Mat roiChecker,roiColor;
        int contCounter;
        double contTemp;

        int winWIDTH=800;
        int winHEIGHT=600;

        Mat edgeBg;

        int xAreaSize,yAreaSize;
        int HDPAV;
        int calPeakBin(vector<int> heightHis,double percentage);

    };
}
#endif // VIDPROCESSOR_H
