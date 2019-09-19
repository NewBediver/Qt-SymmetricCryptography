#include "decodegammingcipherfeedbacktask.h"

DecodeGammingCipherFeedbackTask::DecodeGammingCipherFeedbackTask(QWidget* parent) : MainTask(parent)
{
    changeTaskLabelText("Text to Gamming CFB decode:");
    changeResultLabelText("Gamming CFB decoded text:");
    changeMakeActionPushButtonText("Decode");
}

DecodeGammingCipherFeedbackTask::~DecodeGammingCipherFeedbackTask() {}
