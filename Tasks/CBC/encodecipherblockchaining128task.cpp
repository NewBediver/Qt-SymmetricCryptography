#include "encodecipherblockchaining128task.h"

#include <QBitArray>
#include <QByteArray>
#include <QCryptographicHash>

EncodeCipherBlockChaining128Task::EncodeCipherBlockChaining128Task(QWidget* parent) : MainTask(parent)
{
    changeTaskLabelText("Text to CBC encode:");
    changeResultLabelText("CBC encoded text:");
    changeMakeActionPushButtonText("Encode");
}

void EncodeCipherBlockChaining128Task::mainMethod()
{
    // Show it in the result text edit
    resultTextEdit->setPlainText("NOT IMPLEMENTED");
}

EncodeCipherBlockChaining128Task::~EncodeCipherBlockChaining128Task() {}
