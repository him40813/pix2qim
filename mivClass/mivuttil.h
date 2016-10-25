// Utilities Classes
#ifndef MIVUTTIL
#define MIVUTTIL

#include <opencv/opencv.hpp>
#include <iostream>
#include <iomanip>
#include <QFile>
#include <QStringList>
#include <QTextStream>
#include <QDir>
#include <QDebug>
#include <QElapsedTimer>
#include <QDateTime>
#include <QtCore>
#include <QMessageBox>
#include <QDomDocument>
#include <QCameraInfo>
#include <QCamera>
using namespace std;
using namespace cv;

/// if string contained '.'(dot charecter)
static bool txtIsDouble(QString txt)
{
    QStringList tmpInput = txt.split('.');
    if(tmpInput.size()>1)
        return true;
    else
        return false;
}

class timeCounter
{
    private:
        QElapsedTimer timer;
        double elapsed;
    public:
        timeCounter(){}

        void timeStart()
        {
            timer.start();
        }
        double timeStopinSec()
        {
            elapsed = timer.elapsed();
            elapsed /= 1000;
            return elapsed;
        }
        string timerDisplay()
        {
            return QDateTime::fromTime_t(timeStopinSec()).toUTC().toString("hh:mm:ss").toStdString();
        }
};

//// Camera Devices Info Utility : Get Camera name list
static QStringList getCamList()
{
    QStringList camList;
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    foreach (const QCameraInfo &cameraInfo, cameras)
    {
        camList += cameraInfo.description();
    }
    return camList;
}

//// get camera supported resolutions
static QStringList getCamResSize(const QString &camName)
{
    QStringList camResList;
    QCamera *camSelected;
    QList<QSize> camRes;
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();

    foreach (const QCameraInfo &cameraInfo, cameras) {
        if (cameraInfo.description() == camName)
        {
            camSelected = new QCamera(cameraInfo);
            camSelected->load();
            camRes = camSelected->supportedViewfinderResolutions();
        }
    }

    for (int i = 0; i < camRes.size(); ++i)
    {
        camResList += QString::number(camRes.at(i).width())+","
                        +QString::number(camRes.at(i).height());
    }
    camSelected->unload();
    delete camSelected;
    return camResList;
}

//// CLASS DATE TIME
class infoDateTime
{
    private:
        QDateTime dtInfo = QDateTime::currentDateTime();
        QString dateInfoFormat = "dd/MMM/yyyy";
        QString timeInfoFormat = "hh:mm:ss";
        QString dtInfoFormat = "dd/MMM/yyyy hh:mm:ss";
    public:
        string dateInfo,timeInfo,dateTimeInfo;
        infoDateTime(){}

        string getDateInfo()
        {
           return dtInfo.toString(dateInfoFormat).toStdString();
        }
        string getDateInfo(QString &dtFormat)
        {
           dateInfoFormat = dtFormat;
           return dtInfo.toString(dateInfoFormat).toStdString();
        }
        string getTimeInfo()
         {
             return dtInfo.toString(timeInfoFormat).toStdString();
         }
        string getTimeInfo(QString &dtFormat)
        {
            timeInfoFormat = dtFormat;
            return dtInfo.toString(timeInfoFormat).toStdString();
        }

        string getDateTimeInfo()
        {
           return dtInfo.toString(dtInfoFormat).toStdString();
        }
        string getDateTimeInfo(QString &dtFormat)
        {
           dtInfoFormat = dtFormat;
           return dtInfo.toString(dtInfoFormat).toStdString();
        }
};


///////////////////////// Class invole directory and file info //////////////////////////////////
class infoDirFile{
    private :
        QDir infoPath;
        QFileInfo infoFile;
        QString pathDir,charFile,formatfile;

