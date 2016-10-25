#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    myPlayer = new Player();
    QObject::connect(myPlayer, SIGNAL(processedImage(QImage)),this,
                               SLOT(updatePlayerUI(QImage)));

    ui->setupUi(this);
}

void MainWindow::updatePlayerUI(QImage img)
{
    if (!img.isNull())
    {
        ui->lblOrg->setAlignment(Qt::AlignCenter);
        ui->lblOrg->setPixmap(QPixmap::fromImage(img).scaled(ui->lblOrg->size(),Qt::KeepAspectRatio, Qt::FastTransformation));

//        ui->lblMap->setAlignment(Qt::AlignCenter);
//        ui->lblMap->setPixmap(QPixmap::fromImage(img).scaled(ui->lblMap->size(),Qt::KeepAspectRatio, Qt::FastTransformation));
    }
}

MainWindow::~MainWindow()
{
    delete myPlayer;
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                          tr("Open Video"), ".",
                                          tr("Video Files (*.avi *.mpg *.mp4)"));
    if (!filename.isEmpty()){
        if (!myPlayer->loadVideo(filename.toStdString().data()))
        {
            QMessageBox msgBox;
            msgBox.setText("The selected video could not be opened!");
            msgBox.exec();
        }
    }
}

void MainWindow::on_btnCam_clicked()
{
    if (!myPlayer->connectCam())
    {
        QMessageBox msgBox;
        msgBox.setText("No Camera found!");
        msgBox.exec();
    }
//    else{
//        myPlayer->Play();
//    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if (myPlayer->isStopped())
    {
        myPlayer->Play();
        ui->pushButton_2->setText(tr("Stop"));
    }else
    {
        myPlayer->Stop();
        ui->pushButton_2->setText(tr("Play"));
    }
}
