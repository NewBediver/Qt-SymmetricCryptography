#include "decodegammingtask.h"

DecodeGammingTask::DecodeGammingTask(QWidget* parent) : MainTask(parent)
{
    changeTaskLabelText("Text to Gamming decode:");
    changeResultLabelText("Gamming decoded text:");
    changeMakeActionPushButtonText("Decode");
}

DecodeGammingTask::~DecodeGammingTask() {}
