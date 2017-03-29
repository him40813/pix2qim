#include "vidprocessor.h"

#define bruceForceDebug 0 //0 = none , 1 = numberal Digit Debug , 2 = one Digit Debug

using namespace miv;

vidProcessor::vidProcessor():
    callIt(true),
    delay(-1),
    fnumber(0),
    stop(false),
    frameToStop(-1)
{
    QDesktopWidget widget;
    QRect mainScreenSize = widget.availableGeometry(widget.primaryScreen());
    scrWidth =  mainScreenSize.width();
    scrHeight =  mainScreenSize.height();
    p=false;
    s=false;
    usingFeature=false;
    useEdge=true;
    //read roi checker file


    //roiChecker=imread("37-41_ROI.png",CV_LOAD_IMAGE_GRAYSCALE);
    //roiChecker=imread("100-104_ROI.png",CV_LOAD_IMAGE_GRAYSCALE);
    //roiChecker=imread("106-109_ROI.png",CV_LOAD_IMAGE_GRAYSCALE);
    roiChecker=imread("110-111_ROI.png",CV_LOAD_IMAGE_GRAYSCALE);
    cv::cvtColor(roiChecker, roiColor, cv::COLOR_GRAY2BGR);

    contCounter=0;
    HDPAV=0;

    //test driven code
    //vector<int> test{158,163,161,151,164,162,162,161,163,168,155,160,156,161,170,163,165,163,162,160,164,169,170,168,165,163,162,160,158,161,157,162,160,163,160,162,157,158,161,159,157,156,156,161,158,158,160,159,159,157,159,165,162,161,161,161,160,155,155,156,156,161,161,160,158,162,158,162,162,162,151,156,158,159,162,157,159,161,163,162,162,161,157,155,156,156,157,154,156,155,155,166,164,165,166,162,156,155,161,153,146,160,150,158,159,157,159,161,158,161,162,160,163};
    //cout<<"calPB"<<calPeakBin(test,30)<<endl;
}

vidProcessor::~vidProcessor()
{
    cv::destroyAllWindows();
    metBG.release();
    capture.release();
    clog << "~vidProcessor()" << endl;
}

bool vidProcessor::readNextFrame(cv::Mat& outframe)
{
    if(capture.read(outframe))
    {
        if(camRes.width > 0)
            resize(outframe, outframe, camRes, 0, 0, INTER_CUBIC);
        return true;
    }
    else
        cerr<<"! VideoCapture Can't Read frame input"<<endl;
        return false;
}

void vidProcessor::setMethodProcessor(cv::Ptr<IBGS>const &metProcessorPtr)
{
    metBG = metProcessorPtr;
    setMethodName(typeid(*metBG).name());
    callProcess();
}

void vidProcessor::setMethodProcessor(bool &)
{
    setMethodName("Without Process");
    callIt = false;
}

void vidProcessor::callProcess()
{

    callIt= true;
}

void vidProcessor::convertColorSpace()
{
    processOnGray = true;
}

bool vidProcessor::setInput(const string &filename)
{
    fnumber = 0;
    // In case a resource was already
    // associated with the VideoCapture instance
    capture.release();

    // Open the video file
    if (capture.open(filename))
    {
        capture.read(iniFrame);
        //// get filename based
        QString tmpName = QString::fromStdString( filename ) ;
        mediaInfo srcInfo( tmpName );
        srcInputName = srcInfo.srcName.toStdString();
    }
        return capture.open(filename);
}

bool vidProcessor::setInput(int &id)
{
    fnumber= 0;
    // In case a resource was already
    // associated with the VideoCapture instance
    capture.release();

    // Open the video file
    if (capture.open(id))
    {
        capture.read(iniFrame);
    }
    return capture.open(id);
}

void::vidProcessor::setCamRes(Size_<int> &inputRes)
{
    camRes.width = inputRes.width;
    camRes.height = inputRes.height;
}

void vidProcessor::displayInput(string wn)
{
    if (callIt)
        windowNameInput= wn;
    else
        windowNameInput =+" (Preview Mode)";
    cv::namedWindow(windowNameInput,WINDOW_NORMAL);
    cv::moveWindow(windowNameInput,scrWidth-(430*3),100);
}

void vidProcessor::displayOutput(string wn)
{
    if(callIt)
    {
        windowNameOutput= wn+" from "+methodName + " Algorithm";
        cv::namedWindow(windowNameOutput,WINDOW_NORMAL);
        cv::moveWindow(windowNameOutput,scrWidth-(430*2),100);
        namedWindow("intersect",WINDOW_NORMAL);
        //namedWindow("intersectV2");
    }
}

