#include "encodegammingtask.h"

EncodeGammingTask::EncodeGammingTask(QWidget* parent) : MainTask(parent)
{
    changeTaskLabelText("Text to Gamming encode:");
    changeResultLabelText("Gamming encoded text:");
    changeMakeActionPushButtonText("Encode");
}

EncodeGammingTask::~EncodeGammingTask() {}