    public :
        string absPath,nameFile,nameDir,extFile,fileSequence,parentDir,parentPath;
        QString fileSampling;
        int numFile;
        bool dirEmpty;
        bool dirExist;
        /// Constructor
        infoDirFile(){}
        infoDirFile(QString pathInput)
        {
            pathDir = QDir::fromNativeSeparators( pathInput );
            infoPath = QDir(pathInput);
            dirExist = infoPath.exists();
            infoPath.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot ); // Filter file in dir
            numFile = infoPath.count();    // get number of src files
            nameDir = infoPath.dirName().toStdString(); // Current folder name
            if(infoPath.cdUp())
            {
                parentDir = infoPath.dirName().toStdString();
                parentPath = infoPath.path().toStdString();
                infoPath.cd(pathDir);
            }
            if (numFile)
            {
                infoFile = infoPath.entryInfoList().at(0);  // Get info from first file.
                fileSampling  = infoPath.entryInfoList().at(0).fileName();  // get filename
                extFile = infoFile.suffix().toStdString();  // get file extension
                // extract character in filename string
                charFile =  fileSampling.split(QRegExp("(-?\\d+(?:[\\.,]\\d+(?:e\\d+)?)?)")).at(0);
                // format file for use in process sequence files.
                formatfile = QString::number((fileSampling.count() - (infoFile.suffix().count()+1)) - charFile.count());
                dirEmpty = false;
                setFileSequenceWithFormat();
            }
            else
            {
                cerr << "Directory is Empty" << endl;
                dirEmpty = true;
            }

        } ///- END CONSTRUCTOR

        // Method get first full file path
        string getFileName()
        {
            if (numFile)
            {
               QString str = QDir::fromNativeSeparators( pathDir )
                       + "/" + infoPath.entryInfoList().at(0).fileName();
               return  str.toStdString();
            }
            else
                cerr << "Directory is Empty, Can't get filename" << endl;
                return "";
        }
        // Method get full file path as order by i
        string getFileName(int i)
        {
            if (numFile)
            {
               QString str = QDir::fromNativeSeparators( pathDir )
                       + "/" + infoPath.entryInfoList().at(i).fileName();
               return  str.toStdString();
            }
            else
            {
                cerr << "Directory is Empty, Can't get filename ->"<< i << endl;
                return "";
            }
        }

        // Method get FULL sequence file format for opencv::VideoCapture
        void setFileSequenceWithFormat()
        {
            QString str = QDir::fromNativeSeparators( pathDir )
                               + "/" + charFile + "%0"+ formatfile +"d."+infoFile.suffix();
            fileSequence = str.toStdString();
        }

        bool isDirExist()
        {
            return dirExist;
        }
        bool isDirEmpty()
        {
            return dirEmpty;
        }
        string getDirFullPath()
        {
            return pathDir.toStdString()+ "/";
        }
        string getParentDir()
        {
            return parentDir + "/";
        }
        string getParentPath()
        {
            return parentPath + "/";
        }
        string genDir(const string dirName)
        {
            if (infoPath.mkdir( QString::fromStdString(dirName) ) )
                return dirName + "/";
            else
            {
                cerr << "Can't Generate directory" << endl;
                return "";
            }
        }
        static bool isFileExists(QString path) {
            QFileInfo checkFile(path);
            // check if file exists and if yes: Is it really a file and no directory?
            if (checkFile.exists() && checkFile.isFile())
            {
                return true;
            }
            else
            {
                return false;
            }
        }
};

class mediaInfo
{
    private:

    public:
        int framCount,frameRate,frameWidth,frameHeight;
        QString inputMedia;
        QString fileName,frameResolution,mediaType,fileExt,srcName;
        string path4cvCAP = "";
        bool isImage = false,isVideo = false;
        cv::Mat sampling;
        mediaInfo(){}
        mediaInfo(QString &src)
        {
            inputMedia = src;
            checkMediaType();

        }
        mediaInfo(string &src)
        {
            inputMedia = QString::fromStdString(src);
            checkMediaType();

        }
        void checkMediaType()
        {
            QFileInfo source(inputMedia);
            fileExt = source.suffix();
            /// Get info of Video file
            if(source.suffix() == "wmv"||source.suffix() == "avi" || source.suffix() == "mp4"|| source.suffix() == "mpg")
            {

                fileName = source.fileName();
                srcName = source.baseName();
                mediaType = "VIDEO";
                isVideo = true;
                isImage = false;
                cv::VideoCapture objInfo(inputMedia.toStdString());
                objInfo >> sampling;
                framCount = objInfo.get(cv::CAP_PROP_FRAME_COUNT);
                frameRate = objInfo.get(cv::CAP_PROP_FPS);
                frameWidth = objInfo.get(cv::CAP_PROP_FRAME_WIDTH);
                frameHeight = objInfo.get(cv::CAP_PROP_FRAME_HEIGHT);
                frameResolution = QString::number(frameWidth) + " X " + QString::number(frameHeight);
                path4cvCAP = inputMedia.toStdString();
                objInfo.release();

            }
            else if(source.suffix() == "jpg" || source.suffix() == "bmp"|| source.suffix() == "png")
            {

                fileName = source.fileName();
                mediaType = "IMAGE";
                isVideo = false;
                isImage = true;
                infoDirFile objInfo(source.absolutePath());
                srcName = QString::fromStdString(objInfo.parentDir);
                framCount = objInfo.numFile;
                sampling = cv::imread(inputMedia.toStdString());
                frameWidth = sampling.cols;
                frameHeight = sampling.rows;
                frameResolution = QString::number(frameWidth) + " X " + QString::number(frameHeight);
                path4cvCAP = objInfo.fileSequence;
            }
        }
        void getInfo(QString &src)
        {
            inputMedia = src;
            checkMediaType();
        }
};
//////////////////////// END CLASS INFODIRFILE /////////////////////////////////////////////////

// For READ & WRITE text file.  Future Convert to Non member function
class rwTxtFile{

    public:

        /// Read Text file and return to QStringList
        static int readTxt(QString &fname, QStringList &txtList)
        {

            QFile file(fname);
            if (!file.open(QFile::ReadOnly | QFile::Text))
            {
                std::cerr << "error opening output file\n";
                return EXIT_FAILURE;
            }
            else
            {
                QTextStream sIn(&file);

                while (!sIn.atEnd())
                    txtList += sIn.readLine();
            }
        }

        /// Overload Read Text file and skipline with flag
        static int readTxt(QString &fname, QStringList &txtList,QChar skipFlag)
        {

            QFile file(fname);
            if (!file.open(QFile::ReadOnly | QFile::Text))
            {
                std::cerr << "error opening output file\n";
                return EXIT_FAILURE;
            }
            else
            {
                QTextStream sIn(&file);

                while (!sIn.atEnd())
                {
                    QString tmpStr = sIn.readLine();
                    if(!tmpStr.startsWith(skipFlag,Qt::CaseInsensitive) && !tmpStr.isEmpty())
                        txtList += tmpStr;
                }
            }
        }

