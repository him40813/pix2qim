#ifndef TASK_EXTRACTFRAME_H
#define TASK_EXTRACTFRAME_H

#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QFileSystemModel>
#include <QInputDialog>
// External Library
#include "vidprocessor.h"

namespace Ui {
class task_ExtractFrame;
}

class task_ExtractFrame : public QWidget
{
    friend class MainWindow;
    Q_OBJECT

public:
    explicit task_ExtractFrame(QWidget *parent = 0);
    ~task_ExtractFrame();

private slots:
    void on_dirTreeView_clicked(const QModelIndex &index);
    void on_btnNewDir_clicked();

    void on_btnExtract_clicked();

private:
    Ui::task_ExtractFrame *ui;
    QFileSystemModel *dirModel;

    QModelIndex currentIndex;
    bool isProcess;
    QVariant src2cvCAP;
    string saveImageOutputFormat = "bmp";   // Image output format
    string saveImageOutputPath; // Image output saving path
    string absSaveImageOutputPath;  // Save Dir return from video processor
    QString msgStatus;
    cv::Size_<int> resSize;

    void extractFrameFormat();
    int processor();
};

#endif // TASK_EXTRACTFRAME_H
