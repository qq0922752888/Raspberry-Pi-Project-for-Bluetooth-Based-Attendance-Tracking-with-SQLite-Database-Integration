QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
LIBS += -lsqlite3

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    BluetoothScanner.cpp \
    DatabaseManager.cpp \
    DeviceRegister.cpp \
    Login.cpp \
    LoginQt.cpp \
    SQLQuery.cpp \
    Scanner.cpp \
    functionmain.cpp \
    main.cpp

HEADERS += \
    BluetoothScanner.h \
    DatabaseManager.h \
    DeviceRegister.h \
    Login.h \
    LoginQt.h \
    SQLQuery.h \
    Scanner.h \
    functionmain.h

FORMS += \
    LoginQt.ui \
    functionmain.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Login.pro.user \
    Login.pro.user.a06a3f8 \
    Makefile \
    README.txt \
    data.db