        /// Overload Read Text file and skipline with flag
//        static int readTxt(QString &fname, QMap<QString, QPoint> &outputMap,QChar skipFlag='#')
//        {

//            QFile file(fname);
//            if (!file.open(QFile::ReadOnly | QFile::Text))
//            {
//                std::cerr << "error opening output file\n";
//                return EXIT_FAILURE;
//            }
//            else
//            {
//                QTextStream sIn(&file);
//                int lineNo = 0;
//                while (!sIn.atEnd())
//                {
//                    QString tmpStr = sIn.readLine();
//                    QStringList strList = tmpStr.split(QRegExp("\\t|\\t\\t|\\t\\t\\t"));
//                    QString mapKey = strList.at(0)+"_"+QString::number(lineNo);
//                    QString tmpVal = strList.at(1);
//                    QStringList valList = tmpVal.split(',');
//                    QPoint p;
//                    tmpVal = valList.at(0);
//                    p.setX(tmpVal.toInt());
//                    tmpVal = valList.at(1);
//                    p.setY(tmpVal.toInt());
//                    if(!tmpStr.startsWith(skipFlag,Qt::CaseInsensitive) && !tmpStr.isEmpty())
//                        outputMap.insert(mapKey,p);

//                    lineNo++;
//                    if(lineNo == 3)
//                        lineNo = 0;
//                }
//            }
//        }

        /// Overload Read Text file and skipline with flag
        static int readTxtByRow(QString &fname, QMap<QString, QPoint> &outputMap,QChar skipFlag='#')
        {

            QFile file(fname);
            if (!file.open(QFile::ReadOnly | QFile::Text))
            {
                std::cerr << "error opening output file\n";
                return EXIT_FAILURE;
            }
            else
            {
                QTextStream sIn(&file);
                while (!sIn.atEnd())
                {
                    QString tmpStr = sIn.readLine();
                    /// Found data
                    if(!tmpStr.startsWith(skipFlag,Qt::CaseInsensitive) && !tmpStr.isEmpty()){
                        QStringList strList = tmpStr.split(QRegExp("\\t|\\t\\t|\\t\\t\\t"));
                        int columnNo = strList.size();
                        for (int i = 1; i < columnNo; i++){ /// first column is key
                            QString mapKey = strList.at(0)+"_"+QString::number(i);
                            QString tmpVal = strList.at(i);
                            QStringList valList = tmpVal.split(',');
                            QPoint p;
                            tmpVal = valList.at(0);
                            p.setX(tmpVal.toInt());
                            tmpVal = valList.at(1);
                            p.setY(tmpVal.toInt());
                            outputMap.insert(mapKey,p);
                        }
                    }
                }
            }
        }

        /// Overload Read Text file to QVector and skipline with flag
        static int readTxtByColumn(QString &fname, QVector<QVector<double>> &dataVec,QChar skipFlag='#')
        {

            QFile file(fname);
            if (!file.open(QFile::ReadOnly | QFile::Text))
            {
                std::cerr << "error opening output file\n";
                return EXIT_FAILURE;
            }
            else
            {
                QTextStream sIn(&file);
                int lineNo = 0;
                //QVector< QVector<double> > dataVec;
                while (!sIn.atEnd())
                {
                    QString tmpStr = sIn.readLine();
                    QStringList strList = tmpStr.split( QRegExp("\\t|\\t\\t|\\t\\t\\t") );

                    if(lineNo == 0){
                         dataVec.resize(strList.size());
                    }
                    for(int i = 0; i < strList.size();i++){
                        double dn = strList.at(i).toDouble();
                        dataVec[i].insert(lineNo,dn);
//                        qDebug()<<strList.at(i).toDouble();
                    }

//                    if(!tmpStr.startsWith(skipFlag,Qt::CaseInsensitive) && !tmpStr.isEmpty())
//                        outputMap.insert(mapKey,p);

                    lineNo++;
                }
            }
        }

        // Write Text file with QStringList With flag
        static int writeTxt(QString &fname, QStringList &txtList, bool &newLine)
        {
            QFile file(fname);
            if (!file.open(QFile::Append | QFile::Text))
            {
                std::cerr << "error opening output file\n";
                return EXIT_FAILURE;
            }
            else
            {
                QTextStream stream(&file);
                for (int i = 0; i < txtList.size(); ++i)
                {
                    if(newLine)
                        stream << txtList.at(i) <<'\t' << '\t';
                    else
                        stream << txtList.at(i)<< '\n';
                }
                stream << '\n';
                stream.flush();
                file.close();
            }
            return 0;
        }

        // Overloaded Write Text file with QStringList With flag
        static int writeTxt(string &fnamestr, QStringList &txtList, bool &newLine)
        {
            QString fname = QString::fromStdString(fnamestr);
            QFile file(fname);
            if (!file.open(QFile::Append | QFile::Text))
            {
                std::cerr << "error opening output file\n";
                return EXIT_FAILURE;
            }
            else
            {
                QTextStream stream(&file);
                for (int i = 0; i < txtList.size(); ++i)
                {
                    if(newLine)
                        stream << txtList.at(i) <<'\t' << '\t';
                    else
                        stream << txtList.at(i)<< '\n';
                }
                stream << '\n';
                stream.flush();
                file.close();
            }
            return 0;
        }