bool vidProcessor::run()
{
    // current frame
    cv::Mat frame;
    // output frame
    cv::Mat input,output, output_bkgmodel;

    // if no capture device has been set
    if (!isOpened())
        return false;

    stop = false;

    /// Start Timer for frame rate compute
    timer.timeStart();

    gp=new GroundPlane();

    std::ofstream outputfile;
    string filename=saveOutputPath+srcInputName +"_"+ methodName+".csv";
    outputfile.open(filename.c_str());
    vector<int> heightHis;


    while (!isStopped()) {

        if (p){
            cv::waitKey(1);
            continue;
        }
        // read next frame if any
        if (!readNextFrame(frame))
              break;

        //if (fnumber==5435)
           // p=true;



        // display input frame
        if (windowNameInput.length()!=0)
        {

            cv::imshow(windowNameInput,frame);
            displayStatusBar(windowNameInput,"Frame# "+std::to_string(fnumber)+"  Timming : "+timer.timerDisplay(),0);
        }

        // calling the process function or method
        if (callIt)
        {
            if (processOnGray)
            {
                cv::cvtColor(frame,input,CV_BGR2GRAY);
            }
            else
            {
                input = frame;
            }

            //cv::morphologyEx(input, input, cv::MORPH_OPEN, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(11,11)));
            //cv::morphologyEx(input, input, cv::MORPH_CLOSE, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(11,11)));

            if (!input.empty() && !frame.empty())
            {
#if bruceForceDebug>0
                cout<<"step : 1 "<<endl;
#endif
                metBG->process(input,output,output_bkgmodel);
               // clog << "# " << fnumber<<" - Input Channels : "<<input.channels() << endl;

                if (fnumber==0){
                    dr.show();
                    dr.setImageMat(frame,capture,gp,&p);
                    p=true;
                }

                cv::cvtColor(frame,gray,CV_BGR2GRAY);
                int yExtra=0;
                int yExtraV2=0;


                vector<vector<Point> > contours;
                vector<vector<Point> > contoursDes;
                vector<Vec4i> hierarchy;
                Mat canny_output;
                int thresh=100;
                RNG rng(12345);
                Canny( output, canny_output, thresh, thresh*2, 3 );



                findContours(canny_output,contours,hierarchy,CV_RETR_EXTERNAL , CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
                Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
                //new
                Mat mask_image( canny_output.size(), CV_8U, Scalar(0));
                // draw your contour in mask
                drawContours(mask_image, contours, 0, Scalar(255), CV_FILLED);


                //cout<<output.type()<<endl;




#if bruceForceDebug>0
                cout<<"step : 2 "<<endl;
#endif

// 7/7/59 added FAST in ROI of BackgroundSubtraction
                //FAST
                std::vector<KeyPoint> keypointsz;
                FAST(gray,keypointsz,52,true,FastFeatureDetector::TYPE_9_16);
                Mat keyMat=tools::key2Mat(keypointsz,gray.rows,gray.cols);

                //edge of real frame
                Mat canny_output_real;
                int thresh_real=100;
                Canny( frame, canny_output_real, thresh_real, thresh_real*2, 3 );

                //edge background subtraction
                if (fnumber==0){
                    edgeBg=canny_output_real.clone();
                    cv::morphologyEx(edgeBg, edgeBg, cv::MORPH_DILATE, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3,3)));
                    xAreaSize=(frame.cols/3);
                    yAreaSize=(frame.rows/3);
                }else{
                    for (int r=0;r<edgeBg.rows;++r){
                        for(int c=0;c<edgeBg.cols;++c){
                            if (edgeBg.at<uchar>(r,c)>0){
                                canny_output_real.at<uchar>(r,c)=0;
                            }
                        }
                    }
                }


                Mat drawing2;
                frame.copyTo(drawing2,output);

                Mat drawing2V2=roiColor.clone();
                //convert cannyReal output to bgr
                Mat colorCanny;
                cv::cvtColor(canny_output_real, colorCanny, cv::COLOR_GRAY2BGR);
                //copy with mask to drawing2v2
                colorCanny.copyTo(drawing2V2,output);
//                namedWindow("ttt");
//                imshow("ttt",canny_output_real);
                bool conCheck=false;


#if bruceForceDebug>0
                cout<<"step : 3 "<<endl;
#endif
                for( int i = 0; i< contours.size() ; i++ )
                {

                   bool outOfRoi=false;


                   Mat tempContour=Mat::zeros(output.size(), CV_8UC1);;
                   drawContours(tempContour, contours, i, Scalar(255), CV_FILLED);
                   Point top,low;
                   vector<Point> vtemp;
#if bruceForceDebug>1
                cout<<"step : 3.1 "<<endl;
#endif
                   if (usingFeature){
                       //Plot keypoint in area
                       cv::Mat nz;
                       cv::findNonZero(keyMat, nz);
                       int yyT=1000,yyL=-1;
                       for (int i = 0; i < nz.total(); i++ ) {
                           Point temp=nz.at<cv::Point>(i);
                           if ((int)roiChecker.at<uchar>(temp)>0){
                               top=Point(0,0);
                               low=Point(0,0);
                               outOfRoi=true;

                               break;
                           }

                           if (tempContour.type()==16){
                               if (tempContour.at<Vec3b>(nz.at<cv::Point>(i))[0]>0){
                                  cv::circle(drawing2,nz.at<cv::Point>(i),3,Scalar(0,0,255),-1);
                                  cv::circle(drawing2V2,nz.at<cv::Point>(i),3,Scalar(0,0,255),-1);
                                  if (temp.y>yyL){
                                      yyL=temp.y;
                                      low=temp;
                                  }
                                  if (temp.y<yyT){
                                      yyT=temp.y;
                                      top=temp;
                                  }
                               }
                           }else if (tempContour.type()==0){
                               if (tempContour.at<uchar>(nz.at<cv::Point>(i))>0){
                                  cv::circle(drawing2,nz.at<cv::Point>(i),3,Scalar(0,0,255),-1);
                                  cv::circle(drawing2V2,nz.at<cv::Point>(i),3,Scalar(0,0,255),-1);
                                  if (temp.y>yyL){
                                      yyL=temp.y;
                                      low=temp;
                                  }
                                  if (temp.y<yyT){
                                      yyT=temp.y;
                                      top=temp;
                                  }
                               }
                           }


                       }
                   }else if (useEdge){
#if bruceForceDebug>1
                cout<<"step : 3.2 "<<endl;
#endif
                       cv::Mat nz;
                       cv::findNonZero(canny_output_real, nz);
                       int yyT=1000,yyL=-1;
#if bruceForceDebug>2
                cout<<"step : 3.21 "<<endl;
#endif
                       for (int j = 0; j < nz.total(); j++ ) {
                           Point temp=nz.at<cv::Point>(j);
#if bruceForceDebug>2
                cout<<"step : 3.22 "<<endl;
#endif
                           if (tempContour.type()==16){
#if bruceForceDebug>2
                cout<<"step : 3.23 "<<endl;
#endif
                               if (tempContour.at<Vec3b>(nz.at<cv::Point>(j))[0]>0){
#if bruceForceDebug>2
                cout<<"step : 3.24 "<<endl;
#endif
                                  if (temp.y>yyL){
                                      yyL=temp.y;
                                      low=temp;
                                  }
                                  if (temp.y<yyT){
                                      yyT=temp.y;
                                      top=temp;
                                  }
                               }
                           }else if (tempContour.type()==0){
#if bruceForceDebug>2
                cout<<"step : 3.25 "<<endl;
#endif
                               if (tempContour.at<uchar>(nz.at<cv::Point>(j))>0){
#if bruceForceDebug>2
                cout<<"step : 3.26 "<<endl;
                cout<<tempContour.size[0]<<","<<tempContour.size[1]<<endl;
                cout<<roiChecker.size[0]<<","<<roiChecker.size[1]<<endl;
#endif

                                   if (roiChecker.at<uchar>(nz.at<cv::Point>(j))>0){
#if bruceForceDebug>2
                cout<<"step : 3.27 "<<endl;
                cout<<"temp<<"<<temp.x<<","<<temp.y<<(int)roiChecker.at<uchar>(temp)<<endl;
                cout<<fnumber<<"true"<<endl;
#endif

                                       //cout<<roiChecker<<endl;

                                       top=Point(50,50);
                                       low=Point(50,50);
                                       outOfRoi=true;
                                       break;

                                   }
                                  if (temp.y>yyL){
                                      yyL=temp.y;
                                      low=temp;
                                  }
                                  if (temp.y<yyT){
                                      yyT=temp.y;
                                      top=temp;
                                  }
                               }
                           }


                       }

                   } else {
                       //find Height+TopPoint+LowPoint

                       int yyT=1000,yyL=-1;

                       for (int j=0;j<contours.at(i).size();++j){
                            Point temp=contours.at(i).at(j);
                            if ((int)roiChecker.at<uchar>(temp)>0){
                                top=Point(0,0);
                                low=Point(0,0);
                                outOfRoi=true;
                                break;
                            }
                            if (temp.y>yyL){
                                yyL=temp.y;
                                low=temp;
                            }
                            if (temp.y<yyT){
                                yyT=temp.y;
                                top=temp;
                            }
                       }
                   }

#if bruceForceDebug>0
                cout<<"step : 4 "<<endl;
#endif
                   vtemp.push_back(top);
                   vtemp.push_back(low);
                   contoursDes.push_back(vtemp);
                   //cv::line(drawing,top,low
                        //    ,cv::Scalar(0,255,255));
                   //draw
                   Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
                   if (!outOfRoi)
                        drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );



#if bruceForceDebug>0
                cout<<"step : 5 "<<endl;
#endif

                   if (fnumber!=0){
                       //cout<<gp->calNormVec2D(Point(400,400))<<endl;
                       //line(drawing,Point(400,400),gp->calNormVec2D(Point(400,400)),cv::Scalar(0,0,255));
                       //test
                       //Point3d s=Point3d(0,0,0);
                       //Point3d e=Point3d(600,450,0);
                       double highC=0;
                       Point nTop=gp->calTopPoint(low,top,highC);

                       double highCV2=0;
                       double farCV2=0;
                       double distanceRN=1000;
                       Point nTopV2=gp->calTopPointNonPerpendicular(low,top,highCV2,distanceRN,farCV2);

                       //cv::line(drawing,low,gp->calPerpenTopPoint(low),cv::Scalar(0,0,255));

#if bruceForceDebug>0
                cout<<"step : 6 "<<endl;
#endif
                        cout<<highCV2<<endl;
                       if (highCV2>90 && highCV2<250 && !outOfRoi ){//highCV2>140 && highCV2<200 && distanceRN<=0.5){

                           double iR=0.05;
                           double growingPersent=abs(highCV2-contTemp)*100/contTemp;
#if bruceForceDebug>1
                cout<<"step : 6.1 "<<endl;
#endif
                           if(!conCheck && distanceRN<1 && highCV2>=contTemp*(1-iR) && highCV2<=contTemp*(1+iR)){//high increase +- 10 percent
                                ++contCounter;
                                contTemp=highCV2;
                                conCheck=true;
                           }else {
                                if (!conCheck && i==contours.size()-1)
                                    contCounter=0;
                                    contTemp=highCV2;
                           }
#if bruceForceDebug>1
                cout<<"step : 6.2 "<<endl;


#endif
                           //heightHis push to vector
                            if (round(highCV2)!=104 && round(highCV2)!=495)
                                heightHis.push_back(round(highCV2));

                           if (heightHis.size()>10){
                               HDPAV=calPeakBin(heightHis,30);
                           }
                           outputfile<<to_string(fnumber)<<",";
                           outputfile << to_string(highCV2)<<",";
                           outputfile << to_string(HDPAV)<<",";
                           outputfile << to_string(highC)<<",";
                           outputfile << to_string(distanceRN)<<",";
                           outputfile << to_string(farCV2)<<",";
                           outputfile << to_string(contCounter)<<",";
                           outputfile << to_string(growingPersent)<<",";
                           outputfile << to_string((low.y/yAreaSize*3)+low.x/xAreaSize)<<",";
                           outputfile<<endl;
                           cout<<"distanceRN: "<<distanceRN<<endl;
                           //line(drawing,low,gp->calTestHigh(low),cv::Scalar(0,0,255));
                           //line(drawing,low,nTop,cv::Scalar(255,0,255));
                           line(drawing,low,nTopV2,cv::Scalar(255,0,0));
#if bruceForceDebug>1
                cout<<"step : 6.3 "<<endl;
#endif
                           putText( drawing2, to_string(highC)+"("+to_string(distanceRN)+")", Point(nTop.x+20,nTop.y+yExtra), FONT_HERSHEY_PLAIN,
                                        1,  Scalar(0,contCounter>2?255:0,contCounter>2?0:255));

                           putText( drawing, to_string(highCV2)+"("+to_string(distanceRN)+")", Point(nTop.x+20,nTop.y+yExtra), FONT_HERSHEY_PLAIN,
                                        1,  Scalar(0,contCounter>2?255:0,contCounter>2?0:255));

#if bruceForceDebug>1
                cout<<"step : 6.4 "<<endl;
#endif
                        if(heightHis.size()>10) {

                            putText( drawing2V2, to_string(HDPAV), Point(nTopV2.x+20,nTopV2.y+yExtraV2), FONT_HERSHEY_PLAIN,
                                        1,  Scalar(0,255,0));
                        }

//                           yExtra+=30;
//                           yExtraV2+=30;
                       }








                   }



                }

#if bruceForceDebug>0
                cout<<"step : 7 "<<endl;
#endif

                //subplot
                Mat im3(drawing2.size().height, drawing2.size().width+drawing2V2.size().width, CV_8UC3);
                Mat left(im3, Rect(0, 0, drawing2.size().width, drawing2.size().height));
                //drawing2.copyTo(left);
                drawing.copyTo(left);
                Mat right(im3, Rect(drawing2.size().width, 0, drawing2V2.size().width, drawing2V2.size().height));
                drawing2V2.copyTo(right);

                cv::imshow("intersect",im3);
                //cv::imshow("intersectV2",drawing2V2);
                output=drawing.clone();

                if (output.empty())
                {
                    input.copyTo(output);
                }


                ////  Save output as Image
                writeImageToDisk(im3);
            }

        }
        /// NO IMAGE PROCESSING
        else
        {

          output = frame;
        }



        // increment frame number
        fnumber++;

        // display output frame
        if (windowNameOutput.length()!=0 && callIt)
        {
            cv::imshow(windowNameOutput,output);
            displayStatusBar(windowNameOutput,"Processed FPS# "+std::to_string(fnumber/timer.timeStopinSec()),0);
        }

        // display Special output (BG MODEL)
        if (!output_bkgmodel.empty())
        {
            string bgwinName = "BG Model from " +methodName + " Algorithm";
            cv::namedWindow(bgwinName,WINDOW_NORMAL );
            cv::moveWindow(bgwinName,scrWidth-(430*1),100);
            cv::imshow(bgwinName,output_bkgmodel);
        }
        // introduce a delay
        if (delay >= 0 && cv::waitKey(delay) >= 0)
            return stopIt();

        // check if we should stop
        if (frameToStop >= 0)
            return stopIt();

        if (s){
            p=true;
            s=false;
        }


    }   // END WHILE
    outputfile<<"median"<<endl<<"=MEDIAN(B:B)"<<endl;
    outputfile<<"average"<<endl<<"=AVERAGE(B:B)"<<endl;
    outputfile<<"std"<<endl<<"=STDEV(B:B)"<<endl;
    outputfile.close();


    return stopIt();
}

