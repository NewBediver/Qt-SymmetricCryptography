#include "encodeelectroniccodebooktask.h"

EncodeElectronicCodeBookTask::EncodeElectronicCodeBookTask(QWidget* parent) : MainTask(parent)
{
    changeTaskLabelText("Text to ECB encode:");
    changeResultLabelText("ECB encoded text:");
    changeMakeActionPushButtonText("Encode");
}

EncodeElectronicCodeBookTask::~EncodeElectronicCodeBookTask() {}