        // Write Text file with  QMap<QString, QString>
        static int writeTxt(QString &fname, QMap<QString, QString> &txtList, bool &newLine)
        {
            QFile file(fname);
            if (!file.open(QFile::Append | QFile::Text))
            {
                std::cerr << "error opening output file\n";
                return EXIT_FAILURE;
            }
            else
            {
                QTextStream stream(&file);
                QMapIterator<QString, QString> i(txtList);
                while (i.hasNext()) {
                    i.next();
                    if(newLine)
                        stream << i.key() << i.value() << '\n';
                    else
                        stream << i.value() << '\t'<<'\t';
                }
                stream << '\n';
                stream.flush();
                file.close();
                return 0;
            }
        }

        // Overload Write Text file with QMap<QString, QVariant>
        static int writeTxt(QString &fname, QMap<QString, QVariant> &txtList, bool &newLine)
        {
            QFile file(fname);
            if (!file.open(QFile::Append | QFile::Text))
            {
                std::cerr << "error opening output file\n";
                return EXIT_FAILURE;
            }
            else
            {
                QTextStream stream(&file);
                QMapIterator<QString, QVariant> i(txtList);
                QString mapValue;
                while (i.hasNext()) {
                    i.next();

                    if(i.value().type() == QVariant::Double)
                        mapValue = QString::number(i.value().toDouble(),'f',3);
                    else
                        mapValue = i.value().toString();

                    if(newLine)
                        stream << '\t' << i.key() << " = " << mapValue << '\n';
                    else
                        stream << mapValue << '\t'<<'\t';
                }
                stream << '\n';
                stream.flush();
                file.close();
                return 0;
            }
        }

        // Overload Write Text file with QMap<int, double>
        static int writeTxt(QString &fname, QMap<int, double> &txtList)
        {
            QFile file(fname);
            if (!file.open(QFile::Append | QFile::Text))
            {
                std::cerr << "error opening output file\n";
                return EXIT_FAILURE;
            }
            else
            {
                QTextStream stream(&file);
                QMapIterator<int, double> i(txtList);
                QString mapValue;
                while (i.hasNext()) {
                    i.next();

                        mapValue = QString::number(i.value(),'f',3);

                        stream << i.key() << '\t' << mapValue << '\n';

                }

                stream.flush();
                file.close();
                return 0;
            }
        }

        // Overload Write Text file with cv::Mat
        // Use first column as index
        static int writeTxt(QString &fname, cv::Mat &txtList)
        {
            QFile file(fname);
            if (!file.open(QFile::Append | QFile::Text))
            {
                std::cerr << "error opening output file\n";
                return EXIT_FAILURE;
            }
            else
            {
                QTextStream stream(&file);
                QString mapValue;

                for(int i = 0;i<txtList.rows;i++){
                    /// Write Left header#
                    //stream << QString::number(i) << '\t';
                    /// Access column element
                    for(int k = 0; k<txtList.row(0).cols;k++){
                        mapValue = QString::number(txtList.row(i).at<double>(k));
                        if( k != txtList.row(0).cols-1) /// write each column
                            stream << mapValue << '\t';
                        else
                            stream << mapValue;         /// write lastest column
                    }
                    stream << '\n';
                }

                stream.flush();
                file.close();
                return 0;
            }
        }
};

class evalDetection{
    private:
        long frameNo = 0;
        QString tmpDir = QDir::tempPath()+"/temp.sav";
        bool exportFlag = true;
        QMap<QString, QVariant> paramList;
        QString srcDir,gtDir,targetDir,methodName="";
        QString testCaseName,evalDate;
        string srcPath4cvCAP,gtPath4cvCAP;
        int frameCount = 0;
        int processedFPS = -1;
        QStringList evalListDat;
        QSize srcRes;

        double GTP=0.0,GTN=0.0,TP=0.0,TN=0,FP=0.0,FN=0.0;
        double TPR=0.0,TNR=0.0,FPR=0.0,FNR=0.0,ACCR=0.0;
        double RE=0.0,SP=0.0,PR=0.0,PWC=0.0,FM=0.0,PCC=0.0;
        double FPR_avg=0.0,FNR_avg=0.0,RE_avg=0.0,SP_avg=0.0,
        PR_avg=0.0,PWC_avg=0.0,FM_avg=0.0,PCC_avg=0.0;
        double FPR_w=0.0,FNR_w=0.0,RE_w=0.0,SP_w=0.0,
        PR_w=0.0,PWC_w=0.0,FM_w=0.0,PCC_w=0.0;
    public:
        //Default Constructor
        evalDetection(){}

        // Constructor
        evalDetection(QString &src,QString &gt,QString &res, bool &flag){
            infoDirFile getSrcDirName(src);
            methodName = QString::fromStdString(getSrcDirName.nameDir);
            setSrcDir(src);
            setGtDir(gt);
            setOutputDir(res);
            exportFlag = flag;
        }
        // Constructor
        evalDetection(QString &src,QString &gt,QString &res,QString &method, bool &flag){
            methodName = method;
            setSrcDir(src);
            setGtDir(gt);
            setOutputDir(res);
            exportFlag = flag;
        }
        // Option Constructor Write result frame-by-frame
        evalDetection(QString &src,QString &gt,QString &res, QMap<QString, QVariant>&optionData){
            methodName = optionData.value("methodName").toString();
            processedFPS = optionData.value("processedFPS").toInt();
            paramList = optionData.value("paramList").toMap();
            exportFlag = optionData.value("evalAllFrames").toBool();
            setSrcDir(src);
            setGtDir(gt);
            setOutputDir(res);
        }
        void setSrcDir(QString &inputSrcDir)
        {
            srcDir = inputSrcDir;
        }
        void setGtDir( QString &inputGtDir)
        {
            gtDir = inputGtDir;
        }
        void setOutputDir(QString &inputTargetDir)
        {
            infoDateTime dtInfo;
            QString tFormat = "d_M_yy_h_m";
            targetDir = inputTargetDir+"/Results_"
                +QString::fromStdString(dtInfo.getDateTimeInfo(tFormat))
                    +"_"+methodName+".txt";
        }

