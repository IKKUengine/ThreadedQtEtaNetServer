#include <QtWidgets>
#include <QtNetwork>

#include <stdlib.h>
#include <QDebug>
#include "dialog.h"
#include "server.h"

Dialog::Dialog(QWidget *parent)
    : QWidget(parent)
{
    hostCombo = new QComboBox;
    portLineEdit = new QLineEdit();
    setIpPortButton = new QPushButton(tr("Set Interface"));

    messageLabel = new QLabel;
    messageLabel->setWordWrap(true);
    statusLabel = new QLabel;
    statusLabel->setWordWrap(true);
    quitButton = new QPushButton(tr("Quit"));
    quitButton->setAutoDefault(false);
    dqButton = new QPushButton(tr("Save Data"));
    dqButton->setAutoDefault(false);
    dqButton->setCheckable(true);
    hostLabel = new QLabel(tr("Network Interface:"));
    hostLabel->setBuddy(hostCombo);
    portLabel = new QLabel(tr("Server port:"));
    portLabel->setBuddy(portLineEdit);

    hostCombo->setEditable(true);
    // find out name of this machine
    QString name = QHostInfo::localHostName();

    if (name != QLatin1String("localhost"))
        hostCombo->addItem(QString("localhost"));
    // find out IP addresses of this machine
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // add non-localhost addresses
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            hostCombo->addItem(ipAddressesList.at(i).toString());
        }

    }
    // add localhost addresses
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i).isLoopback())
            hostCombo->addItem(ipAddressesList.at(i).toString());
    }
    portLineEdit->setText("50005");
    setIpPortButton->setEnabled(!hostCombo->currentText().isEmpty() &&
                                !portLineEdit->text().isEmpty());

    statusLabel->setText(tr("The \u03B7Net server ready to start."));
    messageLabel->setText(tr("Please select the network interface."));

    connect(quitButton, &QAbstractButton::clicked, this, &Dialog::close);
    connect(hostCombo, &QComboBox::currentTextChanged, this, &Dialog::networkInterface);
    connect(setIpPortButton, &QAbstractButton::clicked, this, &Dialog::setNetworkInterface);
    connect(portLineEdit, &QLineEdit::textChanged, this, &Dialog::networkInterface);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(setIpPortButton);
    buttonLayout->addWidget(dqButton);
    buttonLayout->addWidget(quitButton);
    buttonLayout->addStretch(1);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    //QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(statusLabel);
    mainLayout->addWidget(messageLabel);
    mainLayout->addWidget(hostLabel);
    mainLayout->addWidget(hostCombo);
    mainLayout->addWidget(portLabel);
    mainLayout->addWidget(portLineEdit);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
    setWindowTitle(tr("\u03B7Net Server v0.9.4"));
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

bool  Dialog::getDQButtonState(void)
{
   qDebug() << "ButtonState: " << dqButton->isChecked();
   return dqButton->isChecked();
}

void Dialog::networkInterface()
{
    if (!this->server.isListening())
    {
        setIpPortButton->setEnabled(!hostCombo->currentText().isEmpty() &&
                                !portLineEdit->text().isEmpty());

    }

}

void Dialog::setNetworkInterface()
{
    setIpPortButton->setEnabled(false);
    hostCombo->setVisible(false);
    portLineEdit->setVisible(false);
    portLabel->setVisible(false);
    hostLabel->setVisible(false);



    QString ipAddress;

    ipAddress = hostCombo->currentText();
    qDebug() << ipAddress;
    QHostAddress ipAddressQ(ipAddress);


    if (!this->server.listen(ipAddressQ, portLineEdit->text().toInt())) {
        QMessageBox::critical(this, tr("\u03B7Net Server"),
                              tr("Unable to start the server: %1.")
                              .arg(this->server.errorString()));
        this->close();
        return;
    }

//    // if we did not find one, use IPv4 localhost
//    if (ipAddress.isEmpty())
//        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    statusLabel->setText(tr("The \u03B7Net server is running on\n\nIP: %1\nport: %2\n\n"
                            "Run the \u03B7Net Clients now.")
                         .arg(ipAddress).arg(server.serverPort()));
    messageLabel->setText(tr("Wait for data from \u03B7Net clients..."));
}

void Dialog::close()
{
    hostCombo->deleteLater();
    portLineEdit->deleteLater();
    hostLabel->deleteLater();
    portLabel->deleteLater();
    QWidget::close();
}


