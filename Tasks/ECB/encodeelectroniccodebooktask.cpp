#include "encodeelectroniccodebooktask.h"

#include <QByteArray>
#include <QBitArray>

EncodeElectronicCodeBookTask::EncodeElectronicCodeBookTask(QWidget* parent) : MainTask(parent)
{
    changeTaskLabelText("Text to ECB encode:");
    changeResultLabelText("ECB encoded text:");
    changeMakeActionPushButtonText("Encode");
}

void EncodeElectronicCodeBookTask::mainMethod()
{
    // Get key
    std::vector<QBitArray> X = getKey();

    // Text array (divisible on 8 * 8 = 64 bits)
    QByteArray textArray = getText();

    QByteArray resultText;

    // Get number of blocks
    int numOfBlocks = textArray.length() / 8;
    for (int numOfBlock = 0; numOfBlock < numOfBlocks; ++numOfBlock) {
        // Get necessary block in QBitArray
        QBitArray textBlockBitArray = getBlockFromQByteArrayText(textArray, numOfBlock);

        // Make main cycle and return encoded text in normal order
        QBitArray encodedBlock = main323CicleEncode(textBlockBitArray, X);

        // Restore result text from encodedBlock in normal to normal text
        resultText.append(restoreDataFromQBitArray(encodedBlock));
    }

    // Show it in the result text edit
    resultTextEdit->setPlainText(resultText.toHex().toUpper());
}

EncodeElectronicCodeBookTask::~EncodeElectronicCodeBookTask() {}
