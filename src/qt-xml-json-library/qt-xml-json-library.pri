QT += xml

# Library version
DEFINES += LIBRARY_VERSION=\\\"1.0.0\\\"

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD 

SOURCES += \
    $$PWD/cpp/jsontoxml.cpp \
    $$PWD/cpp/xmltojson.cpp \
    $$PWD/xmljsonconverter.cpp

HEADERS += \
    $$PWD/cpp/jsontoxml.h \
    $$PWD/cpp/xmltojson.h \
    $$PWD/xmljsonconverter.h
