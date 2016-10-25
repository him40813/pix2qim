/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *inputSrcType;
    QWidget *inputSrcFile_2;
    QWidget *layoutWidget_10;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_13;
    QLabel *lbl_srcName;
    QPushButton *browseInput;
    QWidget *layoutWidget_11;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_9;
    QLabel *lbl_srcFrameRate;
    QLabel *label_10;
    QLabel *lbl_srcDuration;
    QWidget *layoutWidget_6;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_11;
    QLabel *lbl_srcSize;
    QLabel *label_12;
    QLabel *lbl_srcCount;
    QWidget *inputSrcCam_2;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_14;
    QComboBox *camListBox;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_15;
    QComboBox *camResBox;
    QWidget *toolWidget;
    QPushButton *btnPreview;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(790, 730);
        MainWindow->setMinimumSize(QSize(790, 730));
        MainWindow->setMaximumSize(QSize(790, 730));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        inputSrcType = new QTabWidget(centralWidget);
        inputSrcType->setObjectName(QStringLiteral("inputSrcType"));
        inputSrcType->setEnabled(true);
        inputSrcType->setGeometry(QRect(10, 10, 681, 81));
        inputSrcFile_2 = new QWidget();
        inputSrcFile_2->setObjectName(QStringLiteral("inputSrcFile_2"));
        layoutWidget_10 = new QWidget(inputSrcFile_2);
        layoutWidget_10->setObjectName(QStringLiteral("layoutWidget_10"));
        layoutWidget_10->setEnabled(true);
        layoutWidget_10->setGeometry(QRect(80, 10, 241, 41));
        horizontalLayout_11 = new QHBoxLayout(layoutWidget_10);
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(0, 0, 0, 0);
        label_13 = new QLabel(layoutWidget_10);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setEnabled(true);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_13->setFont(font);

        horizontalLayout_11->addWidget(label_13);

        lbl_srcName = new QLabel(layoutWidget_10);
        lbl_srcName->setObjectName(QStringLiteral("lbl_srcName"));
        lbl_srcName->setEnabled(true);
        QFont font1;
        font1.setPointSize(8);
        font1.setBold(true);
        font1.setWeight(75);
        lbl_srcName->setFont(font1);

        horizontalLayout_11->addWidget(lbl_srcName);

        browseInput = new QPushButton(inputSrcFile_2);
        browseInput->setObjectName(QStringLiteral("browseInput"));
        browseInput->setEnabled(true);
        browseInput->setGeometry(QRect(10, 10, 61, 41));
        layoutWidget_11 = new QWidget(inputSrcFile_2);
        layoutWidget_11->setObjectName(QStringLiteral("layoutWidget_11"));
        layoutWidget_11->setEnabled(true);
        layoutWidget_11->setGeometry(QRect(330, 30, 331, 21));
        horizontalLayout_9 = new QHBoxLayout(layoutWidget_11);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        label_9 = new QLabel(layoutWidget_11);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setEnabled(true);

        horizontalLayout_9->addWidget(label_9);

        lbl_srcFrameRate = new QLabel(layoutWidget_11);
        lbl_srcFrameRate->setObjectName(QStringLiteral("lbl_srcFrameRate"));
        lbl_srcFrameRate->setEnabled(true);

        horizontalLayout_9->addWidget(lbl_srcFrameRate);

        label_10 = new QLabel(layoutWidget_11);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setEnabled(true);

        horizontalLayout_9->addWidget(label_10);

        lbl_srcDuration = new QLabel(layoutWidget_11);
        lbl_srcDuration->setObjectName(QStringLiteral("lbl_srcDuration"));
        lbl_srcDuration->setEnabled(true);

        horizontalLayout_9->addWidget(lbl_srcDuration);

        layoutWidget_6 = new QWidget(inputSrcFile_2);
        layoutWidget_6->setObjectName(QStringLiteral("layoutWidget_6"));
        layoutWidget_6->setEnabled(true);
        layoutWidget_6->setGeometry(QRect(330, 10, 331, 21));
        horizontalLayout_10 = new QHBoxLayout(layoutWidget_6);
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
        label_11 = new QLabel(layoutWidget_6);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setEnabled(true);

        horizontalLayout_10->addWidget(label_11);

        lbl_srcSize = new QLabel(layoutWidget_6);
        lbl_srcSize->setObjectName(QStringLiteral("lbl_srcSize"));
        lbl_srcSize->setEnabled(true);

        horizontalLayout_10->addWidget(lbl_srcSize);

        label_12 = new QLabel(layoutWidget_6);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setEnabled(true);

        horizontalLayout_10->addWidget(label_12);

        lbl_srcCount = new QLabel(layoutWidget_6);
        lbl_srcCount->setObjectName(QStringLiteral("lbl_srcCount"));
        lbl_srcCount->setEnabled(true);

        horizontalLayout_10->addWidget(lbl_srcCount);

        inputSrcType->addTab(inputSrcFile_2, QString());
        inputSrcCam_2 = new QWidget();
        inputSrcCam_2->setObjectName(QStringLiteral("inputSrcCam_2"));
        layoutWidget = new QWidget(inputSrcCam_2);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(11, 10, 371, 22));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_14 = new QLabel(layoutWidget);
        label_14->setObjectName(QStringLiteral("label_14"));

        horizontalLayout->addWidget(label_14);

        camListBox = new QComboBox(layoutWidget);
        camListBox->setObjectName(QStringLiteral("camListBox"));

        horizontalLayout->addWidget(camListBox);

        layoutWidget_2 = new QWidget(inputSrcCam_2);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(400, 10, 261, 22));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_15 = new QLabel(layoutWidget_2);
        label_15->setObjectName(QStringLiteral("label_15"));

        horizontalLayout_2->addWidget(label_15);

        camResBox = new QComboBox(layoutWidget_2);
        camResBox->setObjectName(QStringLiteral("camResBox"));

        horizontalLayout_2->addWidget(camResBox);

        inputSrcType->addTab(inputSrcCam_2, QString());
        toolWidget = new QWidget(centralWidget);
        toolWidget->setObjectName(QStringLiteral("toolWidget"));
        toolWidget->setGeometry(QRect(0, 100, 791, 571));
        btnPreview = new QPushButton(centralWidget);
        btnPreview->setObjectName(QStringLiteral("btnPreview"));
        btnPreview->setEnabled(true);
        btnPreview->setGeometry(QRect(700, 40, 71, 41));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 790, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        inputSrcType->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        label_13->setText(QApplication::translate("MainWindow", "Source :", 0));
        lbl_srcName->setText(QApplication::translate("MainWindow", "Source Name", 0));
        browseInput->setText(QApplication::translate("MainWindow", "Browse..", 0));
        label_9->setText(QApplication::translate("MainWindow", "Frame rate :", 0));
        lbl_srcFrameRate->setText(QApplication::translate("MainWindow", "-", 0));
        label_10->setText(QApplication::translate("MainWindow", "Duration :", 0));
        lbl_srcDuration->setText(QApplication::translate("MainWindow", "-", 0));
        label_11->setText(QApplication::translate("MainWindow", "Resolution :", 0));
        lbl_srcSize->setText(QApplication::translate("MainWindow", "-", 0));
        label_12->setText(QApplication::translate("MainWindow", "Number of Frames :", 0));
        lbl_srcCount->setText(QApplication::translate("MainWindow", "-", 0));
        inputSrcType->setTabText(inputSrcType->indexOf(inputSrcFile_2), QApplication::translate("MainWindow", "Video File", 0));
        label_14->setText(QApplication::translate("MainWindow", "Available Camera devices", 0));
        label_15->setText(QApplication::translate("MainWindow", "Supp. resolutions", 0));
        inputSrcType->setTabText(inputSrcType->indexOf(inputSrcCam_2), QApplication::translate("MainWindow", "Video Camera", 0));
        btnPreview->setText(QApplication::translate("MainWindow", "Preview", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