        bool isSameSet()
        {
            infoDirFile src(srcDir);
            infoDirFile gt(gtDir);
            QString srcSampling = QString::fromStdString(src.getFileName() );
            QString gtSampling = QString::fromStdString(gt.getFileName() );

            mediaInfo srcInfo( srcSampling );
            mediaInfo gtInfo( gtSampling );
            infoDateTime dtInfo;
            if(srcInfo.isImage)
            {
                if(srcInfo.framCount == gtInfo.framCount &&
                        srcInfo.fileExt == gtInfo.fileExt &&
                        srcInfo.frameWidth == gtInfo.frameWidth &&
                        srcInfo.frameHeight == gtInfo.frameHeight)
                {
                    srcPath4cvCAP = srcInfo.path4cvCAP;
                    gtPath4cvCAP = gtInfo.path4cvCAP;
                    frameCount = srcInfo.framCount;
                    testCaseName = QString::fromStdString( gt.parentDir );
                    evalDate = QString::fromStdString( dtInfo.getDateTimeInfo() );
                    srcRes.setWidth(srcInfo.frameWidth);
                    srcRes.setHeight(srcInfo.frameHeight);
                    return true;
                }
            }

            std::cerr << "Source and Groundtruth not match" << endl;
            return false;
        }
    void compute(const cv::Mat &test,const cv::Mat &ref)
    {
        cv::Mat srcFrame,gtFrame,tmp;
        cv::Mat invSrc,invGt,invGtP;

        if (test.channels() == 3 || ref.channels() == 3)
        {
           cv::cvtColor(test,srcFrame,CV_BGR2GRAY);
           cv::cvtColor(ref,gtFrame,CV_BGR2GRAY);
        }
        else
        {
            srcFrame = test;
            gtFrame = ref;
        }
        // GT Pixels
        GTP = countNonZero(gtFrame);
        cv::bitwise_not(gtFrame,invGtP);
        GTN = countNonZero(invGtP);

        // True Positive Pixels
        cv::bitwise_and(srcFrame,gtFrame,tmp);
        TP = cv::countNonZero(tmp);
        TP = GTP ? TP/GTP : -1;

        /// True Negative Pixels
        cv::bitwise_not(srcFrame,invSrc);
        cv::bitwise_not(gtFrame,invGt);
        cv::bitwise_and(invSrc,invGt,tmp);
        TN = cv::countNonZero(tmp);
        TN = GTN ? TN/GTN : -1;

        /// False Positive Pixels
        cv::bitwise_not(gtFrame,invGt);
        cv::bitwise_and(invGt,srcFrame,tmp);
        FP = cv::countNonZero(tmp);
        FP = GTN ? FP/GTN : -1;

        /// False Negative Pixels
        cv::bitwise_not(srcFrame,invSrc);
        cv::bitwise_and(gtFrame,invSrc,tmp);
        FN = cv::countNonZero(tmp);
        FN = GTP ? FN/GTP : -1;

        FPR = (FP + TN) ? FP / (FP + TN) : -1;   /// False Positive Rate
        FNR = (TP + FN) ? FN / (TP + FN) : -1;   /// False Negative Rate
        PWC = (TP + FN + FP + TN) ? (FN + FP) / (TP + FN + FP + TN) *100 : -1;    /// % of Wrong Classifications
        PCC = (TP + FN + FP + TN) ? (TP + TN) / (TP + FN + FP + TN) *100 : -1;   /// % of True Classifications
        RE = (TP + FN) ? TP / (TP + FN) : -1;    /// Recall
        SP = (TN + FP) ? TN / (TN + FP) : -1;    /// Specificity
        PR = (TP + FP) ? TP / (TP + FP) : -1;    /// Precision
        FM = (PR + RE) ? (2 * PR * RE) / (PR + RE) : -1;  /// F-Measure

        //// Keep result to QStringList
        evalListDat.clear();
        evalListDat << QString::number(frameNo+1)
                    << QString::number(FPR,'f',3)
                    << QString::number(FNR ,'f',3)
                    << QString::number(PWC ,'f',3)
                    << QString::number(PCC,'f',3)
                    << QString::number(RE ,'f',3)
                    << QString::number(SP ,'f',3)
                    << QString::number(PR ,'f',3)
                    << QString::number(FM,'f',3);

        //// Keep only computeable values and counting for final average
        (FPR > -1) ? FPR_avg+=FPR,  FPR_w++ : FPR_avg*=1,  FPR_w*=1;
        (FNR > -1) ? FNR_avg+=FNR,  FNR_w++ : FNR_avg*=1,  FNR_w*=1;
        (RE > -1)  ? RE_avg+=RE,    RE_w++  : RE_avg*=1,    RE_w*=1;
        (SP > -1)  ? SP_avg+=SP,    SP_w++  : SP_avg*=1,    SP_w*=1;
        (PR > -1)  ? PR_avg+=PR,    PR_w++  : PR_avg*=1,    PR_w*=1;
        (PWC > -1) ? PWC_avg+=PWC,  PWC_w++ : PWC_avg*=1,  PWC_w*=1;
        (PCC > -1) ? PCC_avg+=PCC,  PCC_w++ : PCC_avg*=1,  PCC_w*=1;
        (FM > -1)  ? FM_avg+=FM,    FM_w++  : FM_avg*=1,    FM_w*=1;
    }

