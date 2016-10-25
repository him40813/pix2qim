#include "dynamicwidget.h"

using namespace miv;



void dynamicWidget::makeWidget()
{

}

void dynamicWidget::makeWidgetOnGroupbox(QGroupBox *parentWid, QMap<QString,QString> &param)
{
        QHBoxLayout *inner = new QHBoxLayout;
        QVBoxLayout *outer = new QVBoxLayout;
        QMapIterator<QString, QString> i(param);
        while (i.hasNext()) {
            i.next();

            if( i.value().split('.').size() > 1 )  /// Create QDoubleSpinBox
            {
                QLabel *b1 = new QLabel( i.key() );
                QDoubleSpinBox *b2 = new QDoubleSpinBox();
                b2->setValue( i.value().toDouble() );
                inner->addWidget(b1);
                inner->addWidget(b2);
            }
            else    /// Create QSpinBox
            {
                QLabel *b1 = new QLabel( i.key() );
                QSpinBox *b2 = new QSpinBox();
                b2->setValue( i.value().toInt() );
                inner->addWidget(b1);
                inner->addWidget(b2);
            }
            outer->addLayout(inner);
        }

            parentWid->setLayout(outer);
}

void dynamicWidget::makeWidgetOnGrid(QGridLayout *parenWid, QMap<QString, QString> &childWid)
{

    int gCol = 0, gRow = 0;
    int gColMax = 4;
    QMapIterator<QString, QString> i(childWid);
    while (i.hasNext())
    {

        i.next();

        if( i.value().split('.').size() > 1 )  /// Create QDoubleSpinBox
        {

            QLabel *txtName = new QLabel( i.key() );
            txtName->setObjectName( "lbl"+i.key() );
            QDoubleSpinBox *widObj = new QDoubleSpinBox();
            widObj->setObjectName( i.key() );
            widObj->setValue( i.value().toDouble() );
            widObj->setDecimals(3);
            parenWid->addWidget(txtName,gRow,gCol  ,1,1);
            parenWid->addWidget(widObj, gRow,gCol+1,1,1);
        }
        else    /// Create QSpinBox
        {
            QLabel *txtName = new QLabel( i.key() );
            txtName->setObjectName( "lbl"+i.key() );
            QSpinBox *widObj = new QSpinBox();
            widObj->setObjectName( i.key() );
            widObj->setMaximum(255);
            widObj->setValue( i.value().toInt() );
            parenWid->addWidget(txtName,gRow,gCol  ,1,1);
            parenWid->addWidget(widObj, gRow,gCol+1,1,1);
        }

        gCol+=2;

        if (gCol != 0 && (gCol % gColMax) == 0)
        {
            gRow++;
            gCol = 0;
        }
    }
}

/// Overload with QMap <QString, double>
void dynamicWidget::makeWidgetOnGrid(QGridLayout *parenWid, QMap<QString, double> &childWid)
{
    /// Checking if QMap is empty
    if (childWid.isEmpty() || ( childWid.count() == 1 && childWid.firstKey() == "showOutput") )
    {
        QLabel *txtName = new QLabel( "No parameter setting avialable" );
        txtName->setObjectName( "lblBlank" );
        parenWid->addWidget(txtName,0,0,1,1);
    }
    else
    {
        int gCol = 0, gRow = 0;
        int gColMax = 4;
        QMapIterator<QString, double> i(childWid);
        while (i.hasNext())
        {
            i.next();
            if (i.key() != "showOutput")
            {
                QString chkNum( QString::number(i.value()) );

                if( chkNum.split('.').size() > 1 )  /// Create QDoubleSpinBox
                {
                    QLabel *txtName = new QLabel( i.key() );
                    txtName->setObjectName( "lbl"+i.key() );
                    QDoubleSpinBox *widObj = new QDoubleSpinBox();
                    widObj->setObjectName( i.key() );
                    widObj->setValue( i.value() );
                    widObj->setDecimals(3);
                    parenWid->addWidget(txtName,gRow,gCol  ,1,1);
                    parenWid->addWidget(widObj, gRow,gCol+1,1,1);
                }
                else    /// Create QSpinBox
                {
                    QLabel *txtName = new QLabel( i.key() );
                    txtName->setObjectName( "lbl"+i.key() );
                    QSpinBox *widObj = new QSpinBox();
                    widObj->setObjectName( i.key() );
                     widObj->setMaximum(255);
                    widObj->setValue( i.value() );
                    parenWid->addWidget(txtName,gRow,gCol  ,1,1);
                    parenWid->addWidget(widObj, gRow,gCol+1,1,1);
                }

                gCol+=2;

                if (gCol != 0 && (gCol % gColMax) == 0)
                {
                    gRow++;
                    gCol = 0;
                }
            } // END Inner IF
        } // END WHILE
    } // END Outer IF-ELSE
}

