/********************************************************************************
** Form generated from reading UI file 'task_evaluate.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASK_EVALUATE_H
#define UI_TASK_EVALUATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_task_Evaluate
{
public:
    QTreeView *dirTreeTestcase;
    QTreeView *dirTreeGT;
    QTreeView *dirTreeResult;
    QPushButton *btnEval;
    QLineEdit *txtTestPath;
    QLineEdit *txtGTPath;
    QLineEdit *txtResultPath;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *btnNewDir;

    void setupUi(QWidget *task_Evaluate)
    {
        if (task_Evaluate->objectName().isEmpty())
            task_Evaluate->setObjectName(QStringLiteral("task_Evaluate"));
        task_Evaluate->resize(770, 512);
        dirTreeTestcase = new QTreeView(task_Evaluate);
        dirTreeTestcase->setObjectName(QStringLiteral("dirTreeTestcase"));
        dirTreeTestcase->setGeometry(QRect(10, 40, 241, 321));
        dirTreeGT = new QTreeView(task_Evaluate);
        dirTreeGT->setObjectName(QStringLiteral("dirTreeGT"));
        dirTreeGT->setGeometry(QRect(260, 40, 241, 321));
        dirTreeResult = new QTreeView(task_Evaluate);
        dirTreeResult->setObjectName(QStringLiteral("dirTreeResult"));
        dirTreeResult->setGeometry(QRect(520, 60, 241, 301));
        btnEval = new QPushButton(task_Evaluate);
        btnEval->setObjectName(QStringLiteral("btnEval"));
        btnEval->setGeometry(QRect(350, 452, 75, 41));
        txtTestPath = new QLineEdit(task_Evaluate);
        txtTestPath->setObjectName(QStringLiteral("txtTestPath"));
        txtTestPath->setGeometry(QRect(10, 370, 241, 21));
        txtTestPath->setReadOnly(true);
        txtGTPath = new QLineEdit(task_Evaluate);
        txtGTPath->setObjectName(QStringLiteral("txtGTPath"));
        txtGTPath->setGeometry(QRect(260, 370, 241, 21));
        txtGTPath->setReadOnly(true);
        txtResultPath = new QLineEdit(task_Evaluate);
        txtResultPath->setObjectName(QStringLiteral("txtResultPath"));
        txtResultPath->setGeometry(QRect(520, 370, 241, 21));
        txtResultPath->setReadOnly(true);
        label = new QLabel(task_Evaluate);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 20, 241, 16));
        label_2 = new QLabel(task_Evaluate);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(260, 20, 241, 16));
        label_3 = new QLabel(task_Evaluate);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(520, 30, 141, 16));
        btnNewDir = new QPushButton(task_Evaluate);
        btnNewDir->setObjectName(QStringLiteral("btnNewDir"));
        btnNewDir->setGeometry(QRect(674, 20, 81, 31));

        retranslateUi(task_Evaluate);

        QMetaObject::connectSlotsByName(task_Evaluate);
    } // setupUi

    void retranslateUi(QWidget *task_Evaluate)
    {
        task_Evaluate->setWindowTitle(QApplication::translate("task_Evaluate", "Form", 0));
        btnEval->setText(QApplication::translate("task_Evaluate", "Evaluate", 0));
        txtTestPath->setPlaceholderText(QApplication::translate("task_Evaluate", "Test Images Directory", 0));
        txtGTPath->setPlaceholderText(QApplication::translate("task_Evaluate", "Groundtruth Images Directory", 0));
        txtResultPath->setText(QString());
        txtResultPath->setPlaceholderText(QApplication::translate("task_Evaluate", "Save evaluate file as...", 0));
        label->setText(QApplication::translate("task_Evaluate", "Selecting Testcase Images  Directory", 0));
        label_2->setText(QApplication::translate("task_Evaluate", "Selecting Groundtruth Images  Directory", 0));
        label_3->setText(QApplication::translate("task_Evaluate", "Selecting Save Directory", 0));
        btnNewDir->setText(QApplication::translate("task_Evaluate", "New Directory", 0));
    } // retranslateUi

};

namespace Ui {
    class task_Evaluate: public Ui_task_Evaluate {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASK_EVALUATE_H
