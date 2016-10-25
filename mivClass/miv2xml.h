#ifndef MIV2XML
#define MIV2XML
// Standard LIB
#include <iostream>
// QT LIB
#include <QtCore>
#include <QFile>
#include <QMessageBox>
#include <QDomDocument>

// Opencv LIB
// Internal LIB
// External LIB

using namespace std;

class miv2xml{
    private :
        QFileInfo fileName;
        QDomDocument doc;
        QFile file;
        QDomElement root;
        QDomElement element;
        bool fileState = true;
        bool checkFileOpen();
        bool checkFileParse();

    public :
        miv2xml(QString fname);
        bool writeXMLFile(QMap<QString, double> &inputData);
        bool readXMLFile(QMap<QString, double> &inputData,QString &targetTag);
        bool readXMLFile(QMap<QString, QVariant> &inputData);
};

// Constructor
inline miv2xml::miv2xml(QString fname):fileName(fname),file(fname)
{
    // get filename based

    // create QDomDocument // create QFile
    doc = QDomDocument(fileName.baseName());
    // Check file status
    checkFileOpen();
}

inline bool miv2xml::checkFileOpen()
{
    // check QFile can open
    if (!file.open(QIODevice::ReadWrite))
    {
        std::cerr << "error opening output file\n";
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("error opening output file");
        msgBox.exec();
        return fileState = false;
    }
    qDebug() << "File open OK";
    return fileState = true;
}

inline bool miv2xml::checkFileParse()
{
    // if can open then check Parse file
    if (!doc.setContent(&file))
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("error can't parse file");
        msgBox.exec();
        return fileState = false;
     }

    qDebug() << "File parsing OK";
    return fileState = true;
}


inline bool miv2xml::writeXMLFile(QMap<QString, double> &inputData)
{
    if (fileState) // check file ready
    {
        QString parentTag(inputData.firstKey());
        parentTag.remove(0,1);
        qDebug()<<"Create New File"<<parentTag;

        // check file is null
        if (!checkFileParse()) // Create new one.
        {
            root = doc.createElement("Method");
            doc.appendChild(root);
            QDomElement newParentNode = doc.createElement(parentTag);   // create a new Parent node
            /// Iteration create child nodes
            QMapIterator<QString, double> j(inputData);
            while (j.hasNext())
            {
                j.next();
                if (j.key() != inputData.firstKey())   // Skip Parent
                {
                    QDomElement newChildNode = doc.createElement(j.key());   // child tag
                    newChildNode.appendChild(doc.createTextNode( QString::number(j.value()) )); // child value
                    newParentNode.appendChild(newChildNode);    // append value to tag
                    //qDebug()<< j.key() << j.value();
                }
            }
            root.appendChild(newParentNode);
            qDebug() << "Create New finished";
        }

        else //Update
        {
            root = doc.documentElement();
            element = root.firstChildElement(parentTag);

            if(element.isNull())    // Write new node.
            {
                qDebug()<< "Create New node";
                QDomElement newParentNode = doc.createElement(parentTag);   // create a new Parent node
                /// Iteration create child nodes
                QMapIterator<QString, double> j(inputData);
                while (j.hasNext())
                {
                    j.next();
                    if (j.key() != inputData.firstKey())   // Skip Parent
                    {
                        QDomElement newChildNode = doc.createElement(j.key());   // child tag
                        newChildNode.appendChild(doc.createTextNode( QString::number(j.value()) )); // child value
                        newParentNode.appendChild(newChildNode);    // append value to tag

                    }
                }
                root.appendChild(newParentNode);
                qDebug() << "Update with New node finished";
            }
            else    // Update exist node.
            {
                qDebug()<< "Update Existed node";
                QDomElement newParentNode = doc.createElement(parentTag);   // create a new Parent node
                /// Iteration create child nodes
                QMapIterator<QString, double> j(inputData);
                while (j.hasNext())
                {
                    j.next();
                    if (j.key() != inputData.firstKey())   // Skip Parent
                    {
                        QDomElement newChildNode = doc.createElement(j.key());   // child tag
                        newChildNode.appendChild(doc.createTextNode( QString::number(j.value()) )); // child value
                        newParentNode.appendChild(newChildNode);    // append value to tag

                    }
                }
                root.replaceChild(newParentNode,element);
                qDebug() << "Update Existed node finished";
            }
        }



        // Write to Disk
        file.resize(0);
        QTextStream stream;
        stream.setDevice(&file);
        doc.save(stream, 4);
        file.close();

        qDebug() << "Write completed";
        return fileState = true;
    }
    return fileState = false;
}


//// Read XML and return output to QMAP Object
inline bool miv2xml::readXMLFile(QMap<QString, double> &inputData,QString &targetTag)
{
    if (fileState && checkFileParse()) // check file ready
    {

        root = doc.documentElement();
        element = root.firstChildElement(targetTag);

        for(int j = 0;j < element.childNodes().count(); j++)
        {
            QDomElement childElement = element.childNodes().at(j).toElement();
            inputData[childElement.tagName()] = childElement.text().toDouble();
//            qDebug()<<childElement.tagName();
//            qDebug()<<childElement.text();
        }

        file.close();
        return fileState = true;
    }

    return fileState = false;
}

/// overload for one parent node
inline bool miv2xml::readXMLFile(QMap<QString, QVariant> &inputData)
{
    if (fileState && checkFileParse()) // check file ready
    {
        element = doc.documentElement();

        for(QDomNode n = element.firstChild(); !n.isNull(); n = n.nextSibling())
        {
            QDomElement childElement = n.toElement();
            inputData[childElement.tagName()] = childElement.text().toDouble();
        }

        file.close();
        return fileState = true;
    }

    return fileState = false;
}

#endif // MIV2XML

