#include "cbcmac128task.h"

#include <QBitArray>
#include <QByteArray>

CBCMAC128Task::CBCMAC128Task(QWidget *parent) : MainTask(parent)
{
    changeTaskLabelText("Text to CBC-MAC encode:");
    changeResultLabelText("CBC-MAC encoded text:");
    changeMakeActionPushButtonText("Encode");
}

void CBCMAC128Task::mainMethod()
{
    // Show it in the result text edit
    resultTextEdit->setPlainText("NOT IMPLEMENTED");
}

CBCMAC128Task::~CBCMAC128Task() {}
