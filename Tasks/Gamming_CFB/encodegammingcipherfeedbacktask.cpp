#include "encodegammingcipherfeedbacktask.h"

EncodeGammingCipherFeedbackTask::EncodeGammingCipherFeedbackTask(QWidget* parent) : MainTask(parent)
{
    changeTaskLabelText("Text to Gamming CFB encode:");
    changeResultLabelText("Gamming CFB encoded text:");
    changeMakeActionPushButtonText("Encode");
}

EncodeGammingCipherFeedbackTask::~EncodeGammingCipherFeedbackTask() {}
