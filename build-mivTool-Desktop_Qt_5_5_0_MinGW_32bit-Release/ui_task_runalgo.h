/********************************************************************************
** Form generated from reading UI file 'task_runalgo.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASK_RUNALGO_H
#define UI_TASK_RUNALGO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_task_RunAlgo
{
public:
    QGroupBox *evaluatePanel;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *cbIsEvalPerf;
    QPushButton *browse_gtDir;
    QLineEdit *txtGtDir;
    QPushButton *browse_resultDir;
    QLineEdit *txtResultDir;
    QGroupBox *saveOutputPanel;
    QGroupBox *saveImageFormat;
    QWidget *layoutWidget_4;
    QHBoxLayout *horizontalLayout_5;
    QRadioButton *saveJPG;
    QRadioButton *saveBMP;
    QRadioButton *savePNG;
    QWidget *layoutWidget_5;
    QVBoxLayout *verticalLayout;
    QCheckBox *cbIsSaveImage;
    QLineEdit *txtSaveImageOutputPath;
    QPushButton *btnProcess;
    QGroupBox *paramPanel;
    QWidget *layoutWidget_3;
    QVBoxLayout *verticalLayout_4;
    QPushButton *btnLoadDefaultConfig;
    QWidget *widgetParam;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QListWidget *selAlgo;
    QPushButton *stepB;
    QPushButton *pPB;

    void setupUi(QWidget *task_RunAlgo)
    {
        if (task_RunAlgo->objectName().isEmpty())
            task_RunAlgo->setObjectName(QStringLiteral("task_RunAlgo"));
        task_RunAlgo->resize(770, 512);
        evaluatePanel = new QGroupBox(task_RunAlgo);
        evaluatePanel->setObjectName(QStringLiteral("evaluatePanel"));
        evaluatePanel->setEnabled(true);
        evaluatePanel->setGeometry(QRect(10, 320, 381, 141));
        layoutWidget_2 = new QWidget(evaluatePanel);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setEnabled(true);
        layoutWidget_2->setGeometry(QRect(10, 10, 361, 141));
        verticalLayout_2 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        cbIsEvalPerf = new QCheckBox(layoutWidget_2);
        cbIsEvalPerf->setObjectName(QStringLiteral("cbIsEvalPerf"));

        verticalLayout_2->addWidget(cbIsEvalPerf);

        browse_gtDir = new QPushButton(layoutWidget_2);
        browse_gtDir->setObjectName(QStringLiteral("browse_gtDir"));
        browse_gtDir->setEnabled(true);

        verticalLayout_2->addWidget(browse_gtDir);

        txtGtDir = new QLineEdit(layoutWidget_2);
        txtGtDir->setObjectName(QStringLiteral("txtGtDir"));
        txtGtDir->setEnabled(true);

        verticalLayout_2->addWidget(txtGtDir);

        browse_resultDir = new QPushButton(layoutWidget_2);
        browse_resultDir->setObjectName(QStringLiteral("browse_resultDir"));
        browse_resultDir->setEnabled(true);

        verticalLayout_2->addWidget(browse_resultDir);

        txtResultDir = new QLineEdit(layoutWidget_2);
        txtResultDir->setObjectName(QStringLiteral("txtResultDir"));
        txtResultDir->setEnabled(true);

        verticalLayout_2->addWidget(txtResultDir);

        saveOutputPanel = new QGroupBox(task_RunAlgo);
        saveOutputPanel->setObjectName(QStringLiteral("saveOutputPanel"));
        saveOutputPanel->setEnabled(true);
        saveOutputPanel->setGeometry(QRect(410, 320, 351, 141));
        saveImageFormat = new QGroupBox(saveOutputPanel);
        saveImageFormat->setObjectName(QStringLiteral("saveImageFormat"));
        saveImageFormat->setEnabled(true);
        saveImageFormat->setGeometry(QRect(10, 80, 331, 51));
        layoutWidget_4 = new QWidget(saveImageFormat);
        layoutWidget_4->setObjectName(QStringLiteral("layoutWidget_4"));
        layoutWidget_4->setEnabled(true);
        layoutWidget_4->setGeometry(QRect(10, 20, 311, 27));
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
        saveBMP->setChecked(false);

        horizontalLayout_5->addWidget(saveBMP);

        savePNG = new QRadioButton(layoutWidget_4);
        savePNG->setObjectName(QStringLiteral("savePNG"));
        savePNG->setEnabled(true);
        savePNG->setChecked(true);

        horizontalLayout_5->addWidget(savePNG);

        layoutWidget_5 = new QWidget(saveOutputPanel);
        layoutWidget_5->setObjectName(QStringLiteral("layoutWidget_5"));
        layoutWidget_5->setEnabled(true);
        layoutWidget_5->setGeometry(QRect(10, 10, 331, 54));
        verticalLayout = new QVBoxLayout(layoutWidget_5);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        cbIsSaveImage = new QCheckBox(layoutWidget_5);
        cbIsSaveImage->setObjectName(QStringLiteral("cbIsSaveImage"));
        cbIsSaveImage->setEnabled(true);

        verticalLayout->addWidget(cbIsSaveImage);

        txtSaveImageOutputPath = new QLineEdit(layoutWidget_5);
        txtSaveImageOutputPath->setObjectName(QStringLiteral("txtSaveImageOutputPath"));
        txtSaveImageOutputPath->setEnabled(true);
        txtSaveImageOutputPath->setReadOnly(true);

        verticalLayout->addWidget(txtSaveImageOutputPath);

        layoutWidget_5->raise();
        saveImageFormat->raise();
        btnProcess = new QPushButton(task_RunAlgo);
        btnProcess->setObjectName(QStringLiteral("btnProcess"));
        btnProcess->setEnabled(true);
        btnProcess->setGeometry(QRect(530, 470, 131, 31));
        paramPanel = new QGroupBox(task_RunAlgo);
        paramPanel->setObjectName(QStringLiteral("paramPanel"));
        paramPanel->setEnabled(true);
        paramPanel->setGeometry(QRect(410, 10, 351, 301));
        layoutWidget_3 = new QWidget(paramPanel);
        layoutWidget_3->setObjectName(QStringLiteral("layoutWidget_3"));
        layoutWidget_3->setEnabled(true);
        layoutWidget_3->setGeometry(QRect(10, 20, 331, 271));
        verticalLayout_4 = new QVBoxLayout(layoutWidget_3);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        btnLoadDefaultConfig = new QPushButton(layoutWidget_3);
        btnLoadDefaultConfig->setObjectName(QStringLiteral("btnLoadDefaultConfig"));
        btnLoadDefaultConfig->setEnabled(true);

        verticalLayout_4->addWidget(btnLoadDefaultConfig);

        widgetParam = new QWidget(layoutWidget_3);
        widgetParam->setObjectName(QStringLiteral("widgetParam"));
        widgetParam->setEnabled(true);

        verticalLayout_4->addWidget(widgetParam);

        layoutWidget = new QWidget(task_RunAlgo);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setEnabled(true);
        layoutWidget->setGeometry(QRect(10, 10, 381, 301));
        verticalLayout_3 = new QVBoxLayout(layoutWidget);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setEnabled(true);

        verticalLayout_3->addWidget(label);

        selAlgo = new QListWidget(layoutWidget);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(selAlgo);
        __qlistwidgetitem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        new QListWidgetItem(selAlgo);
        new QListWidgetItem(selAlgo);
        new QListWidgetItem(selAlgo);
        new QListWidgetItem(selAlgo);
        new QListWidgetItem(selAlgo);
        new QListWidgetItem(selAlgo);
        new QListWidgetItem(selAlgo);
        new QListWidgetItem(selAlgo);
        new QListWidgetItem(selAlgo);
        new QListWidgetItem(selAlgo);
        new QListWidgetItem(selAlgo);
        new QListWidgetItem(selAlgo);
        selAlgo->setObjectName(QStringLiteral("selAlgo"));
        selAlgo->setEnabled(true);

        verticalLayout_3->addWidget(selAlgo);

        stepB = new QPushButton(task_RunAlgo);
        stepB->setObjectName(QStringLiteral("stepB"));
        stepB->setGeometry(QRect(410, 470, 111, 31));
        pPB = new QPushButton(task_RunAlgo);
        pPB->setObjectName(QStringLiteral("pPB"));
        pPB->setGeometry(QRect(670, 470, 91, 30));

        retranslateUi(task_RunAlgo);

        QMetaObject::connectSlotsByName(task_RunAlgo);
    } // setupUi

    void retranslateUi(QWidget *task_RunAlgo)
    {
        task_RunAlgo->setWindowTitle(QApplication::translate("task_RunAlgo", "Form", 0));
        evaluatePanel->setTitle(QString());
        cbIsEvalPerf->setText(QApplication::translate("task_RunAlgo", "Evaluate Perfomance", 0));
        browse_gtDir->setText(QApplication::translate("task_RunAlgo", "Selecting Groundtruth Directory", 0));
        txtGtDir->setText(QString());
        browse_resultDir->setText(QApplication::translate("task_RunAlgo", "Save Eval as", 0));
        txtResultDir->setText(QApplication::translate("task_RunAlgo", "Default save output to ~/../My Documents/xResults", 0));
        saveOutputPanel->setTitle(QString());
        saveImageFormat->setTitle(QApplication::translate("task_RunAlgo", "Output Images Format", 0));
        saveJPG->setText(QApplication::translate("task_RunAlgo", "jpg", 0));
        saveBMP->setText(QApplication::translate("task_RunAlgo", "bmp", 0));
        savePNG->setText(QApplication::translate("task_RunAlgo", "png", 0));
        cbIsSaveImage->setText(QApplication::translate("task_RunAlgo", "Export output Images", 0));
        txtSaveImageOutputPath->setText(QApplication::translate("task_RunAlgo", "E:\\QTWS\\dataset", 0));
        btnProcess->setText(QApplication::translate("task_RunAlgo", "PROCESS", 0));
        paramPanel->setTitle(QApplication::translate("task_RunAlgo", "Parameters :", 0));
        btnLoadDefaultConfig->setText(QApplication::translate("task_RunAlgo", "Load Default Parameters", 0));
        label->setText(QApplication::translate("task_RunAlgo", "Algorithms Selection", 0));

        const bool __sortingEnabled = selAlgo->isSortingEnabled();
        selAlgo->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = selAlgo->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("task_RunAlgo", "Select Method below or select this to Extract frame as images", 0));
        QListWidgetItem *___qlistwidgetitem1 = selAlgo->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("task_RunAlgo", "Basic methods-FrameDifferenceBGS", 0));
        QListWidgetItem *___qlistwidgetitem2 = selAlgo->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("task_RunAlgo", "Basic methods-DPMeanBGS", 0));
        QListWidgetItem *___qlistwidgetitem3 = selAlgo->item(3);
        ___qlistwidgetitem3->setText(QApplication::translate("task_RunAlgo", "Single gaussian based methods-LBSimpleGaussian", 0));
        QListWidgetItem *___qlistwidgetitem4 = selAlgo->item(4);
        ___qlistwidgetitem4->setText(QApplication::translate("task_RunAlgo", "Multiple gaussians based methods-DPGrimsonGMMBGS", 0));
        QListWidgetItem *___qlistwidgetitem5 = selAlgo->item(5);
        ___qlistwidgetitem5->setText(QApplication::translate("task_RunAlgo", "Type 2 Fuzzy based methods-T2FGMM_UM", 0));
        QListWidgetItem *___qlistwidgetitem6 = selAlgo->item(6);
        ___qlistwidgetitem6->setText(QApplication::translate("task_RunAlgo", "Multiple features based methods-DPTextureBGS", 0));
        QListWidgetItem *___qlistwidgetitem7 = selAlgo->item(7);
        ___qlistwidgetitem7->setText(QApplication::translate("task_RunAlgo", "Multiple features based methods-SJN_MultiCueBGS", 0));
        QListWidgetItem *___qlistwidgetitem8 = selAlgo->item(8);
        ___qlistwidgetitem8->setText(QApplication::translate("task_RunAlgo", "Multiple features based methods-LOBSTERBGS", 0));
        QListWidgetItem *___qlistwidgetitem9 = selAlgo->item(9);
        ___qlistwidgetitem9->setText(QApplication::translate("task_RunAlgo", "Multiple features based methods-SuBSENSEBGS", 0));
        QListWidgetItem *___qlistwidgetitem10 = selAlgo->item(10);
        ___qlistwidgetitem10->setText(QApplication::translate("task_RunAlgo", "Non parametric methods-KDE", 0));
        QListWidgetItem *___qlistwidgetitem11 = selAlgo->item(11);
        ___qlistwidgetitem11->setText(QApplication::translate("task_RunAlgo", "Non parametric methods-IndependentMultimodalBGS", 0));
        QListWidgetItem *___qlistwidgetitem12 = selAlgo->item(12);
        ___qlistwidgetitem12->setText(QApplication::translate("task_RunAlgo", "Non parametric methods-PBAS", 0));
        selAlgo->setSortingEnabled(__sortingEnabled);

        stepB->setText(QApplication::translate("task_RunAlgo", "Step", 0));
        pPB->setText(QApplication::translate("task_RunAlgo", "Play/Pause", 0));
    } // retranslateUi

};

namespace Ui {
    class task_RunAlgo: public Ui_task_RunAlgo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASK_RUNALGO_H
