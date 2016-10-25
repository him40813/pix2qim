/********************************************************************************
** Form generated from reading UI file 'task_extractframe.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASK_EXTRACTFRAME_H
#define UI_TASK_EXTRACTFRAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_task_ExtractFrame
{
public:
    QGroupBox *extractPanel;
    QGroupBox *saveImageFormat;
    QWidget *layoutWidget_4;
    QHBoxLayout *horizontalLayout_5;
    QRadioButton *saveJPG;
    QRadioButton *saveBMP;
    QRadioButton *savePNG;
    QWidget *layoutWidget_5;
    QVBoxLayout *verticalLayout;
    QLineEdit *txtOutputPath;
    QPushButton *btnExtract;
    QTreeView *dirTreeView;
    QLabel *label;
    QPushButton *btnNewDir;

    void setupUi(QWidget *task_ExtractFrame)
    {
        if (task_ExtractFrame->objectName().isEmpty())
            task_ExtractFrame->setObjectName(QStringLiteral("task_ExtractFrame"));
        task_ExtractFrame->resize(770, 512);
        extractPanel = new QGroupBox(task_ExtractFrame);
        extractPanel->setObjectName(QStringLiteral("extractPanel"));
        extractPanel->setEnabled(true);
        extractPanel->setGeometry(QRect(520, 50, 241, 221));
        saveImageFormat = new QGroupBox(extractPanel);
        saveImageFormat->setObjectName(QStringLiteral("saveImageFormat"));
        saveImageFormat->setEnabled(true);
        saveImageFormat->setGeometry(QRect(10, 80, 221, 51));
        layoutWidget_4 = new QWidget(saveImageFormat);
        layoutWidget_4->setObjectName(QStringLiteral("layoutWidget_4"));
        layoutWidget_4->setEnabled(true);
        layoutWidget_4->setGeometry(QRect(10, 20, 211, 20));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget_4);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        saveJPG = new QRadioButton(layoutWidget_4);
        saveJPG->setObjectName(QStringLiteral("saveJPG"));
        saveJPG->setEnabled(true);
        saveJPG->setChecked(false);

        horizontalLayout_5->addWidget(saveJPG);

        saveBMP = new QRadioButton(layoutWidget_4);
        saveBMP->setObjectName(QStringLiteral("saveBMP"));
        saveBMP->setEnabled(true);
        saveBMP->setChecked(true);

        horizontalLayout_5->addWidget(saveBMP);

        savePNG = new QRadioButton(layoutWidget_4);
        savePNG->setObjectName(QStringLiteral("savePNG"));
        savePNG->setEnabled(true);

        horizontalLayout_5->addWidget(savePNG);

        layoutWidget_5 = new QWidget(extractPanel);
        layoutWidget_5->setObjectName(QStringLiteral("layoutWidget_5"));
        layoutWidget_5->setEnabled(true);
        layoutWidget_5->setGeometry(QRect(10, 10, 221, 51));
        verticalLayout = new QVBoxLayout(layoutWidget_5);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        txtOutputPath = new QLineEdit(layoutWidget_5);
        txtOutputPath->setObjectName(QStringLiteral("txtOutputPath"));
        txtOutputPath->setEnabled(true);
        txtOutputPath->setReadOnly(true);

        verticalLayout->addWidget(txtOutputPath);

        btnExtract = new QPushButton(extractPanel);
        btnExtract->setObjectName(QStringLiteral("btnExtract"));
        btnExtract->setGeometry(QRect(80, 160, 75, 31));
        layoutWidget_5->raise();
        saveImageFormat->raise();
        btnExtract->raise();
        dirTreeView = new QTreeView(task_ExtractFrame);
        dirTreeView->setObjectName(QStringLiteral("dirTreeView"));
        dirTreeView->setGeometry(QRect(10, 50, 501, 451));
        label = new QLabel(task_ExtractFrame);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 20, 201, 16));
        btnNewDir = new QPushButton(task_ExtractFrame);
        btnNewDir->setObjectName(QStringLiteral("btnNewDir"));
        btnNewDir->setGeometry(QRect(420, 10, 91, 31));

        retranslateUi(task_ExtractFrame);

        QMetaObject::connectSlotsByName(task_ExtractFrame);
    } // setupUi

    void retranslateUi(QWidget *task_ExtractFrame)
    {
        task_ExtractFrame->setWindowTitle(QApplication::translate("task_ExtractFrame", "Form", 0));
        extractPanel->setTitle(QString());
        saveImageFormat->setTitle(QApplication::translate("task_ExtractFrame", "Output Images Format", 0));
        saveJPG->setText(QApplication::translate("task_ExtractFrame", "jpg", 0));
        saveBMP->setText(QApplication::translate("task_ExtractFrame", "bmp", 0));
        savePNG->setText(QApplication::translate("task_ExtractFrame", "png", 0));
        txtOutputPath->setInputMask(QString());
        txtOutputPath->setText(QString());
        txtOutputPath->setPlaceholderText(QApplication::translate("task_ExtractFrame", "Export Frames as...", 0));
        btnExtract->setText(QApplication::translate("task_ExtractFrame", "Extract", 0));
        label->setText(QApplication::translate("task_ExtractFrame", "Extract Frames As ...", 0));
        btnNewDir->setText(QApplication::translate("task_ExtractFrame", "New Directory", 0));
    } // retranslateUi

};

namespace Ui {
    class task_ExtractFrame: public Ui_task_ExtractFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASK_EXTRACTFRAME_H
