#include <QtWidgets>
#include <QtNetwork>

#include <stdlib.h>

#include "dialog.h"
#include "server.h"

Dialog::Dialog(QWidget *parent)
    : QWidget(parent)
{
    messageLabel = new QLabel;
    messageLabel->setWordWrap(true);
    statusLabel = new QLabel;
    statusLabel->setWordWrap(true);
    quitButton = new QPushButton(tr("Quit"));
    quitButton->setAutoDefault(false);

    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }

    QHostAddress ipAddressQ(ipAddress);


    if (!server.listen(ipAddressQ, 50005)) {
        QMessageBox::critical(this, tr("\u03B7Net Server"),
                              tr("Unable to start the server: %1.")
                              .arg(server.errorString()));
        this->close();
        return;
    }

    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    statusLabel->setText(tr("The \u03B7Net server is running on\n\nIP: %1\nport: %2\n\n"
                            "Run the \u03B7Net Clients now.")
                         .arg(ipAddress).arg(server.serverPort()));
    messageLabel->setText(tr("Wait for data from \u03B7Net clients..."));

    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(quitButton);
    buttonLayout->addStretch(1);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(statusLabel);
    mainLayout->addWidget(messageLabel);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
    setWindowTitle(tr("\u03B7Net Server"));
}

Dialog& Dialog::getInstance()
{
    static Dialog instance;
    return instance;
}

void  Dialog::setTextLabel(QString text)
{
    messageLabel->setText(text);
}