Point vidProcessor::testingLow=Point(100,100);
void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
     if ( flags == (EVENT_FLAG_LBUTTON) )
     {
         vidProcessor::testingLow.x=x;
         vidProcessor::testingLow.y=y;
          cout << "Left mouse button is clicked while pressing CTRL key - position (" << x << ", " << y << ")" << endl;
     }
//     else if ( flags == (EVENT_FLAG_RBUTTON + EVENT_FLAG_SHIFTKEY) )
//     {
//          cout << "Right mouse button is clicked while pressing SHIFT key - position (" << x << ", " << y << ")" << endl;
//     }
//     else if ( event == EVENT_MOUSEMOVE && flags == EVENT_FLAG_ALTKEY)
//     {

//          cout << "Mouse is moved over the window while pressing ALT key - position (" << x << ", " << y << ")" << endl;
//     }
}

bool vidProcessor::runVTesting(){
    // current frame
    cv::Mat frame;
    // output frame
    cv::Mat input,output, output_bkgmodel;

    // if no capture device has been set
    if (!isOpened())
        return false;

    stop = false;

    /// Start Timer for frame rate compute
    timer.timeStart();

    gp=new GroundPlane();

    std::ofstream outputfile;
    string filename="testdata.csv";
    outputfile.open(filename.c_str());

    setMouseCallback(windowNameInput,CallBackFunc,NULL);


    while (!isStopped()) {

        if (p){
            cv::waitKey(1);
            continue;
        }
        // read next frame if any
        if (!readNextFrame(frame))
              break;



        // display input frame
        if (windowNameInput.length()!=0)
        {
            cv::imshow(windowNameInput,frame);
            displayStatusBar(windowNameInput,"Frame# "+std::to_string(fnumber)+"  Timming : "+timer.timerDisplay(),0);
        }

        // calling the process function or method
        if (callIt)
        {
            if (processOnGray)
            {
                cv::cvtColor(frame,input,CV_BGR2GRAY);
            }
            else
            {
                input = frame;
            }

            if (!input.empty() && !frame.empty())
            {

                metBG->process(input,output,output_bkgmodel);
               // clog << "# " << fnumber<<" - Input Channels : "<<input.channels() << endl;

                if (fnumber==0){
                    dr.show();
                    dr.setImageMat(frame,capture,gp,&p);
                    p=true;

                }else{



                    double highC1,highC2,highC3,highC4,highC5;
                    double highCV21,highCV22,highCV23,highCV24,highCV25;

                    Point low=Point(vidProcessor::testingLow.x,vidProcessor::testingLow.y);
                        cout<<low<<endl;
                    Point3d TopPoint=gp->calTestHighV3d(low);

                    Point testTopPoint1=gp->getPointAtImageFrom3D(Point3d(TopPoint.x-20,TopPoint.y,TopPoint.z));
                    Point testTopPoint2=gp->getPointAtImageFrom3D(Point3d(TopPoint.x-10,TopPoint.y,TopPoint.z));
                    Point testTopPoint3=gp->getPointAtImageFrom3D(Point3d(TopPoint.x,TopPoint.y,TopPoint.z));
                    Point testTopPoint4=gp->getPointAtImageFrom3D(Point3d(TopPoint.x+10,TopPoint.y,TopPoint.z));
                    Point testTopPoint5=    gp->getPointAtImageFrom3D(Point3d(TopPoint.x+20,TopPoint.y,TopPoint.z));

                    Point p1=gp->calTopPoint(low,testTopPoint1,highC1);
                    Point p2=gp->calTopPoint(low,testTopPoint2,highC2);
                    Point p3=gp->calTopPoint(low,testTopPoint3,highC3);
                    Point p4=gp->calTopPoint(low,testTopPoint4,highC4);
                    Point p5=gp->calTopPoint(low,testTopPoint5,highC5);

                    double distanceRN1=1000;
                    double d1=0;
                    double d2=0;
                    double d3=0;
                    double d4=0;
                    double d5=0;
                    Point pp1=gp->calTopPointNonPerpendicular(low,testTopPoint1,highCV21,distanceRN1,d1);
                    Point pp2=gp->calTopPointNonPerpendicular(low,testTopPoint2,highCV22,distanceRN1,d2);
                    Point pp3=gp->calTopPointNonPerpendicular(low,testTopPoint3,highCV23,distanceRN1,d3);
                    Point pp4=gp->calTopPointNonPerpendicular(low,testTopPoint4,highCV24,distanceRN1,d4);
                    Point pp5=gp->calTopPointNonPerpendicular(low,testTopPoint5,highCV25,distanceRN1,d5);

                    Mat drawing = output;

                    //line(drawing,low,gp->calTestHigh(low),cv::Scalar(0,0,255));
                    //line(drawing,low,testTopPoint3,cv::Scalar(255,0,255));

                    Mat drawing2;
                    drawing.copyTo(drawing2);
                    Mat drawing2V2;
                    drawing.copyTo(drawing2V2);

                    outputfile<<to_string(fnumber)<<",";
                    //line cal top point approach1
                    line(drawing2,low,p1,cv::Scalar(0,0,255));
                    line(drawing2,low,p2,cv::Scalar(0,0,255));
                    line(drawing2,low,p3,cv::Scalar(0,255,255));
                    line(drawing2,low,p4,cv::Scalar(0,255,0));
                    line(drawing2,low,p5,cv::Scalar(0,255,0));

                    //line cal top point approach2
                    line(drawing2V2,low,pp1,cv::Scalar(0,0,255));
                    line(drawing2V2,low,pp2,cv::Scalar(0,0,255));
                    line(drawing2V2,low,pp3,cv::Scalar(0,255,255));
                    line(drawing2V2,low,pp4,cv::Scalar(0,255,0));
                    line(drawing2V2,low,pp5,cv::Scalar(0,255,0));



                    putText( drawing2, to_string(highC1), Point(testTopPoint3.x+30,testTopPoint3.y+10), FONT_HERSHEY_PLAIN,
                                 2,  Scalar(0,0,255));
                    putText( drawing2, to_string(highC2), Point(testTopPoint3.x+30,testTopPoint3.y+40), FONT_HERSHEY_PLAIN,
                                 2,  Scalar(0,0,255));
                    putText( drawing2, to_string(highC3), Point(testTopPoint3.x+30,testTopPoint3.y+70), FONT_HERSHEY_PLAIN,
                                 2,  Scalar(0,255,255));
                    putText( drawing2, to_string(highC4), Point(testTopPoint3.x+30,testTopPoint3.y+100), FONT_HERSHEY_PLAIN,
                                 2,  Scalar(0,255,0));
                    putText( drawing2, to_string(highC5), Point(testTopPoint3.x+30,testTopPoint3.y+130), FONT_HERSHEY_PLAIN,
                                 2,  Scalar(0,255,0));

                    putText( drawing2V2, to_string(highCV21), Point(testTopPoint3.x+30,testTopPoint3.y+10), FONT_HERSHEY_PLAIN,
                                 2,  Scalar(0,0,255));
                    putText( drawing2V2, to_string(highCV22), Point(testTopPoint3.x+30,testTopPoint3.y+40), FONT_HERSHEY_PLAIN,
                                 2,  Scalar(0,0,255));
                    putText( drawing2V2, to_string(highCV23), Point(testTopPoint3.x+30,testTopPoint3.y+70), FONT_HERSHEY_PLAIN,
                                 2,  Scalar(0,255,255));
                    putText( drawing2V2, to_string(highCV24), Point(testTopPoint3.x+30,testTopPoint3.y+100), FONT_HERSHEY_PLAIN,
                                 2,  Scalar(0,255,0));
                    putText( drawing2V2, to_string(highCV25), Point(testTopPoint3.x+30,testTopPoint3.y+130), FONT_HERSHEY_PLAIN,
                                 2,  Scalar(0,255,0));




                    outputfile<<endl;

                    //subplot
                    Mat im3(drawing2.size().height, drawing2.size().width+drawing2V2.size().width, CV_8UC3);
                    Mat left(im3, Rect(0, 0, drawing2.size().width, drawing2.size().height));
                    drawing2.copyTo(left);
                    Mat right(im3, Rect(drawing2.size().width, 0, drawing2V2.size().width, drawing2V2.size().height));
                    drawing2V2.copyTo(right);

                    cv::imshow("intersect",im3);
                    //cv::imshow("intersectV2",drawing2V2);

                    if (output.empty())
                    {
                        input.copyTo(output);
                    }


                }
            }

        }
        /// NO IMAGE PROCESSING
        else
        {

          output = frame;
        }

        ////  Save output as Image
        writeImageToDisk(output);

        // increment frame number
        fnumber++;

        // display output frame
        if (windowNameOutput.length()!=0 && callIt)
        {
            cv::imshow(windowNameOutput,output);
            displayStatusBar(windowNameOutput,"Processed FPS# "+std::to_string(fnumber/timer.timeStopinSec()),0);
        }

        // display Special output (BG MODEL)
        if (!output_bkgmodel.empty())
        {
            string bgwinName = "BG Model from " +methodName + " Algorithm";
            cv::namedWindow(bgwinName,WINDOW_NORMAL);
            cv::moveWindow(bgwinName,scrWidth-(430*1),100);
            cv::imshow(bgwinName,output_bkgmodel);
        }
        // introduce a delay
        if (delay >= 0 && cv::waitKey(delay) >= 0)
            return stopIt();

        // check if we should stop
        if (frameToStop >= 0)
            return stopIt();

        if (s){
            p=true;
            s=false;
        }


    }   // END WHILE
    outputfile.close();
    return stopIt();
}

