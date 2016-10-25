#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_task_runalgo.h"
#include "ui_task_extractframe.h"
#include "ui_task_evaluate.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QVBoxLayout *toolLayout = new QVBoxLayout;
    QTabWidget *tabTask = new QTabWidget;
    toolLayout->addWidget(tabTask);
    ui->toolWidget->setLayout(toolLayout);

    runTask = static_cast<QWidget*>(runAlgoUI);
    extractTask = static_cast<QWidget*>(extractUI);
    evaluateTask = static_cast<QWidget*>(evalUI);

    tabTask->insertTab(0,runTask,"Run Algorithm");
    tabTask->insertTab(1,extractTask,"Extract Tool");
    tabTask->insertTab(2,evaluateTask,"Evaluate Tool");

    /// Selecting Input Occur
    connect( ui->browseInput,&QPushButton::clicked,this,&MainWindow::browseInput_clicked );
    /// Processor UI workflow
    connect( runAlgoUI,&task_RunAlgo::uiState ,this,&MainWindow::toggleUI );
    /// Mainwindow UI workflow
    connect( this,&MainWindow::uiState,this,&MainWindow::toggleUI );
    ///
    connect( this,&MainWindow::taskState,runAlgoUI,&task_RunAlgo::taskMng );
    useSrc = vidFile;

    /// Get Camera List to UI
    ui->camListBox->addItems( getCamList() );

    emit uiState();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_inputSrcType_currentChanged(int index)
{
    switch (index )
    {
        case 0:
            useSrc = vidFile;
        break;
        case 1:
            useSrc = vidCam;
        break;
    }
    getCurrentTask();
    emit uiState();
}

void MainWindow::browseInput_clicked()
{
    QString inputSource = QFileDialog::getOpenFileName(this, tr("Selecting Source"),srcTEMPPATH);
    if (!inputSource.isEmpty())
    {
        inputInfo.getInfo(inputSource);    // get media info
        doTask = doProcess;
        emit uiState();
    }

    else
        clog<<"No source select"<<endl;
}

//// Get Input Source
void MainWindow::getSrc2cvCAP()
{
    switch(useSrc)
    {
        case vidFile:
            if(inputInfo.path4cvCAP != "")
                src2cvCAP = QString::fromStdString(inputInfo.path4cvCAP);
            else
                src2cvCAP.clear();
        break;
        case vidCam:
            src2cvCAP = camID;
        break;
    }
    runAlgoUI->src2cvCAP.clear();
    runAlgoUI->src2cvCAP = src2cvCAP;
    extractUI->src2cvCAP.clear();
    extractUI->src2cvCAP = src2cvCAP;
}

void MainWindow::on_btnPreview_clicked()
{
    emit taskState(0);

}

//void MainWindow::tabTask_currentChanged(int index)
//{
//    index += 1;
//    switch(index)
//    {
//    case 1:
//        doTask = doProcess;
//        break;
//    case 2:
//        doTask = doExtract;
//        break;
//    case 3:
//        doTask = doEval;
//        break;
//    }
//}

void MainWindow::getCurrentTask()
{
    QTabWidget *tabWidTask = ui->toolWidget->findChild<QTabWidget *>();
    int index = tabWidTask->currentIndex()+1;
    switch(index)
    {
    case 1:
        doTask = doProcess;
        break;
    case 2:
        doTask = doExtract;
        break;
    case 3:
        doTask = doEval;
        break;
    }
}

