#ifndef TASK_EVALUATE_H
#define TASK_EVALUATE_H

#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QFileSystemModel>
#include <QInputDialog>
// External Library
#include "mivuttil.h"

namespace Ui {
class task_Evaluate;
}

class task_Evaluate : public QWidget
{
    friend class MainWindow;
    Q_OBJECT

public:
    explicit task_Evaluate(QWidget *parent = 0);
    ~task_Evaluate();

private slots:
    void on_btnNewDir_clicked();

    void on_btnEval_clicked();

private:
    Ui::task_Evaluate *ui;
    QFileSystemModel *testDirModel;
    QFileSystemModel *GTDirModel;
    QFileSystemModel *resultDirModel;
    QModelIndex currentIndex;

    void getDirName(const QModelIndex &index);
    void processor();
};

#endif // TASK_EVALUATE_H
