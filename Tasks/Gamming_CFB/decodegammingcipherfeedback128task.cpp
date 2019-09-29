#include "decodegammingcipherfeedback128task.h"

#include <QBitArray>
#include <QByteArray>
#include <QCryptographicHash>

DecodeGammingCipherFeedback128Task::DecodeGammingCipherFeedback128Task(QWidget* parent) : MainTask(parent)
{
    changeTaskLabelText("Text to Gamming CFB decode:");
    changeResultLabelText("Gamming CFB decoded text:");
    changeMakeActionPushButtonText("Decode");
}

void DecodeGammingCipherFeedback128Task::mainMethod()
{
    // Show it in the result text edit
    resultTextEdit->setPlainText("NOT IMPLEMENTED");
}

DecodeGammingCipherFeedback128Task::~DecodeGammingCipherFeedback128Task() {}
