#include "decodecipherblockchaining128task.h"

#include <QBitArray>
#include <QByteArray>
#include <QCryptographicHash>

DecodeCipherBlockChaining128Task::DecodeCipherBlockChaining128Task(QWidget* parent) : MainTask(parent)
{
    changeTaskLabelText("Text to CBC decode:");
    changeResultLabelText("CBC decoded text:");
    changeMakeActionPushButtonText("Decode");
}

void DecodeCipherBlockChaining128Task::mainMethod()
{
    // Show it in the result text edit
    resultTextEdit->setPlainText("NOT IMPLEMENTED");
}

DecodeCipherBlockChaining128Task::~DecodeCipherBlockChaining128Task() {}
