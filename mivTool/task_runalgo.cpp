#include "task_runalgo.h"
#include "ui_task_runalgo.h"

using namespace std;
using namespace cv;

task_RunAlgo::task_RunAlgo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::task_RunAlgo)
{
    ui->setupUi(this);

    widgetIni();
    ui->txtResultDir->setText(RESULTDIR);  // set default Result Evaluate Directory

    /// OutputImage Format mode
    connect(ui->saveJPG,SIGNAL(clicked()),this,SLOT(on_saveImageFormat_clicked() ) );
    connect(ui->saveBMP,SIGNAL(clicked()),this,SLOT(on_saveImageFormat_clicked() ) );
    connect(ui->savePNG,SIGNAL(clicked()),this,SLOT(on_saveImageFormat_clicked() ) );

    connect( ui->cbIsEvalPerf,&QCheckBox::stateChanged,this,&task_RunAlgo::broadCastSignal );
    connect( ui->cbIsSaveImage,&QCheckBox::stateChanged,this,&task_RunAlgo::saveImageOutput );

    connect( this,&task_RunAlgo::taskState,this,&task_RunAlgo::taskMng );

    clog<<"Initial Complete" << endl;
}

task_RunAlgo::~task_RunAlgo()
{
    delete ui;
}

void task_RunAlgo::taskMng(int task)
{
    switch(task)
    {
    case 0:
        isProcess = false;
        msgStatus = "Preview finished.";
        videoProcessor(); /// Call Processing
        break;
    case 1:
        isProcess = true;
        msgStatus = "Processing completed.";
        saveParamConfig();  /// Write current parameters to xml config file.
        makeMethodProcessor();
        videoProcessor();
        evaluateResults();
        break;
    }
}

void task_RunAlgo::widgetIni()
{
    /// Load Alogorithms from TXT to QListWidget
    QString metListPath(configDirPath+"/methodList.txt");
    QStringList metList;
    rwTxtFile::readTxt(metListPath,metList,'#');
    ui->selAlgo->clear();
    ui->selAlgo->insertItems(0,metList);

    /// Registed method class
    methodSelector();

    firstRun = true;
    useSrc = vidFile;

    evalModeSelected = evalNone;

}
void task_RunAlgo::saveImageOutput()
{
    if(ui->cbIsSaveImage->isChecked())
    {
        QString savePath = dialogGetDir("Save Images as...");
         if(!savePath.isEmpty())
         {
//             saveImageOutputPath = savePath.toStdString();
             ui->txtSaveImageOutputPath->setEnabled(1);
             ui->txtSaveImageOutputPath->setText(savePath);
//             isSaveImageOutput = true;

             if(ui->cbIsEvalPerf->isChecked())
                 ui->saveImageFormat->setEnabled(0);
             else
                 ui->saveImageFormat->setEnabled(1);
         }
         else
         {
             ui->cbIsSaveImage->setCheckState(Qt::Unchecked);
             ui->saveImageFormat->setEnabled(0);
         }
    }
     else
     {
         saveImageOutputPath.clear();
         ui->txtSaveImageOutputPath->clear();
         ui->cbIsSaveImage->setChecked(false);
         ui->cbIsSaveImage->setCheckState(Qt::Unchecked);
         ui->saveImageFormat->setEnabled(0);
     }
}

void task_RunAlgo::getSaveImageOutputPath()
{
    if(!ui->txtSaveImageOutputPath->text().isEmpty())
    {
        saveImageOutputPath = ui->txtSaveImageOutputPath->text().toStdString();
        isSaveImageOutput = true;
    }
    else
    {
        isSaveImageOutput = false;
    }
}

void task_RunAlgo::broadCastSignal()
{
    emit uiState();
}

void task_RunAlgo::on_browse_inputSource_clicked()
{
    QString inputSource = QFileDialog::getOpenFileName(this, tr("Selecting Source"),srcTEMPPATH);
    if (!inputSource.isEmpty())
    {
        inputInfo.getInfo(inputSource);    // get media info
        emit uiState();
    }

    else
        clog<<"No source select"<<endl;
}

