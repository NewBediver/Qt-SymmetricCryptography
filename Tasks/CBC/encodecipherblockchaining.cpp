#include "encodecipherblockchaining.h"

EncodeCipherBlockChaining::EncodeCipherBlockChaining(QWidget* parent) : MainTask(parent)
{
    changeTaskLabelText("Text to CBC encode:");
    changeResultLabelText("CBC encoded text:");
    changeMakeActionPushButtonText("Encode");
}

EncodeCipherBlockChaining::~EncodeCipherBlockChaining() {}