    ///////////////// Evaluation Detection /////////////////
    int evalPerf()
    {
        if (isSameSet() )
        {
            cv::VideoCapture srcCap(srcPath4cvCAP);
            cv::VideoCapture gtCap(gtPath4cvCAP);

            if (!srcCap.isOpened()|| !gtCap.isOpened())
            {
                return -1;
            }
           bool stop(false);

       /////////////////////////////////////////////////////////////////////////////

           // for all frames in video
           while (!stop)
           {

               cv::Mat testFrame,refFrame,srcFrame,gtFrame,resultFrame;
               testFrame = 0; refFrame = 0;


               // read next frame if any
               if (!srcCap.read(testFrame) || !gtCap.read(refFrame)){
                   break;
               }

               // Convert Input to gray
               if (testFrame.channels() == 3 || refFrame.channels() == 3)
               {
                  cv::cvtColor(testFrame,srcFrame,CV_BGR2GRAY);
                  cv::cvtColor(refFrame,gtFrame,CV_BGR2GRAY);
               }
               else
               {
                   srcFrame = testFrame;
                   gtFrame = refFrame;
               }

               /////////// PROCESSING /////////////////

                compute(testFrame,refFrame);
                if(exportFlag)
                {

                    /// Write frame-by-frame to temp file
                    bool newLine = true;
                    rwTxtFile::writeTxt(tmpDir,evalListDat,newLine);

                }

               /// counting frame
               frameNo++;
               // introduce a delay or press key to stop
               if (frameNo == frameCount)
                   stop= true;

           } // END WHILE

           // Conclusion of Performance average of dataset
           FPR_avg = (FPR_avg / FPR_w)*100;
           FNR_avg = (FNR_avg / FNR_w)*100;
           PWC_avg = (PWC_avg / PWC_w);
           PCC_avg = (PCC_avg / PCC_w);
           RE_avg = (RE_avg / RE_w)*100;
           SP_avg = (SP_avg / SP_w)*100;
           PR_avg = (PR_avg / PR_w)*100;
           FM_avg = (FM_avg / FM_w);

            srcCap.release();
            gtCap.release();

            //// Result Conclusion
            evalListDat.clear();
            evalListDat << QString::number(frameCount)
                        << QString::number(FPR_avg)
                        << QString::number(FNR_avg)
                        << QString::number(PWC_avg)
                        << QString::number(PCC_avg)
                        << QString::number(RE_avg)
                        << QString::number(SP_avg)
                        << QString::number(PR_avg)
                        << QString::number(FM_avg);


            //// EXPORT OUTPUT
            if(exportFlag)
            {
                /// HEADER File
                QMap<QString,QString> headerMeta,skipLine;
                headerMeta.insert("1. Evaluate Test-case name : ",testCaseName);
                headerMeta.insert("2. Evaluated Date : ",evalDate);
                headerMeta.insert("3. Ground-Truth directory : ",gtDir);
                headerMeta.insert("4. Source directory : ",srcDir);
                headerMeta.insert("5. Resolution : ",QString::number(srcRes.width())
                                  +" x "+QString::number(srcRes.height()) );
                headerMeta.insert("6. Method : ",methodName);
                headerMeta.insert("7. Processed FPS : ",QString::number(processedFPS));
                headerMeta.insert("8. Used parameters : ","");

                bool newLine = true;
                rwTxtFile::writeTxt(targetDir,headerMeta,newLine);

                /// List of Used parameters
                rwTxtFile::writeTxt(targetDir,paramList,newLine);

                /// HEADER Conclusion
                QMap<QString,QString> header;
                header.insert("0","Frames");
                header.insert("1","FPR");
                header.insert("2","FNR");
                header.insert("3","PWC");
                header.insert("4","PCC");
                header.insert("5","RE");
                header.insert("6","SP");
                header.insert("7","PR");
                header.insert("8","FM");

                newLine = false;
                rwTxtFile::writeTxt(targetDir,header,newLine);


                //// Result Conclusion
                newLine = true;
                rwTxtFile::writeTxt(targetDir,evalListDat,newLine);
                rwTxtFile::writeTxt(targetDir,skipLine,newLine);

                /// Results Frame by Frame
                evalListDat.clear();
                rwTxtFile::readTxt(tmpDir,evalListDat);
                newLine = false;
                rwTxtFile::writeTxt(targetDir,evalListDat,newLine);
                QFile::remove(tmpDir);
            }

            qDebug()<<"FINISH";
            return 0;

        }   /// END IF
        else
            return -1;

    } /// END EVALPERF
    ///////////////// END EVALDET /////////////////
};

//// Read and write data with cvStorage Object
class rwXMLFile{

    private:
        QFileInfo fileName;
        QDomDocument doc;
        QFile file;
        QDomElement root;
        QDomElement element;
        bool fileState = true;

        bool checkFileOpen()
        {
            // check QFile can open
            if (!file.open(QIODevice::ReadWrite))
            {
                std::cerr << "error opening output file\n";
                QMessageBox msgBox;
                msgBox.setIcon(QMessageBox::Critical);
                msgBox.setText("error opening output file");
                msgBox.exec();
                return fileState = false;
            }
            qDebug() << "File open OK";
            return fileState = true;
        }

