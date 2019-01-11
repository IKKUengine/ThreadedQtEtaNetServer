#ifndef FORTUNETHREAD_H
#define FORTUNETHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QDataStream>

/**
 * \class EtaNetThread
 *
 * \brief A EtaNetThread provides a way to manage threads.
 *
 * For each connection will be create a new thread. Each thread handle a incomming message from the clients.
 */
class EtaNetThread : public QThread
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     */
    EtaNetThread(int socketDescriptor, QObject *parent);

    /**
     * @brief After calling start(), the newly created thread calls this virtual function.
     *
     */
    void run() override;

signals:
    /**
     * @brief Is used for displaying socket errors
     *
     */
    void error(QTcpSocket::SocketError socketError);

private slots:
    /**
     * @brief Is used for start transactions between server and client
     *
     */
    void read();

private:
    /**
     * @brief data stream - is a binary stream of encoded information
     */
    QDataStream in;
    /**
     * @brief TCP socket -  provides a TCP socket
     */
    QTcpSocket* tcpSocket;
    /**
     * @brief socket descriptor - is the native socket descriptor for the accepted connection
     */
    int socketDescriptor;
};


#endif