bool vidProcessor::stopIt()
{
    stop= true;
    /// Compute Processed frame rate
    processedTime = timer.timeStopinSec();
    processedFrameRate = fnumber/processedTime;

    /// Clear resources
    cv::destroyAllWindows();
    metBG.release();
    capture.release();
    clog << "Stop It and release possible resources." <<endl;
    return true;
}

bool vidProcessor::isStopped()
{
    return stop;
}

bool vidProcessor::isOpened()
{
   return capture.isOpened();
}


void vidProcessor::setDelay(int d)
{
    delay= d;
}

long vidProcessor::getFrameNumber()
{
    long f = static_cast<long>(capture.get(CV_CAP_PROP_POS_FRAMES));
    return f;
}

double vidProcessor::getFrameRate()
{
    double r = capture.get(CV_CAP_PROP_FPS);
    return r;
}

int vidProcessor::getProcessedFrameRate()
{
    return processedFrameRate;
}

string vidProcessor::setSaveOutputPath(string &outputPath, string &outputFormat)
{
    outputPath = outputPath+ "/"+ srcInputName +"_"+ methodName;
    extOutput += outputFormat;

    infoDirFile dirInfo(QString::fromStdString(outputPath) );

    if(dirInfo.isDirExist())
    {
        if (dirInfo.isDirEmpty())
        {
            saveOutputPath = dirInfo.getDirFullPath() + prefName;
            saveOutputDirPath = dirInfo.getDirFullPath();

        }
        else
        {

            infoDateTime dt;
            QString tmp = "dd_MM_yy_hh_mm";
            string newDirName = outputPath+"_"+dt.getDateTimeInfo(tmp);

            newDirName = dirInfo.genDir( newDirName );
            saveOutputPath = newDirName + prefName;
            saveOutputDirPath = newDirName;

        }
    }
    else
    {
        saveOutputPath = dirInfo.genDir( dirInfo.getDirFullPath() ) + prefName;
        saveOutputDirPath = dirInfo.getDirFullPath();
    }

    setWriteImageToDisk(true);
    return getSaveOutputDirPath();
}