        bool checkFileParse()
        {
            // if can open then check Parse file
            if (!doc.setContent(&file))
            {
                QMessageBox msgBox;
                msgBox.setIcon(QMessageBox::Critical);
                msgBox.setText("error can't parse file");
                msgBox.exec();
                return fileState = false;
             }

            qDebug() << "File parsing OK";
            return fileState = true;
        }

    public:
        rwXMLFile(QString &fname):fileName(fname),file(fname)
        {
            // get filename based

            // create QDomDocument // create QFile
            doc = QDomDocument(fileName.baseName());
            // Check file status
            checkFileOpen();
        }

        /// overload for one parent node
        void readXMLFile(QMap<QString, QVariant> &outputData)
        {

            if (fileState && checkFileParse()) // check file ready
            {
                element = doc.documentElement();

                for(QDomNode n = element.firstChild(); !n.isNull(); n = n.nextSibling())
                {
                    QDomElement childElement = n.toElement();
                    if( txtIsDouble(childElement.text()) )
                        outputData[childElement.tagName()] = childElement.text().toDouble();
                    else
                        outputData[childElement.tagName()] = childElement.text().toInt();
                }

                file.close();
                //return fileState = true;
            }

            //return fileState = false;
        }

        void writeXMLFile(QMap<QString, QVariant> &inputData)
        {
            cv::FileStorage fs(fileName.absoluteFilePath().toStdString(), cv::FileStorage::WRITE);

            QMapIterator<QString, QVariant> i(inputData);
            while (i.hasNext())
            {

                i.next();
                if(i.value().type() == QVariant::Double)
                    fs << i.key().toStdString() << i.value().toDouble();

                else
                    fs << i.key().toStdString() << i.value().toInt();

            }

            fs.release();
        }
};

//// Sliding Window Operation, return vector of block window
class slidingWindow{
private:
    vector<Rect> rects;

public:
    int nRows = 0, nCols = 0;
    vector<Rect> getSlidingWindow(Mat& image,int winSize, int step = 1)
    {
      int winWidth = winSize;
      int winHeight = winSize;

      for(int i=0;i<image.rows;i+=step)
      {
          if((i+winHeight)>image.rows){
              nRows = i;
              break;
          }
          for(int j=0;j< image.cols;j+=step){
              if((j+winWidth)>image.cols){
                  nCols = i;
                  break;
              }

              Rect rect(j,i,winWidth,winHeight);
              rects.push_back(rect);
          }
      }
      return rects;
    }
    Rect getWindowRect(Mat& image, int winSize, QPoint p)
    {
        int rad = winSize/2;
        Rect rect;
        if ( p.x()+rad < image.rows && p.y()+rad < image.cols
             && p.x()-rad >-1 && p.y()-rad > -1 ){

            Rect tm(p.x()-rad,p.y()-rad,winSize,winSize);
            rect = tm;
        }
        /// window Heigher than image
        else if (p.x()+rad > image.rows && p.y()+rad < image.cols
                 && p.x()-rad >-1 && p.y()-rad > -1){
            int newHeight = winSize - ( ( p.x()+rad )-image.rows );
            Rect tm(p.x()-rad,p.y()-rad,winSize,newHeight);
            rect = tm;
        }
        /// window Wider than image
        else if (p.x()+rad < image.rows && p.y()+rad > image.cols
                 && p.x()-rad >-1 && p.y()-rad > -1){
            int newWidth = winSize - ( ( p.x()+rad )-image.cols );
            Rect tm(p.x()-rad,p.y()-rad,newWidth,winSize);
            rect = tm;
        }
        return rect;
    }

};

static string getDirNamebyLevel(string &strPath, int level){
    QString pathInput = QString::fromStdString(strPath);
    QStringList strList = pathInput.split('/');
    pathInput = strList.at(level-1);
    return pathInput.toStdString();
}

static bool mkDirByString(string &strPath){
    QString dirName = QString::fromStdString(strPath);
    QDir tmp(dirName);
    if(!tmp.exists())
        return tmp.mkdir(dirName);
    else
        return true;
}

static bool mkDirByString(QString &dirName){
    QDir tmp(dirName);
    if(!tmp.exists())
        return tmp.mkdir(dirName);
    else
        return true;
}

static double getNumberFromString(const QString &xString)
{
  //QString xString = QString::fromStdString(str);
  QRegExp xRegExp("(-?\\d+(?:[\\.,]\\d+(?:e\\d+)?)?)");
  xRegExp.indexIn(xString);
  QStringList xList = xRegExp.capturedTexts();
  if (true == xList.empty())
  {
    return 0.0;
  }
  QString tm = xList.at(0);
  return tm.toDouble();;
}
//// Function to compute Global contrast factor-a new approach to image contrast"
/// (Matkovic, Kresimir et al., 2005)

