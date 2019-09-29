#include "ecbmac128task.h"

#include <QBitArray>
#include <QByteArray>

ECBMAC128Task::ECBMAC128Task(QWidget *parent) : MainTask(parent)
{
    changeTaskLabelText("Text to ECB-MAC encode:");
    changeResultLabelText("ECB-MAC encoded text:");
    changeMakeActionPushButtonText("Encode");
}

void ECBMAC128Task::mainMethod()
{
    // Show it in the result text edit
    resultTextEdit->setPlainText("NOT IMPLEMENTED");
}

ECBMAC128Task::~ECBMAC128Task() {}
