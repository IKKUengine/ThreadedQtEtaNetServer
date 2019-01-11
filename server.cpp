#include "server.h"
#include "clientthread.h"
#include "dialog.h"

#include <stdlib.h>


EtaNetServer::EtaNetServer(QObject *parent)
    : QTcpServer(parent)
{
}

void EtaNetServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << "objekt erzeugt";
    EtaNetThread *thread = new EtaNetThread(socketDescriptor, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();

}
