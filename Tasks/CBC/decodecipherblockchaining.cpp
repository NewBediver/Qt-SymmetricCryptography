#include "decodecipherblockchaining.h"

DecodeCipherBlockChaining::DecodeCipherBlockChaining(QWidget* parent) : MainTask(parent)
{
    changeTaskLabelText("Text to CBC decode:");
    changeResultLabelText("CBC decoded text:");
    changeMakeActionPushButtonText("Decode");
}

DecodeCipherBlockChaining::~DecodeCipherBlockChaining() {}
