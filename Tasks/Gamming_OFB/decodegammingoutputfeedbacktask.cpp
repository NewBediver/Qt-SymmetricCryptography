#include "decodegammingoutputfeedbacktask.h"

DecodeGammingOutputFeedbackTask::DecodeGammingOutputFeedbackTask(QWidget* parent) : MainTask(parent)
{
    changeTaskLabelText("Text to Gamming OFB decode:");
    changeResultLabelText("Gamming OFB decoded text:");
    changeMakeActionPushButtonText("Decode");
}

DecodeGammingOutputFeedbackTask::~DecodeGammingOutputFeedbackTask() {}
