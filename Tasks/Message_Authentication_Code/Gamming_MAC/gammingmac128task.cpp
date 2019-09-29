#include "gammingmac128task.h"

#include <QBitArray>
#include <QByteArray>

GammingMAC128Task::GammingMAC128Task(QWidget *parent) : MainTask(parent)
{
    changeTaskLabelText("Text to Gamming-MAC encode:");
    changeResultLabelText("Gamming-MAC encoded text:");
    changeMakeActionPushButtonText("Encode");
}

void GammingMAC128Task::mainMethod()
{
    // Show it in the result text edit
    resultTextEdit->setPlainText("NOT IMPLEMENTED");
}

GammingMAC128Task::~GammingMAC128Task() {}
