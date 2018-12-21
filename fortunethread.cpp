/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "fortunethread.h"

#include <QtNetwork>
#include "dialog.h"

#include <dbhandler.h>

static const QString path = "example.db";

EtaNetThread::EtaNetThread(int socketDescriptor, const QString &fortune, QObject *parent)
    : QThread(parent), socketDescriptor(socketDescriptor), text(fortune), tcpSocket(new QTcpSocket(this))
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
    qDebug() << "run fct";
    QThread::msleep(50);
}

void  EtaNetThread::read()
{

    qDebug() << "read funktion: vor db is open abfrage";
    //DbHandler db(path);
    in.startTransaction();

    QString message;
    in >> message;
    qDebug() << message;
//    int length = message.length();
//    if (db.isOpen() && length != 0)
//    {
//        if(!db.insertTuble(message)){
//            db.createTable(message);
//            db.insertTuble(message);
//        }
//    }
//    else
//    {
//        qDebug() << "Database is not open!";
//    }

    Dialog::getInstance().setTextLabel(message);

    if (!in.commitTransaction())
        return;


    //-------------------------------------------------------------------------------
    if(tcpSocket->isWritable())
    {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << text;

    tcpSocket->write(block);
    tcpSocket->disconnectFromHost();
    tcpSocket->waitForDisconnected();
    }
 //   if (nextFortune == currentFortune) {
 //       QTimer::singleShot(0, this, &Client::requestNewFortune);
 //       return;
 //   }

}
