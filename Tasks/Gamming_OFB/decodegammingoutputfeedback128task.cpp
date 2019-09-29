#include "decodegammingoutputfeedback128task.h"

#include <QBitArray>
#include <QByteArray>
#include <QCryptographicHash>

DecodeGammingOutputFeedback128Task::DecodeGammingOutputFeedback128Task(QWidget* parent) : MainTask(parent)
{
    changeTaskLabelText("Text to Gamming OFB decode:");
    changeResultLabelText("Gamming OFB decoded text:");
    changeMakeActionPushButtonText("Decode");
}

void DecodeGammingOutputFeedback128Task::mainMethod()
{
    // Show it in the result text edit
    resultTextEdit->setPlainText("NOT IMPLEMENTED");
}

DecodeGammingOutputFeedback128Task::~DecodeGammingOutputFeedback128Task() {}