//// Get Input Source
void task_RunAlgo::getSrc2cvCAP()
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
}

//// Show Parameter settings Panel
void task_RunAlgo::on_selAlgo_itemClicked()
{

    QStringList tmpMethod = ui->selAlgo->currentItem()->text().split("-");
    methodString = tmpMethod[1].toStdString();
    /// Load parameters and generate gui
    useParam = loadRecent;
    loadParam2UI();
    isProcess = true;
    emit uiState();
}

void task_RunAlgo::loadParam2UI()
{
    paramFilePath = QString::fromStdString(bgsLibConfigPath + methodString+".xml") ;
    bool paramFileIsExist = infoDirFile::isFileExists(paramFilePath);  // Check file exist

    if(useParam == loadDefault && paramFileIsExist)
    {
        QFile::remove(paramFilePath);
        paramFileIsExist = false;
    }

    if(!paramFileIsExist) /// Method's config file non exist, Create new one.
    {
        makeMethodProcessor();
        algoProcessor->saveConfig();
        algoProcessor.release();
    }

    if(!firstRun)    /// delete old parameters UI before create new one.
    {
        QLayout* layout = ui->widgetParam->layout();    /// Get child layout
        if (layout != 0)    // Delete existed Layout parameters
        {
            QLayoutItem *item;
            while ((item = layout->takeAt(0)) != 0)
            {
                delete item->widget();
                delete item;
            }
            delete layout;
            clog<<"Delete old Layout"<<endl;
        }
    }

    /// create new parameters Layout
    gridLayout = new QGridLayout;
    gridLayout->setObjectName( QString::fromStdString(methodString) );

    /// Read parameters from XML config
    QMap<QString, QVariant> defaultParam;
    cv::Ptr<rwXMLFile> tmpXML = new rwXMLFile(paramFilePath);
    tmpXML->readXMLFile(defaultParam);
    paramWid->makeWidgetOnGrid(gridLayout,defaultParam);
    ui->widgetParam->setLayout(gridLayout);
    firstRun = false;
}

//// LOAD Default Parameters from XML
void task_RunAlgo::on_btnLoadDefaultConfig_clicked()
{
    useParam = loadDefault;
    loadParam2UI();
}


//// Select GroundTruth directory for Evaluate
void task_RunAlgo::on_browse_gtDir_clicked()
{
    QString savePath = dialogGetDir("Save Images as...");
    ui->txtGtDir->setText(savePath);
}

void task_RunAlgo::on_browse_resultDir_clicked()
{
    QString savePath = dialogGetDir("Save Images as...");
    ui->txtResultDir->setText(savePath);
}


//// SLOT for save image format
void::task_RunAlgo::on_saveImageFormat_clicked()
{
    QRadioButton *saveFormat = qobject_cast<QRadioButton*>(sender());
    saveImageOutputFormat = saveFormat->text().toStdString();

}

// Instantiate Method for Processing by name
void task_RunAlgo::makeMethodProcessor()
{
    char *mname = &methodString[0u];
    int id = QMetaType::type(mname);
    if (id != QMetaType::UnknownType)
    {
        algoProcessor = static_cast< IBGS* >( QMetaType::create( id ) );
    }
}

//// Preparing before Run Main Process
void task_RunAlgo::on_btnProcess_clicked()
{
    getSaveImageOutputPath();

    /// Checking eval option and save ouput images
    if(ui->cbIsEvalPerf->isChecked())      /// is evaluate ?
    {
        if(!ui->txtGtDir->text().isEmpty()) /// eval = yes
        {
            if(!isSaveImageOutput)  /// set tmp Dir save for eval
            {
                saveImageOutputPath = tempDirPath.toStdString()+"_tmpEval";
                QDir tmp;
                tmp.mkdir(QString::fromStdString(saveImageOutputPath) );    // Create temp dir
            }

            if( ui->txtResultDir->text().isEmpty())
                 ui->txtResultDir->setText(RESULTDIR);

            infoDirFile gtInfo(ui->txtGtDir->text());
            saveImageOutputFormat = gtInfo.extFile; /// get GT format

            isEval = true;
        }
        else    /// Eval = No
        {
            ui->cbIsEvalPerf->setCheckState(Qt::Unchecked);
            isEval = false;
        }
    }
    else
    {
        getSaveImageFormat();
        isEval = false;
    }

    emit taskState(1);
}

