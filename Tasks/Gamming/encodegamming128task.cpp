#include "encodegamming128task.h"

#include <QBitArray>
#include <QByteArray>
#include <QCryptographicHash>

EncodeGamming128Task::EncodeGamming128Task(QWidget* parent) : MainTask(parent)
{
    changeTaskLabelText("Text to Gamming encode:");
    changeResultLabelText("Gamming encoded text:");
    changeMakeActionPushButtonText("Encode");
}

void EncodeGamming128Task::mainMethod()
{
    // Show it in the result text edit
    resultTextEdit->setPlainText("NOT IMPLEMENTED");
}

EncodeGamming128Task::~EncodeGamming128Task() {}
