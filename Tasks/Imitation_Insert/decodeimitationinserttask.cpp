#include "decodeimitationinserttask.h"

DecodeImitationInsertTask::DecodeImitationInsertTask(QWidget* parent) : MainTask(parent)
{
    changeTaskLabelText("Text to Imitation Insert decode:");
    changeResultLabelText("Imitation Insert decoded text:");
    changeMakeActionPushButtonText("Decode");
}

DecodeImitationInsertTask::~DecodeImitationInsertTask() {}