/// Overload with QVariant
void dynamicWidget::makeWidgetOnGrid(QGridLayout *parenWid, QMap<QString, QVariant> &childWid)
{
    /// Checking if QMap is empty or containt only non method's parameter
    if (childWid.isEmpty() || ( childWid.count() == 1 && childWid.firstKey() == "showOutput") )
    {
        QLabel *txtName = new QLabel( "No parameter setting avialable" );
        txtName->setObjectName( "lblBlank" );
        parenWid->addWidget(txtName,0,0,1,1);
    }
    else
    {       
        int gCol = 0, gRow = 0,gColMax;
        /// Layouting as two column if widget more than 8
        if(childWid.count() > 8)
            gColMax = 4;
        else
            gColMax = 1;
        QMapIterator<QString, QVariant> i(childWid);
        while (i.hasNext())
        {
            i.next();
            if (i.key() != "showOutput")
            {

                if( i.value().type() == QVariant::Double )  /// Create QDoubleSpinBox
                {
                    QLabel *txtName = new QLabel( i.key() );
                    txtName->setObjectName( "lbl"+i.key() );
                    QDoubleSpinBox *widObj = new QDoubleSpinBox();
                    widObj->setObjectName( i.key() );
                    widObj->setValue(  i.value().toDouble() );
                    widObj->setDecimals(3);
                    parenWid->addWidget(txtName,gRow,gCol  ,1,1);
                    parenWid->addWidget(widObj, gRow,gCol+1,1,1);
                }
                else    /// Create QSpinBox
                {
                    QLabel *txtName = new QLabel( i.key() );
                    txtName->setObjectName( "lbl"+i.key() );
                    QSpinBox *widObj = new QSpinBox();
                    widObj->setObjectName( i.key() );
                    widObj->setMaximum(255);
                    widObj->setValue( i.value().toInt() );
                    parenWid->addWidget(txtName,gRow,gCol  ,1,1);
                    parenWid->addWidget(widObj, gRow,gCol+1,1,1);
                }

                gCol+=2;

                if (gCol != 0 && (gCol % gColMax) == 0)
                {
                    gRow++;
                    gCol = 0;
                }
            } // END Inner IF
        } // END WHILE
    } // END Outer IF-ELSE
}

void dynamicWidget::getWidget2QMap(QWidget *parentWid,QMap<QString, QString> &output)
{
    for (int i = 0; i < parentWid->layout()->count(); ++i)
    {
      QWidget *widget = parentWid->layout()->itemAt(i)->widget();

      if (widget != NULL)
      {

          if(QDoubleSpinBox *obj = qobject_cast<QDoubleSpinBox * >(widget))
          {
              output.insert(obj->objectName(),QString::number(obj->value()) );
              //qDebug()<<widget->metaObject()->className();
          }
          else if(QSpinBox *obj = qobject_cast<QSpinBox * >(widget))
          {
              output.insert(obj->objectName(),QString::number(obj->value()));
              //qDebug()<<widget->metaObject()->className();
          }

      }

    }
}

/// Overload with QMap<QString, double>
void dynamicWidget::getWidget2QMap(QWidget *parentWid,QMap<QString, double> &output)
{
    QString parentName = parentWid->layout()->objectName();
    output.insert("."+parentName,0.0);

    for (int i = 0; i < parentWid->layout()->count(); ++i)
    {
      QWidget *widget = parentWid->layout()->itemAt(i)->widget();

      if (widget != NULL)
      {

          if(QDoubleSpinBox *obj = qobject_cast<QDoubleSpinBox * >(widget))
          {
              output.insert(obj->objectName(),obj->value() );
              //qDebug()<<widget->metaObject()->className();
          }
          else if(QSpinBox *obj = qobject_cast<QSpinBox * >(widget))
          {
              output.insert(obj->objectName(),obj->value() );
              //qDebug()<<widget->metaObject()->className();
          }

      }

    }
}

/// Overload with QMap<QString, QVariant>
void dynamicWidget::getWidget2QMap(QWidget *parentWid,QMap<QString, QVariant> &output)
{
    //QString parentName = parentWid->layout()->objectName();
    //output.insert("."+parentName,0.0);

    for (int i = 0; i < parentWid->layout()->count(); ++i)
    {
      QWidget *widget = parentWid->layout()->itemAt(i)->widget();

      if (widget != NULL)
      {

          if(QDoubleSpinBox *obj = qobject_cast<QDoubleSpinBox * >(widget))
          {
              output.insert(obj->objectName(),obj->value() );
          }
          else if(QSpinBox *obj = qobject_cast<QSpinBox * >(widget))
          {
              output.insert(obj->objectName(),obj->value() );
          }

      }

    }
}
