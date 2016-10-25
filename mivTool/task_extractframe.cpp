#include "task_extractframe.h"
#include "ui_task_extractframe.h"

task_ExtractFrame::task_ExtractFrame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::task_ExtractFrame)
{
    ui->setupUi(this);

    QString sPath = "C:/";
    dirModel = new QFileSystemModel(this);
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirModel->setRootPath(sPath);
    ui->dirTreeView->setModel(dirModel);
    ui->dirTreeView->hideColumn(1);
    ui->dirTreeView->hideColumn(2);
    ui->dirTreeView->hideColumn(3);
    ui->btnNewDir->setEnabled(0);
    ui->btnExtract->setEnabled(0);

    /// OutputImage Format mode
    connect(ui->saveJPG,&QRadioButton::clicked,this,&task_ExtractFrame::extractFrameFormat );
    connect(ui->saveBMP,&QRadioButton::clicked,this,&task_ExtractFrame::extractFrameFormat );
    connect(ui->savePNG,&QRadioButton::clicked,this,&task_ExtractFrame::extractFrameFormat );
}

task_ExtractFrame::~task_ExtractFrame()
{
    delete ui;
}

void task_ExtractFrame::on_dirTreeView_clicked(const QModelIndex &index)
{
    currentIndex = index;
    ui->btnNewDir->setEnabled(1);
    QString extractPath = dirModel->fileInfo(index).absoluteFilePath();
    ui->txtOutputPath->setText(extractPath);
    ui->btnExtract->setEnabled(1);
}

void task_ExtractFrame::on_btnNewDir_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Enter Directory Name"),
                                         tr("Directory Name:"), QLineEdit::Normal,
                                         tr("NewExtractFolder"), &ok);
    if (ok && !text.isEmpty())
    {
        QModelIndex index = dirModel->mkdir(currentIndex,text);
        QString extractPath = dirModel->fileInfo(index).absoluteFilePath();
        ui->txtOutputPath->setText(extractPath);
    }
}

//// SLOT for save image format
void::task_ExtractFrame::extractFrameFormat()
{
    QRadioButton *saveFormat = qobject_cast<QRadioButton*>(sender());
    saveImageOutputFormat = saveFormat->text().toStdString();

}

int task_ExtractFrame::processor()
{
    cv::Ptr<miv::vidProcessor> processor = new miv::vidProcessor;
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

    processor->setMethodProcessor(isProcess); // Preview or Extract Only

    /// Checking save/extract image output  or not
    if ( !saveImageOutputPath.empty() )
        absSaveImageOutputPath = processor->setSaveOutputPath(saveImageOutputPath,saveImageOutputFormat);

    /// Declare a window to display the video
    processor->displayInput("Input Video");

    /// Start the process
    if ( processor->run() )
        QMessageBox::information(
            this,tr("Video Processing Status"),msgStatus );

    /// Release possible resources
    processor.release();
    return 0;
}

void task_ExtractFrame::on_btnExtract_clicked()
{
    saveImageOutputPath = ui->txtOutputPath->text().toStdString();
    if(!saveImageOutputPath.empty())
    {
        msgStatus = "Extracting images completed.";
        processor();
    }
    else
       ui->btnExtract->setEnabled(0);
}
