#include "encodeimitationinserttask.h"

EncodeImitationInsertTask::EncodeImitationInsertTask(QWidget* parent) : MainTask(parent)
{
    changeTaskLabelText("Text to Imitation Insert encode:");
    changeResultLabelText("Imitation Insert encoded text:");
    changeMakeActionPushButtonText("Encode");
}

EncodeImitationInsertTask::~EncodeImitationInsertTask() {}
