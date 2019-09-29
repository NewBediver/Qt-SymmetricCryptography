#include "encodegammingoutputfeedback128task.h"

#include <QBitArray>
#include <QByteArray>
#include <QCryptographicHash>

EncodeGammingOutputFeedback128Task::EncodeGammingOutputFeedback128Task(QWidget* parent) : MainTask(parent)
{
    changeTaskLabelText("Text to Gamming OFB encode:");
    changeResultLabelText("Gamming OFB encoded text:");
    changeMakeActionPushButtonText("Encode");
}

void EncodeGammingOutputFeedback128Task::mainMethod()
{
    // Show it in the result text edit
    resultTextEdit->setPlainText("NOT IMPLEMENTED");
}

EncodeGammingOutputFeedback128Task::~EncodeGammingOutputFeedback128Task() {}
