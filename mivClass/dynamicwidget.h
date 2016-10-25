#ifndef DYNAMICWIDGET_H
#define DYNAMICWIDGET_H

#include <QStackedWidget>
#include <QComboBox>
#include <QWidget>
#include <QtGui>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QListWidgetItem>
#include <QListWidget>
#include <QSpinBox>
#include <QMessageBox>
#include <QMap>
#include <QObject>
#include <QObjectList>
#include <QGroupBox>
#include <QRegExp>
#include <QFileDialog>

namespace miv {

class dynamicWidget : public QWidget
{
    Q_OBJECT

    public:
        explicit dynamicWidget(QWidget *parent = 0);

    void makeWidget();
    void makeWidgetOnGroupbox(QGroupBox *parentWid, QMap<QString,QString> &param);
    void makeWidgetOnGrid(QGridLayout *parenWid, QMap<QString, QString> &childWid);
    void makeWidgetOnGrid(QGridLayout *parenWid, QMap<QString, double> &childWid);
    void makeWidgetOnGrid(QGridLayout *parenWid, QMap<QString, QVariant> &childWid);
    void getWidget2QMap(QWidget *parentWid,QMap<QString, QString> &output);
    void getWidget2QMap(QWidget *parentWid,QMap<QString, double> &output);
    void getWidget2QMap(QWidget *parentWid,QMap<QString, QVariant> &output);
};

}
#endif // DYNAMICWIDGET_H