void MainWindow::toggleUI()
{
    switch (doTask)
    {
    case doProcess:
    {
        ui->inputSrcType->setEnabled(1);
        getSrc2cvCAP();

        if(src2cvCAP.isValid())    // input source accept
        {
            ui->inputSrcType->setEnabled(1);
            ui->btnPreview->setEnabled(1);
            runAlgoUI->ui->selAlgo->setEnabled(1);

            if(useSrc == vidFile)
            {
                ui->lbl_srcName->setText(inputInfo.fileName);
                ui->lbl_srcCount->setText(QString::number(inputInfo.framCount));
                ui->lbl_srcSize->setText(inputInfo.frameResolution);

                if(inputInfo.mediaType == "VIDEO")
                {
                    ui->lbl_srcFrameRate->setText(QString::number(inputInfo.frameRate));
                    int srcMinute = (inputInfo.framCount/inputInfo.frameRate)/60;
                    int srcSec = (inputInfo.framCount/inputInfo.frameRate)%60;
                    ui->lbl_srcDuration->setText(QString::number(srcMinute)+":"+QString::number(srcSec));
                }
                else
                {
                     ui->lbl_srcFrameRate->setText("-");
                     ui->lbl_srcDuration->setText("-");
                }
            }
            else
            {
                runAlgoUI->ui->evaluatePanel->setEnabled(0);
            }

            if(runAlgoUI->isProcess)    /// Method is selected
            {
                runAlgoUI->ui->paramPanel->setEnabled(1);
                runAlgoUI->ui->evaluatePanel->setEnabled(1);
                runAlgoUI->ui->saveOutputPanel->setEnabled(1);
                runAlgoUI->ui->btnProcess->setEnabled(1);

                if(runAlgoUI->ui->cbIsEvalPerf->checkState())   /// Evaluate
                {
                    runAlgoUI->ui->browse_gtDir->setEnabled(1);
                    runAlgoUI->ui->txtGtDir->setEnabled(1);
                    runAlgoUI->ui->browse_resultDir->setEnabled(1);
                    runAlgoUI->ui->txtResultDir->setEnabled(1);
                }
                else
                {
                    runAlgoUI->ui->browse_gtDir->setEnabled(0);
                    runAlgoUI->ui->txtGtDir->setEnabled(0);
                    runAlgoUI->ui->browse_resultDir->setEnabled(0);
                    runAlgoUI->ui->txtResultDir->setEnabled(0);
                }

                if(runAlgoUI->ui->cbIsSaveImage->checkState())  /// Save Image Output
                {
                    runAlgoUI->ui->txtSaveImageOutputPath->setEnabled(1);
                    runAlgoUI->ui->saveImageFormat->setEnabled(1);
                }
                else
                {
                    runAlgoUI->ui->txtSaveImageOutputPath->setEnabled(0);
                    runAlgoUI->ui->saveImageFormat->setEnabled(0);
                }
            }

        } /// Main IF

        else if(!src2cvCAP.isValid())   // input source unaccept
        {
            ui->inputSrcType->setEnabled(1);
            ui->btnPreview->setEnabled(0);
            runAlgoUI->ui->selAlgo->setEnabled(0);
            runAlgoUI->ui->browse_gtDir->setEnabled(0);
            runAlgoUI->ui->txtGtDir->setEnabled(0);
            runAlgoUI->ui->browse_resultDir->setEnabled(0);
            runAlgoUI->ui->txtResultDir->setEnabled(0);
            runAlgoUI->ui->paramPanel->setEnabled(0);
            runAlgoUI->ui->evaluatePanel->setEnabled(0);
            runAlgoUI->ui->saveOutputPanel->setEnabled(0);
            runAlgoUI->ui->btnProcess->setEnabled(0);
        }
        break;
    } // case

    case doExtract:
    {
        ui->inputSrcType->setEnabled(1);
        getSrc2cvCAP();
        extractUI->isProcess = false;
        break;
    }

    case doEval:
    {
        ui->inputSrcType->setEnabled(1);
        break;
    }
    default :
    {
        ui->inputSrcType->setEnabled(1);
        ui->btnPreview->setEnabled(0);
        runAlgoUI->ui->selAlgo->setEnabled(0);
        runAlgoUI->ui->browse_gtDir->setEnabled(0);
        runAlgoUI->ui->txtGtDir->setEnabled(0);
        runAlgoUI->ui->browse_resultDir->setEnabled(0);
        runAlgoUI->ui->txtResultDir->setEnabled(0);
        runAlgoUI->ui->paramPanel->setEnabled(0);
        runAlgoUI->ui->evaluatePanel->setEnabled(0);
        runAlgoUI->ui->saveOutputPanel->setEnabled(0);
        runAlgoUI->ui->btnProcess->setEnabled(0);
    }

    } /// switch
}



void MainWindow::on_camListBox_currentIndexChanged(const QString &arg1)
{
    int c = ui->camResBox->count();
    ui->camResBox->addItems(getCamResSize(arg1));

    for(int i=0;i< c;++i)
    {
        ui->camResBox->removeItem(0);
    }
    camID = ui->camListBox->currentIndex();
//    doTask = doProcess;
    emit uiState();
}

void MainWindow::on_camResBox_currentIndexChanged(const QString &arg1)
{
    QStringList tmpSize = arg1.split(',');
    QString w = tmpSize.at(0);
    QString h = tmpSize.at(1);
    runAlgoUI->resSize.width = w.toInt();
    runAlgoUI->resSize.height = h.toInt();
    extractUI->resSize.width = w.toInt();
    extractUI->resSize.height = h.toInt();
    emit uiState();
}