void vidProcessor::setWriteImageToDisk(bool flag)
{
    writeImageOutput = flag;
}

string vidProcessor::getSaveOutputDirPath()
{
    return saveOutputDirPath;
}

void vidProcessor::writeImageToDisk(Mat &out)
{
    if(writeImageOutput)
    cv::imwrite(saveOutputPath+std::to_string(fnumber)+extOutput,out);
}

void vidProcessor::setMethodName(string strMethod)
{
    //// Utility srcipt when before processing
    /// get selected method name
    QString tmpStr = QString::fromStdString(strMethod);
    tmpStr.remove(QRegExp("[^a-zA-Z\\_]"));
    methodName = tmpStr.toStdString();
}



int vidProcessor::calPeakBin(vector<int> heightHis,double percentage)
{
    //sort first
    sort(heightHis.begin(),heightHis.end());
    //prepare parameter
    vector<int> tempHeight,tempNum;
    int remainNumber=heightHis.size()*percentage/100;

    //order height information into histrogram
    for (int i=0;i<heightHis.size();++i){
        int thisHeight=heightHis.at(i);

        std::vector<int>::iterator found=find(tempHeight.begin(),tempHeight.end(),thisHeight);
        if (found!=tempHeight.end()){
            int hIndex=distance(tempHeight.begin(),found);
            ++tempNum.at(hIndex);
            //cout<<thisHeight<<" : "<<tempHeight.at(hIndex)<<endl;
             cout<<"thisHeight1"<<tempNum.at(hIndex)<<endl;
        }else {
            tempHeight.push_back(thisHeight);
            tempNum.push_back(1);
            cout<<"thisHeight1"<<tempHeight.at(0)<<endl;
        }
    }
    cout<<"1"<<endl;

    //find peak bin
    std::vector<int>::iterator maxNum=max_element(tempNum.begin(),tempNum.end());
    //cout<<"maxNum: "<<*maxNum<<endl;
    int maxNumIndex=distance(tempNum.begin(),maxNum);
    int maxCount = count (tempNum.begin(), tempNum.end(),*maxNum);
    //cout<<"maxCount: "<<maxCount<<endl;
    //Multiple max value circumstance
    if (maxCount>1){
        int mostValue=0;
        int mostValInd=-1;
        for (int mi=0;mi<tempNum.size();++mi){
            if (tempNum.at(mi)==*maxNum){
                //initialize neighboor value
                cout<<"maxNum & ind"<<tempNum.at(mi)<<" : "<<mi<<endl;
                int thisVal=0;
                if (mi-1>=0)
                    thisVal+=tempNum.at(mi-1);
                if (mi+1<tempNum.size())
                    thisVal+=tempNum.at(mi+1);
                //compare with mostValue
                if (thisVal>mostValue){
                    mostValue=thisVal;
                    mostValInd=mi;
                }
            }
        }
        maxNumIndex=mostValInd;
        //cout<<"maxNumInd : "<<maxNumIndex<<" : "<<tempHeight.at(maxNumIndex)<<endl;
    }

    cout<<"2"<<endl;
    //main loop for opt
    int leftShift=1;
    int rightShift=1;
    vector<int> resultNum(tempNum.size(),0);
    cout<<tempNum.size()<<" : "<<resultNum.size()<<endl;
    //install max num
    resultNum.at(maxNumIndex)=tempNum.at(maxNumIndex);
    while(remainNumber>0){
        int lVal=-1;
        int rVal=-1;

        //initialize right and left val
        if (maxNumIndex-leftShift>=0)
            lVal=tempNum.at(maxNumIndex-leftShift);
        if (maxNumIndex+rightShift<tempNum.size())
            rVal=tempNum.at(maxNumIndex+rightShift);

        //compare
        if (lVal>=rVal && lVal!=-1){

            resultNum.at(maxNumIndex-leftShift)=lVal;
            remainNumber-=lVal;
            ++leftShift;
        }else if(rVal!=-1) {

            resultNum.at(maxNumIndex+rightShift)=rVal;
            remainNumber-=rVal;
            ++rightShift;
        }else{
            //cout<<remainNumber<<endl;
            break;
        }

    }
    cout<<"3"<<endl;
    int allVal=0;
    int allNum=0;
    for (int wi=0;wi<resultNum.size();++wi){
        cout<<wi<<","<<resultNum.size()<<endl;
        int tempNum=resultNum.at(wi);
        cout<<tempNum<<endl;
        if (tempNum>0){
            allVal+=tempNum*tempHeight.at(wi);
            allNum+=tempNum;
        }
        cout<<allVal<<","<<allNum<<endl;
    }

    cout<<"average : "<<allVal/allNum<<endl;

    return allVal/allNum;

}


