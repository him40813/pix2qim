/********************************************************************************
** Form generated from reading UI file 'dialogrange.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGRANGE_H
#define UI_DIALOGRANGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <qlabelclick.h>

QT_BEGIN_NAMESPACE

class Ui_DialogRange
{
public:
    QDialogButtonBox *buttonBox;
    QLabelClick *imgLabel;
    QGroupBox *groupBox;
    QPushButton *ccBut;
    QPushButton *lcpBut;
    QPushButton *scpBut;
    QGroupBox *groupBox_2;
    QPushButton *fmBut;
    QPushButton *fcBut;
    QPushButton *lgpBut;
    QPushButton *sgpBut;
    QGroupBox *groupBox_3;
    QPushButton *sspBut;
    QLineEdit *lspTxt;
    QPushButton *lspBut;
    QLabel *statusLb;
    QGroupBox *groupBox_4;
    QLineEdit *agTxt;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *disTxt;
    QPushButton *calSimulateBut;

    void setupUi(QDialog *DialogRange)
    {
        if (DialogRange->objectName().isEmpty())
            DialogRange->setObjectName(QStringLiteral("DialogRange"));
        DialogRange->resize(1200, 800);
        buttonBox = new QDialogButtonBox(DialogRange);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(980, 750, 181, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        imgLabel = new QLabelClick(DialogRange);
        imgLabel->setObjectName(QStringLiteral("imgLabel"));
        imgLabel->setGeometry(QRect(30, 20, 960, 680));
        groupBox = new QGroupBox(DialogRange);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(980, 40, 201, 181));
        ccBut = new QPushButton(groupBox);
        ccBut->setObjectName(QStringLiteral("ccBut"));
        ccBut->setGeometry(QRect(10, 30, 181, 34));
        lcpBut = new QPushButton(groupBox);
        lcpBut->setObjectName(QStringLiteral("lcpBut"));
        lcpBut->setGeometry(QRect(10, 80, 181, 34));
        scpBut = new QPushButton(groupBox);
        scpBut->setObjectName(QStringLiteral("scpBut"));
        scpBut->setGeometry(QRect(10, 130, 181, 34));
        groupBox_2 = new QGroupBox(DialogRange);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(980, 230, 201, 231));
        fmBut = new QPushButton(groupBox_2);
        fmBut->setObjectName(QStringLiteral("fmBut"));
        fmBut->setGeometry(QRect(10, 30, 181, 34));
        fcBut = new QPushButton(groupBox_2);
        fcBut->setObjectName(QStringLiteral("fcBut"));
        fcBut->setGeometry(QRect(10, 80, 181, 34));
        lgpBut = new QPushButton(groupBox_2);
        lgpBut->setObjectName(QStringLiteral("lgpBut"));
        lgpBut->setGeometry(QRect(10, 130, 181, 34));
        sgpBut = new QPushButton(groupBox_2);
        sgpBut->setObjectName(QStringLiteral("sgpBut"));
        sgpBut->setGeometry(QRect(10, 180, 181, 34));
        groupBox_3 = new QGroupBox(DialogRange);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(980, 470, 201, 161));
        sspBut = new QPushButton(groupBox_3);
        sspBut->setObjectName(QStringLiteral("sspBut"));
        sspBut->setGeometry(QRect(10, 110, 181, 34));
        lspTxt = new QLineEdit(groupBox_3);
        lspTxt->setObjectName(QStringLiteral("lspTxt"));
        lspTxt->setGeometry(QRect(10, 30, 181, 25));
        lspBut = new QPushButton(groupBox_3);
        lspBut->setObjectName(QStringLiteral("lspBut"));
        lspBut->setGeometry(QRect(10, 60, 181, 34));
        statusLb = new QLabel(DialogRange);
        statusLb->setObjectName(QStringLiteral("statusLb"));
        statusLb->setGeometry(QRect(980, 10, 201, 31));
        QFont font;
        font.setPointSize(10);
        statusLb->setFont(font);
        groupBox_4 = new QGroupBox(DialogRange);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(980, 630, 201, 111));
        agTxt = new QLineEdit(groupBox_4);
        agTxt->setObjectName(QStringLiteral("agTxt"));
        agTxt->setGeometry(QRect(110, 30, 61, 27));
        label = new QLabel(groupBox_4);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 30, 68, 19));
        label_2 = new QLabel(groupBox_4);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 60, 68, 19));
        disTxt = new QLineEdit(groupBox_4);
        disTxt->setObjectName(QStringLiteral("disTxt"));
        disTxt->setGeometry(QRect(110, 60, 61, 27));
        calSimulateBut = new QPushButton(groupBox_4);
        calSimulateBut->setObjectName(QStringLiteral("calSimulateBut"));
        calSimulateBut->setGeometry(QRect(0, 90, 201, 21));
        imgLabel->raise();
        groupBox->raise();
        groupBox_2->raise();
        groupBox_3->raise();
        statusLb->raise();
        groupBox_4->raise();
        buttonBox->raise();

        retranslateUi(DialogRange);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogRange, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogRange, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogRange);
    } // setupUi

    void retranslateUi(QDialog *DialogRange)
    {
        DialogRange->setWindowTitle(QApplication::translate("DialogRange", "Global Coordinate Setup", 0));
        imgLabel->setText(QApplication::translate("DialogRange", "Picture", 0));
        groupBox->setTitle(QApplication::translate("DialogRange", "Camera", 0));
        ccBut->setText(QApplication::translate("DialogRange", "Calibrate Camera", 0));
        lcpBut->setText(QApplication::translate("DialogRange", "Load Camera Param", 0));
        scpBut->setText(QApplication::translate("DialogRange", "Save Camera Param", 0));
        groupBox_2->setTitle(QApplication::translate("DialogRange", "Ground Plane", 0));
        fmBut->setText(QApplication::translate("DialogRange", "From Image", 0));
        fcBut->setText(QApplication::translate("DialogRange", "From Camera", 0));
        lgpBut->setText(QApplication::translate("DialogRange", "Load Ground Param", 0));
        sgpBut->setText(QApplication::translate("DialogRange", "Save Ground Param", 0));
        groupBox_3->setTitle(QApplication::translate("DialogRange", "Setting", 0));
        sspBut->setText(QApplication::translate("DialogRange", "Save Setting Param", 0));
        lspBut->setText(QApplication::translate("DialogRange", "Load Setting Param", 0));
        statusLb->setText(QApplication::translate("DialogRange", "Status :", 0));
        groupBox_4->setTitle(QApplication::translate("DialogRange", "Simulate Ground", 0));
        label->setText(QApplication::translate("DialogRange", "Angle", 0));
        label_2->setText(QApplication::translate("DialogRange", "Distance", 0));
        disTxt->setText(QString());
        calSimulateBut->setText(QApplication::translate("DialogRange", "Calculate ", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogRange: public Ui_DialogRange {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGRANGE_H
