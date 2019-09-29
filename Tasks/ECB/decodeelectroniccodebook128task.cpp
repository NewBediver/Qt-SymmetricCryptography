#include "decodeelectroniccodebook128task.h"

#include <QByteArray>
#include <QBitArray>

DecodeElectronicCodeBook128Task::DecodeElectronicCodeBook128Task(QWidget* parent) : MainTask(parent)
{
    changeTaskLabelText("Text to ECB decode:");
    changeResultLabelText("ECB decoded text:");
    changeMakeActionPushButtonText("Decode");
}

void DecodeElectronicCodeBook128Task::mainMethod()
{
    // Show it in the result text edit
    resultTextEdit->setPlainText("NOT IMPLEMENTED");
}

DecodeElectronicCodeBook128Task::~DecodeElectronicCodeBook128Task() {}
