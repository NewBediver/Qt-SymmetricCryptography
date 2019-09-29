#include "decodegamming128task.h"

#include <QBitArray>
#include <QByteArray>
#include <QCryptographicHash>

DecodeGamming128Task::DecodeGamming128Task(QWidget* parent) : MainTask(parent)
{
    changeTaskLabelText("Text to Gamming decode:");
    changeResultLabelText("Gamming decoded text:");
    changeMakeActionPushButtonText("Decode");
}

void DecodeGamming128Task::mainMethod()
{
    // Show it in the result text edit
    resultTextEdit->setPlainText("NOT IMPLEMENTED");
}

DecodeGamming128Task::~DecodeGamming128Task() {}
