#include "task_evaluate.h"
#include "ui_task_evaluate.h"

task_Evaluate::task_Evaluate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::task_Evaluate)
{
    ui->setupUi(this);

    QString sPath = "C:/";
    testDirModel = new QFileSystemModel(this);
    testDirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    testDirModel->setRootPath(sPath);

    GTDirModel = new QFileSystemModel(this);
    GTDirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    GTDirModel->setRootPath(sPath);

    resultDirModel = new QFileSystemModel(this);
    resultDirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    resultDirModel->setRootPath(sPath);

    ui->dirTreeTestcase->setModel(testDirModel);
    ui->dirTreeTestcase->hideColumn(1);
    ui->dirTreeTestcase->hideColumn(2);
    ui->dirTreeTestcase->hideColumn(3);
    ui->dirTreeGT->setModel(GTDirModel);
    ui->dirTreeGT->hideColumn(1);
    ui->dirTreeGT->hideColumn(2);
    ui->dirTreeGT->hideColumn(3);
    ui->dirTreeResult->setModel(resultDirModel);
    ui->dirTreeResult->hideColumn(1);
    ui->dirTreeResult->hideColumn(2);
    ui->dirTreeResult->hideColumn(3);

    ui->btnNewDir->setEnabled(0);

    connect(ui->dirTreeTestcase,&QTreeView::clicked,this,&task_Evaluate::getDirName);
    connect(ui->dirTreeGT,&QTreeView::clicked,this,&task_Evaluate::getDirName);
    connect(ui->dirTreeResult,&QTreeView::clicked,this,&task_Evaluate::getDirName);
}

task_Evaluate::~task_Evaluate()
{
    delete ui;
}

void task_Evaluate::getDirName(const QModelIndex &index)
{
    if(QObject::sender()->objectName() == "dirTreeTestcase")
    {
        QString dirPath = testDirModel->fileInfo(index).absoluteFilePath();
        ui->txtTestPath->setText(dirPath);
    }
    else if(QObject::sender()->objectName() == "dirTreeGT")
    {
        QString dirPath = GTDirModel->fileInfo(index).absoluteFilePath();
        ui->txtGTPath->setText(dirPath);
    }
    else if(QObject::sender()->objectName() == "dirTreeResult")
    {
        currentIndex = index;
        QString dirPath = resultDirModel->fileInfo(index).absoluteFilePath();
        ui->txtResultPath->setText(dirPath);
        ui->btnNewDir->setEnabled(1);
    }

}

void task_Evaluate::on_btnNewDir_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Enter Directory Name"),
                                         tr("Directory Name:"), QLineEdit::Normal,
                                         tr("New Result Folder"), &ok);
    if (ok && !text.isEmpty())
    {
        QModelIndex index = resultDirModel->mkdir(currentIndex,text);
        QString dirPath = resultDirModel->fileInfo(index).absoluteFilePath();
        ui->txtResultPath->setText(dirPath);
    }
}

void task_Evaluate::on_btnEval_clicked()
{
    if(!ui->txtTestPath->text().isEmpty()
            && !ui->txtGTPath->text().isEmpty()
            && !ui->txtResultPath->text().isEmpty() )
        processor();
    else
    {
        QString msgStatus = "Testcase, Groundtruth or Save Result directory not select.";
        QMessageBox::information(
            this,tr("No Directory Selected"),msgStatus );
    }
}

void task_Evaluate::processor()
{

    QString srcDir = ui->txtTestPath->text();
    QString gtDir(ui->txtGTPath->text());
    QString resDir(ui->txtResultPath->text());
    bool evalAllFrames = true;

    evalDetection eval(srcDir, gtDir, resDir, evalAllFrames);
    eval.evalPerf();
    QString msgStatus = "Evaluate finished, result is saved as "+resDir;
    QMessageBox::information(
        this,tr("Video Processing Status"),msgStatus );
}
