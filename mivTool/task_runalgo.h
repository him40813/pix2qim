#ifndef TASK_RUNALGO_H
#define TASK_RUNALGO_H

// QT Library
#include <QMainWindow>
#include <QStackedWidget>
#include <QComboBox>
#include <QWidget>
#include <QtGui>
#include <QPushButton>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QListWidget>
#include <QSpinBox>
#include <QMessageBox>
#include <QMap>
#include <QObject>
#include <QObjectList>
#include <QRegExp>
#include <QFileDialog>
#include <QCameraInfo>

// External Library
//#include "mivvidprocessor.h"
#include "vidprocessor.h"
#include "mivbgslib.h"
#include "mivuttil.h"
#include "miv2xml.h"
#include "dynamicwidget.h"
#include <typeinfo>

namespace Ui {
class task_RunAlgo;
}

class task_RunAlgo : public QWidget
{
    friend class MainWindow;
    Q_OBJECT

public:
    explicit task_RunAlgo(QWidget *parent = 0);
    ~task_RunAlgo();

    enum taskType {doPreview,doProcess };
    taskType doTask;
    enum evaluateMode {evalNone, evalOnfly, evalExist};
    evaluateMode evalModeSelected;

private slots:
    void on_selAlgo_itemClicked();

    void on_btnProcess_clicked();

    void on_btnLoadDefaultConfig_clicked();

    void on_browse_inputSource_clicked();

    void on_saveImageFormat_clicked();

    void on_browse_gtDir_clicked();

    void on_browse_resultDir_clicked();

    void on_stepB_clicked();

    void on_pPB_clicked();

signals:
    void uiState();
    void taskState(int task);
private:

    //// TEMP FOR DEBUG
    int v = 99;
    int tmp();
    QString srcTEMPPATH = INPUTDIR;
    ////

    Ui::task_RunAlgo *ui;
    cv::Ptr<miv::dynamicWidget> paramWid;
    QGridLayout *gridLayout;
    QMap<QString, QVariant> paramList;    // Store Parameters on fly
    QMap<QString, QVariant> evalOptionData;
    cv::Ptr<IBGS> algoProcessor;
    cv::Mat samplingFrame;
    mediaInfo inputInfo;
    void widgetIni();
    int videoProcessor();

    void loadParam2UI();
    void saveParamConfig();
    void evaluateResults();
    void makeMethodProcessor(); // Instantiate Method for Processing by name
    void getSrc2cvCAP();  // Determine video or camera for videoProcess Module
    void broadCastSignal();
    void taskMng(int task);
    void saveImageOutput();
    void getSaveImageFormat();
    void getSaveImageOutputPath();
    int processedFPS;
    int camID;
    cv::Size_<int> resSize;
    bool isProcess;   // process or not flag
    bool firstRun;
    bool isSaveImageOutput;
    bool isEval;
    bool evalOutput;

    string methodString;  // Method for process
    string saveImageOutputFormat = "bmp";   // Image output format
    string saveImageOutputPath; // Image output saving path
//    string configParamFileName = "defaultConfigBGSLib.xml";
    string bgsLibConfigPath = "./config/";
    string absSaveImageOutputPath;  // Save Dir return from video processor
    QString dialogGetDir(QString dialogTxt);
    QString tempDirPath = QDir::tempPath()+"/";
    QString paramFilePath;
    QString msgStatus;
    QString configDirPath = CONFIGDIR;
    QVariant src2cvCAP;
    enum paramMode{loadDefault, loadRecent};
    paramMode useParam;
    enum srcType {vidFile, vidCam};
    srcType useSrc;
    cv::Ptr<miv::vidProcessor> processor;
};

#endif // TASK_RUNALGO_H
