TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    menu.c \
    mrowka.c

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    mrowka.h \
    menu.h

