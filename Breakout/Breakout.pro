QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Sources/arkanoid.cpp \
    Sources/ball.cpp \
    Sources/brick.cpp \
    Sources/paddle.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Headers/arkanoid.h \
    Headers/ball.h \
    Headers/brick.h \
    Headers/paddle.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    My_Resources.qrc \

#For setting icon in page
RC_ICONS = Images/arcanoid.ico