static double getGCF(Mat &im){

//    // 9 different resolution levels
//    double GCF = 0.0;

//    vector<int> resolutions{1, 2, 4, 8, 16, 25, 50, 100, 200};
//    vector<double> LC(resolutions.size(),0);
//    vector<double> c(resolutions.size(),0);
//    vector<double> w(resolutions.size(),0);

//    int W = im.cols;
//    int H = im.rows;

//    Mat rIm;// = im;
//    im.convertTo(rIm,CV_64F);

//    for (int i = 0; i < resolutions.size(); ++i )
//    {

//        //attempt at resizing as in the paper
//        if (i > 0)
//        {
////          rIm = imresize(im, im.rows*1/(2^(i-1)),im.cols*1/(2^(i-1)), 'bilinear');
//          cv::resize(im,rIm,im.size()*1/(2^(i)) );
//        }

//        W = rIm.cols;
//        H = rIm.rows;

//        Mat rL = Mat(rIm.size(), CV_64F, double(0));

//        // compute linear luminance l
//        Mat l = Mat(rIm.size(), CV_64F, double(0));
//            l = (rIm/255) * 2.2;

//        // compute perceptual luminance L
//        //rL = 100 * sqrt(l);
//            clog<<l.type() <<"-" << rL.type() << endl;
//        //cv::sqrt(l,rL);
//        rL *= 100;
//        // compute local contrast for each pixel
//        double lc = 0.0;

//        for (int x = 0; x < H; ++x)
//        {
//            for (int y = 0; y < W; ++y)
//            {
//                if ((x == 0) && (x == H))
//                {
//                    if ((y == 0) && (y == W))
//                       lc = lc + 0;
//                    else if (y == 0)
//                       lc = lc + abs(rL.at<double>(x, y) - rL.at<double>(x,y+1));
//                    else if (y == W)
//                        lc = lc + abs(rL.at<double>(x, y) - rL.at<double>(x,y-1));
//                    else
//                        lc = lc + ( abs(rL.at<double>(x, y) - rL.at<double>(x,y-1)) +
//                                abs(rL.at<double>(x, y) - rL.at<double>(x,y+1)) )/2;
//                }

//                else if (x == 0)
//                {
//                    if ((y == 0) && (y == W))
//                        lc = lc + abs(rL.at<double>(x, y) - rL.at<double>(x+1,y));
//                    else if (y == 0)
//                        lc = lc + ( abs(rL.at<double>(x, y) - rL.at<double>(x,y+1)) +
//                                abs(rL.at<double>(x, y) - rL.at<double>(x+1,y)) )/2;
//                    else if (y == W)
//                        lc = lc + ( abs(rL.at<double>(x, y) - rL.at<double>(x,y-1)) +
//                                abs(rL.at<double>(x, y) - rL.at<double>(x+1,y)) )/2;
//                    else
//                        lc = lc + ( abs(rL.at<double>(x, y) - rL.at<double>(x,y-1)) +
//                                abs(rL.at<double>(x, y) - rL.at<double>(x,y+1)) +
//                                abs(rL.at<double>(x, y) - rL.at<double>(x+1,y)) )/3;
//                }

//                else if (x == H)
//                {
//                    if ((y == 0) && (y == W))
//                        lc = lc + abs(rL.at<double>(x, y) - rL.at<double>(x-1,y));
//                    else if (y == 0)
//                        lc = lc + ( abs(rL.at<double>(x, y) - rL.at<double>(x,y+1)) +
//                                abs(rL.at<double>(x, y) - rL.at<double>(x-1,y)) )/2;
//                    else if (y == W)
//                        lc = lc + ( abs(rL.at<double>(x, y) - rL.at<double>(x,y-1)) +
//                                abs(rL.at<double>(x, y) - rL.at<double>(x-1,y)) )/2;
//                    else
//                        lc = lc + ( abs(rL.at<double>(x, y) - rL.at<double>(x,y-1)) +
//                                    abs(rL.at<double>(x, y) - rL.at<double>(x,y+1)) +
//                                    abs(rL.at<double>(x, y) - rL.at<double>(x-1,y)) )/3;
//                }
//                else // x > 1 && x < H
//                {
//                    if ((y == 0) && (y == W))
//                        lc = lc + ( abs(rL.at<double>(x, y) - rL.at<double>(x+1,y)) +
//                                abs(rL.at<double>(x, y) - rL.at<double>(x-1,y)) )/2;
//                    else if (y == 0)
//                        lc = lc + ( abs(rL.at<double>(x, y) - rL.at<double>(x,y+1)) +
//                                    abs(rL.at<double>(x, y) - rL.at<double>(x+1,y)) +
//                                    abs(rL.at<double>(x, y) - rL.at<double>(x-1,y)) )/3;
//                    else if (y == W)
//                        lc = lc + ( abs(rL.at<double>(x, y) - rL.at<double>(x,y-1)) +
//                                    abs(rL.at<double>(x, y) - rL.at<double>(x+1,y)) +
//                                    abs(rL.at<double>(x, y) - rL.at<double>(x-1,y)) )/3;
//                    else
//                        lc = lc + ( abs(rL.at<double>(x, y) - rL.at<double>(x,y-1)) +
//                                    abs(rL.at<double>(x, y) - rL.at<double>(x,y+1)) +
//                                    abs(rL.at<double>(x, y) - rL.at<double>(x-1,y)) +
//                                    abs(rL.at<double>(x, y) - rL.at<double>(x+1,y)) )/4;
//                }

//            }
//        }

//        /// compute average local contrast c
//        c.at(i) = lc/(W*H);
//        w.at(i) = (-0.406385*(i/9)+0.334573)*(i/9)+ 0.0877526;

//        /// compute global contrast factor
//        LC.at(i) = c.at(i)*w.at(i);
//        GCF = GCF + LC.at(i);

//    }   /// END FOR


//    return GCF;
}

#endif // MIVUTTIL

