#include "clientthread.h"

#include <QtNetwork>
#include "dialog.h"

#include <dbhandler.h>


static QString oldValue;


EtaNetThread::EtaNetThread(int socketDescriptor, QObject *parent)
    : QThread(parent), tcpSocket(new QTcpSocket(this)), socketDescriptor(socketDescriptor)
{
    if (!tcpSocket->setSocketDescriptor(socketDescriptor)) {
        emit error(tcpSocket->error());
        return;
    }
    in.setDevice(tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);
    connect(this->tcpSocket, &QIODevice::readyRead, this, &EtaNetThread::read);
    qDebug() << "pass thead construktor";
}

void EtaNetThread::run()
{

    QThread::msleep(50);
    qDebug() << "run fct";
}

void  EtaNetThread::read()
{
    qDebug() << "read funktion: vor db is open abfrage";
    DbHandler db;
    in.startTransaction();
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    QString message;
    QString feedback;
    in >> message;
    int length = message.length();
    if(length != 0)
    {
        bool y,z,w ;
        y = message[0] == 'E';
        z = message[1] == '5';
        w = message.length() == 2;
        QStringList messageList = message.split(" (");
        if (!(y && z && w))
        {
            if (db.isOpen())
            {
                QString text = "Message received from " + messageList[0];
                qDebug() <<  messageList[0];
                Dialog::getInstance().setTextLabel(text);
                db.createControllTable(message);

                if(Dialog::getInstance().getDQButtonState())
                {
                    if(db.createMonitoringTable(message)){
                        db.insertMonitoringTuble(message);
                        QString value = db.selectControllValues(messageList[0]);
                        if (value == oldValue)
                        {
                            feedback = "E5";
                        }
                        else
                        {
                            feedback = value;
                            oldValue = value;
                            Dialog::getInstance().setTextLabel("\u03B7Net server is configuring...");
                        }
                    }
                    else
                    {
                        Dialog::getInstance().setTextLabel("Wrong messages from " + messageList[0]);
                        feedback = "F6";
                    }
                }
                else
                {
                    qDebug() << "Meauerment stops";
                    if(db.createMonitoringTable(message)){
                        db.updateLastMonitoringTuble(message);
                        QString value = db.selectControllValues(messageList[0]);
                        if (value == oldValue)
                        {
                            feedback = "E5";
                        }
                        else
                        {
                            feedback = value;
                            oldValue = value;
                            Dialog::getInstance().setTextLabel("\u03B7Net server responds...");
                        }
                    }
                    else
                    {
                        Dialog::getInstance().setTextLabel("Wrong messages from " + messageList[0]);
                        feedback = "F6";
                    }
                }

            }
            else
            {
                qDebug() << "Database is not open!";
                Dialog::getInstance().setTextLabel("Database is not open!");
                feedback = "F7";
            }
        }
        else
        {
             if (db.isOpen())
             {
                 QString value = db.selectControllValues(messageList[0]);
                 if (value == oldValue)
                 {
                     feedback = "E5";
                 }
                 else
                 {
                     feedback = value;
                     oldValue = value;
                     Dialog::getInstance().setTextLabel("\u03B7Net server is configuring...");
                 }
             }
             else
             {
                 qDebug() << "Database is not open!";
                 Dialog::getInstance().setTextLabel("Database is not open!");
                 feedback = "F7";
             }
        }
     }
    else
    {
        Dialog::getInstance().setTextLabel("\u03B7Net server gets no messages!");
        feedback = "F8";
    }
    if (!in.commitTransaction())
        return;

    if(tcpSocket->isWritable())
    {
        out << feedback;
        qDebug() << feedback;
        tcpSocket->write(block);
        tcpSocket->disconnectFromHost();
        tcpSocket->waitForDisconnected();
    }


}
