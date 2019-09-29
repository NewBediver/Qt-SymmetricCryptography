#include "gammingcfbmac128task.h"

#include <QBitArray>
#include <QByteArray>

GammingCFBMAC128Task::GammingCFBMAC128Task(QWidget *parent) : MainTask(parent)
{
    changeTaskLabelText("Text to Gamming CFB-MAC encode:");
    changeResultLabelText("Gamming CFB-MAC encoded text:");
    changeMakeActionPushButtonText("Encode");
}

void GammingCFBMAC128Task::mainMethod()
{
    // Show it in the result text edit
    resultTextEdit->setPlainText("NOT IMPLEMENTED");
}

GammingCFBMAC128Task::~GammingCFBMAC128Task() {}