void task_RunAlgo::getSaveImageFormat()
{
     QList<QRadioButton*>saveFormat = ui->saveImageFormat->findChildren<QRadioButton *>();
     for(int i=0;i<saveFormat.size(); ++i)
     {
         if(saveFormat.at(i)->isChecked())
         {
             saveImageOutputFormat = saveFormat.at(i)->text().toStdString();
             i = 99;
         }
     }
}

void task_RunAlgo::saveParamConfig()
{
    paramList.clear();
    paramWid->getWidget2QMap(ui->widgetParam,paramList);
    paramList.insert("showOutput",0);
    cv::Ptr<rwXMLFile> tmpXML = new rwXMLFile(paramFilePath);
    tmpXML->writeXMLFile(paramList);

}

//// Processing Only
int task_RunAlgo::videoProcessor()
{
    processor = new miv::vidProcessor;

    /// Check Input source File or Camera
    if(src2cvCAP.type() == QVariant::Int)   // input from camera
    {
        int inputSource = src2cvCAP.toInt();
        processor->setInput(inputSource);
        processor->setCamRes(resSize);
    }
    else
    {
        string inputSource = src2cvCAP.toString().toStdString();
        processor->setInput(inputSource);
    }


    processor->setDelay(30);

    /// Checking processing frame or not
    if (!isProcess)
    {
        processor->setMethodProcessor(isProcess); // Preview or Extract Only
    }
    else
    {
        processor->setMethodProcessor(algoProcessor); // Processing
    }

    /// Checking save/extract image output  or not
    if ( !saveImageOutputPath.empty() )
        absSaveImageOutputPath = processor->setSaveOutputPath(saveImageOutputPath,saveImageOutputFormat);

    /// Declare a window to display the video
    processor->displayInput("Input Video");
    processor->displayOutput("Output Video");

    /// Start the process
    if ( processor->run() )
        QMessageBox::information(
            this,tr("Video Processing Status"),msgStatus );

    processedFPS = processor->getProcessedFrameRate();

    /// Release possible resources
    algoProcessor.release();
    processor.release();
    return 0;
}

void task_RunAlgo::evaluateResults()
{
    if(isEval)
    {
        QString gtDir(ui->txtGtDir->text());
        QString resDir(ui->txtResultDir->text());
        bool evalAllFrames = true;

        QString srcDir = QString::fromStdString(absSaveImageOutputPath);

        QString methodName = QString::fromStdString(methodString);
        paramList.remove("showOutput");
        evalOptionData.clear();
        evalOptionData.insert("methodName",methodName);
        evalOptionData.insert("paramList",paramList);
        evalOptionData.insert("processedFPS",processedFPS);
        evalOptionData.insert("evalAllFrames",evalAllFrames);
        evalDetection eval(srcDir, gtDir, resDir,evalOptionData);
        eval.evalPerf();

        if(!isSaveImageOutput)  // Remove Evaluate Temp Dir
        {
            QDir tm(srcDir);
            tm.removeRecursively();
        }

    }
}

QString task_RunAlgo::dialogGetDir(QString dialogTxt)
{
    QString pth = QFileDialog::getExistingDirectory(this, dialogTxt,
                srcTEMPPATH,QFileDialog::ShowDirsOnly);
    return pth;
}


void task_RunAlgo::on_stepB_clicked(){
    std::cout<<"step Click"<<endl;
    processor->p=false;
    processor->s=true;

}

void task_RunAlgo::on_pPB_clicked(){
    std::cout<<"pp Click"<<endl;
    processor->p=!processor->p;
}


