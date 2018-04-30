QT     += quick qml
CONFIG += c++11

TARGET = languagelesson
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
    worddatabase.cpp \
    wordpairmodel.cpp

HEADERS += \
    worddatabase.h \
    wordpairmodel.h

RESOURCES += \
    qml.qrc
