QT += network widgets

QT += core sql

HEADERS       = dialog.h \
                fortuneserver.h \
                fortunethread.h \
                dbhandler.h
SOURCES       = dialog.cpp \
                fortuneserver.cpp \
                fortunethread.cpp \
                dbhandler.cpp \
                main.cpp

# install
#target.path = E:\Softwareprojekte\etaNet\EtaNetManagement
#INSTALLS += target


