#include "encodeelectroniccodebook128task.h"

#include <QByteArray>
#include <QBitArray>

EncodeElectronicCodeBook128Task::EncodeElectronicCodeBook128Task(QWidget* parent) : MainTask(parent)
{
    changeTaskLabelText("Text to ECB encode:");
    changeResultLabelText("ECB encoded text:");
    changeMakeActionPushButtonText("Encode");
}

void EncodeElectronicCodeBook128Task::mainMethod()
{
    // Show it in the result text edit
    resultTextEdit->setPlainText("NOT IMPLEMENTED");
}

EncodeElectronicCodeBook128Task::~EncodeElectronicCodeBook128Task() {}
