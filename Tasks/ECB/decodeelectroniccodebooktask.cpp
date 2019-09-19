#include "decodeelectroniccodebooktask.h"

DecodeElectronicCodeBookTask::DecodeElectronicCodeBookTask(QWidget* parent) : MainTask(parent)
{
    changeTaskLabelText("Text to ECB decode:");
    changeResultLabelText("ECB decoded text:");
    changeMakeActionPushButtonText("Decode");
}

DecodeElectronicCodeBookTask::~DecodeElectronicCodeBookTask() {}
