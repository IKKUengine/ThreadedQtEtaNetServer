QT += network widgets

QT += core sql

TARGET = EtaNetServerV0_9_1

HEADERS       = dialog.h \
                dbhandler.h \
                server.h \
                clientthread.h
SOURCES       = dialog.cpp \
                dbhandler.cpp \
                main.cpp \
                server.cpp \
                clientthread.cpp



