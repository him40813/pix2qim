#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QtGui>
#include <QApplication>
#include <QMainWindow>
#include "task_runalgo.h"
#include "task_extractframe.h"
#include "task_evaluate.h"

// External Library
//#include "mivvidprocessor.h"
#include "vidprocessor.h"
#include "mivbgslib.h"
#include "mivuttil.h"
#include "miv2xml.h"
#include "dynamicwidget.h"

#include <typeinfo>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    //// TEMP FOR DEBUG
    QString srcTEMPPATH = INPUTDIR;
    ////

    Ui::MainWindow *ui;
    cv::Ptr<task_RunAlgo>runAlgoUI = new task_RunAlgo;
    cv::Ptr<task_ExtractFrame>extractUI = new task_ExtractFrame;
    cv::Ptr<task_Evaluate>evalUI = new task_Evaluate;

    QWidget *runTask; //= new task_RunAlgo;
    QWidget *extractTask; //= new QWidget;
    QWidget *evaluateTask; //= new QWidget;

    mediaInfo inputInfo;

    void toggleUI();
    void getSrc2cvCAP();

    void getCurrentTask();
    QVariant src2cvCAP;

    int camID;
    cv::Size_<int> resSize;

    enum srcType {vidFile, vidCam};
    srcType useSrc;
    enum taskType {doPreview,doProcess, doExtract, doEval};
    taskType doTask;


signals:
    void uiState();
    void taskState(int task);

private slots: 

    void on_inputSrcType_currentChanged(int index);
    void on_btnPreview_clicked();
    void on_camListBox_currentIndexChanged(const QString &arg1);
    void on_camResBox_currentIndexChanged(const QString &arg1);
    void browseInput_clicked();


};

#endif // MAINWINDOW_H
