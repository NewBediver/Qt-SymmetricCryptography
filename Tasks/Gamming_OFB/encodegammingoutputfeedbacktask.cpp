#include "encodegammingoutputfeedbacktask.h"

EncodeGammingOutputFeedbackTask::EncodeGammingOutputFeedbackTask(QWidget* parent) : MainTask(parent)
{
    changeTaskLabelText("Text to Gamming OFB encode:");
    changeResultLabelText("Gamming OFB encoded text:");
    changeMakeActionPushButtonText("Encode");
}

EncodeGammingOutputFeedbackTask::~EncodeGammingOutputFeedbackTask() {}
