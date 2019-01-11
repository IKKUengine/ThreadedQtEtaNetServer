#ifndef SERVER_H
#define SERVER_H

#include <QStringList>
#include <QTcpServer>

/**
 * \class EtaNetServer
 *
 * \brief The EtaNetServer makes it possible to accept incoming TCP connections.
 *
 * You can listen on a specific address or on all the machine's addresses.
 */
class EtaNetServer : public QTcpServer
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     */
    EtaNetServer(QObject *parent = 0);

protected:
    /**
     * @brief This virtual function is called by server when a new connection is available.
     * @param socket descriptor - is the native socket descriptor for the accepted connection
     *
     */
    void incomingConnection(qintptr socketDescriptor) override;

private:
    QStringList fortunes;
};


#endif
