#ifndef DIALOG_H
#define DIALOG_H

#include <QWidget>
#include "server.h"


QT_BEGIN_NAMESPACE
class QComboBox;
class QLineEdit;
class QLabel;
class QPushButton;

QT_END_NAMESPACE

/**
 * \class Dialog
 *
 * \brief The Dialog class is the base class of dialog windows.
 *
 * The dialog window is a top-level window used for server tasks and communications with the field element clients.
 * Singleton pattern: only one instance of the class should created.
 */
class Dialog : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Global access point to the Singleton.
     * @return Pointer to the static instance.
     */
    static Dialog& getInstance();
    /**
     * @brief Set the text of the text label.
     * @param text - text of the label.
     *
     */
    void setTextLabel(QString text);
    /**
     * @brief Gets DQ Button state
     * @return Bool: True is pushed
     *
     */
    bool getDQButtonState(void);

private:
    /**
     * @brief Constructor
     *
     *
     * Constructor sets up connection with db and opens it
     * @param path - absolute path to db file
     */
    Dialog(QWidget *parent = 0);
    /**
     * @brief Destructor
     *
     * Close the db connection
     */
    Dialog(const Dialog&);

 //slots:
    void networkInterface(void);
    void setNetworkInterface(void);
    void close(void);


private:
    QComboBox *hostCombo;
    QLineEdit *portLineEdit;
    QPushButton *setIpPortButton;
    QLabel *hostLabel;
    QLabel *portLabel;
    /**
     * @brief label - is used for displaying text
     */
    QLabel *statusLabel;
    /**
     * @brief label - is used for displaying text
     */
    QLabel *messageLabel;
    /**
     * @brief button - is used for close the dialog window
     */
    QPushButton *quitButton;
    /**
     * @brief button - is used for start and stop of data acquisition
     */
    QPushButton *dqButton;
    /**
     * @brief server - creates the server instance
     */
    EtaNetServer server;

};

#endif
