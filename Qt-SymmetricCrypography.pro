#-------------------------------------------------
#
# Project created by QtCreator 2019-09-14T18:02:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt-SymmetricCrypography
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        AboutWindow/aboutwindow.cpp \
        MainTask/maintask.cpp \
        Tasks/CBC/decodecipherblockchaining.cpp \
        Tasks/CBC/decodecipherblockchaining128task.cpp \
        Tasks/CBC/encodecipherblockchaining.cpp \
        Tasks/CBC/encodecipherblockchaining128task.cpp \
        Tasks/ECB/decodeelectroniccodebook128task.cpp \
        Tasks/ECB/decodeelectroniccodebooktask.cpp \
        Tasks/ECB/encodeelectroniccodebook128task.cpp \
        Tasks/ECB/encodeelectroniccodebooktask.cpp \
        Tasks/Gamming/decodegamming128task.cpp \
        Tasks/Gamming/decodegammingtask.cpp \
        Tasks/Gamming/encodegamming128task.cpp \
        Tasks/Gamming/encodegammingtask.cpp \
        Tasks/Gamming_CFB/decodegammingcipherfeedback128task.cpp \
        Tasks/Gamming_CFB/decodegammingcipherfeedbacktask.cpp \
        Tasks/Gamming_CFB/encodegammingcipherfeedback128task.cpp \
        Tasks/Gamming_CFB/encodegammingcipherfeedbacktask.cpp \
        Tasks/Gamming_OFB/decodegammingoutputfeedback128task.cpp \
        Tasks/Gamming_OFB/decodegammingoutputfeedbacktask.cpp \
        Tasks/Gamming_OFB/encodegammingoutputfeedback128task.cpp \
        Tasks/Gamming_OFB/encodegammingoutputfeedbacktask.cpp \
        Tasks/Message_Authentication_Code/CBC_MAC/cbcmac128task.cpp \
        Tasks/Message_Authentication_Code/CBC_MAC/cbcmactask.cpp \
        Tasks/Message_Authentication_Code/ECB_MAC/ecbmac128task.cpp \
        Tasks/Message_Authentication_Code/ECB_MAC/ecbmactask.cpp \
        Tasks/Message_Authentication_Code/GammingCFB_MAC/gammingcfbmac128task.cpp \
        Tasks/Message_Authentication_Code/GammingCFB_MAC/gammingcfbmactask.cpp \
        Tasks/Message_Authentication_Code/GammingOFB_MAC/gammingofbmac128task.cpp \
        Tasks/Message_Authentication_Code/GammingOFB_MAC/gammingofbmactask.cpp \
        Tasks/Message_Authentication_Code/Gamming_MAC/gammingmac128task.cpp \
        Tasks/Message_Authentication_Code/Gamming_MAC/gamminmactask.cpp \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        AboutWindow/aboutwindow.h \
        MainTask/maintask.h \
        Tasks/CBC/decodecipherblockchaining.h \
        Tasks/CBC/decodecipherblockchaining128task.h \
        Tasks/CBC/encodecipherblockchaining.h \
        Tasks/CBC/encodecipherblockchaining128task.h \
        Tasks/ECB/decodeelectroniccodebook128task.h \
        Tasks/ECB/decodeelectroniccodebooktask.h \
        Tasks/ECB/encodeelectroniccodebook128task.h \
        Tasks/ECB/encodeelectroniccodebooktask.h \
        Tasks/Gamming/decodegamming128task.h \
        Tasks/Gamming/decodegammingtask.h \
        Tasks/Gamming/encodegamming128task.h \
        Tasks/Gamming/encodegammingtask.h \
        Tasks/Gamming_CFB/decodegammingcipherfeedback128task.h \
        Tasks/Gamming_CFB/decodegammingcipherfeedbacktask.h \
        Tasks/Gamming_CFB/encodegammingcipherfeedback128task.h \
        Tasks/Gamming_CFB/encodegammingcipherfeedbacktask.h \
        Tasks/Gamming_OFB/decodegammingoutputfeedback128task.h \
        Tasks/Gamming_OFB/decodegammingoutputfeedbacktask.h \
        Tasks/Gamming_OFB/encodegammingoutputfeedback128task.h \
        Tasks/Gamming_OFB/encodegammingoutputfeedbacktask.h \
        Tasks/Message_Authentication_Code/CBC_MAC/cbcmac128task.h \
        Tasks/Message_Authentication_Code/CBC_MAC/cbcmactask.h \
        Tasks/Message_Authentication_Code/ECB_MAC/ecbmac128task.h \
        Tasks/Message_Authentication_Code/ECB_MAC/ecbmactask.h \
        Tasks/Message_Authentication_Code/GammingCFB_MAC/gammingcfbmac128task.h \
        Tasks/Message_Authentication_Code/GammingCFB_MAC/gammingcfbmactask.h \
        Tasks/Message_Authentication_Code/GammingOFB_MAC/gammingofbmac128task.h \
        Tasks/Message_Authentication_Code/GammingOFB_MAC/gammingofbmactask.h \
        Tasks/Message_Authentication_Code/Gamming_MAC/gammingmac128task.h \
        Tasks/Message_Authentication_Code/Gamming_MAC/gamminmactask.h \
        mainwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources/resources.qrc
