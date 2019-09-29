#include "gammingofbmac128task.h"

#include <QBitArray>
#include <QByteArray>

GammingOFBMAC128Task::GammingOFBMAC128Task(QWidget *parent) : MainTask(parent)
{
    changeTaskLabelText("Text to Gamming OFB-MAC encode:");
    changeResultLabelText("Gamming OFB-MAC encoded text:");
    changeMakeActionPushButtonText("Encode");
}

void GammingOFBMAC128Task::mainMethod()
{
    // Show it in the result text edit
    resultTextEdit->setPlainText("NOT IMPLEMENTED");
}

GammingOFBMAC128Task::~GammingOFBMAC128Task() {}
