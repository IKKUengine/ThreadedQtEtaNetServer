#include <QApplication>
#include <QtCore>
#include <QDebug>

#include <stdlib.h>

#include "dialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Dialog::getInstance().show();
    return app.exec();
}
