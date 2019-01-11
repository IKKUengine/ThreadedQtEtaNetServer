#include <QApplication>
#include <QtCore>
#include <QDebug>

#include <stdlib.h>

#include "dialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Dialog::getInstance().show();
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    return app.exec();
}
