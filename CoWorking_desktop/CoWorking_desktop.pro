QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AppController.cpp \
    AuthorizationWindow/AuthorizationWindow.cpp \
    AuthorizationWindow/LoginWigdet.cpp \
    AuthorizationWindow/SignupWidget.cpp \
    MainWindow/BookingItem.cpp \
    MainWindow/BookingsView.cpp \
    MainWindow/CoworkingDesktop.cpp \
    MainWindow/MenuWidget.cpp \
    Network/NetworkManager.cpp \
    main.cpp

HEADERS += \
    AppController.h \
    AuthorizationWindow/AuthorizationWindow.h \
    AuthorizationWindow/LoginWigdet.h \
    AuthorizationWindow/SignupWidget.h \
    MainWindow/BookingItem.h \
    MainWindow/BookingsView.h \
    MainWindow/CoworkingDesktop.h \
    MainWindow/MenuWidget.h \
    Network/NetworkManager.h

FORMS += \
    appication.ui \
    authorizationwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
