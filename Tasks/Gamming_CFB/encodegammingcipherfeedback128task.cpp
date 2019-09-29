#include "encodegammingcipherfeedback128task.h"

#include <QBitArray>
#include <QByteArray>
#include <QCryptographicHash>

EncodeGammingCipherFeedback128Task::EncodeGammingCipherFeedback128Task(QWidget* parent) : MainTask(parent)
{
    changeTaskLabelText("Text to Gamming CFB encode:");
    changeResultLabelText("Gamming CFB encoded text:");
    changeMakeActionPushButtonText("Encode");
}

void EncodeGammingCipherFeedback128Task::mainMethod()
{
    // Show it in the result text edit
    resultTextEdit->setPlainText("NOT IMPLEMENTED");
}

EncodeGammingCipherFeedback128Task::~EncodeGammingCipherFeedback128Task() {}
