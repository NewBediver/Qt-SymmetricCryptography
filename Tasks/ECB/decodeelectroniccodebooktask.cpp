#include "decodeelectroniccodebooktask.h"

#include <QByteArray>
#include <QBitArray>

DecodeElectronicCodeBookTask::DecodeElectronicCodeBookTask(QWidget* parent) : MainTask(parent)
{
    changeTaskLabelText("Text to ECB decode:");
    changeResultLabelText("ECB decoded text:");
    changeMakeActionPushButtonText("Decode");
}

void DecodeElectronicCodeBookTask::mainMethod()
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

        // Make main cycle and return decoded text in normal order
        QBitArray decodedBlock = main32PCicleDecode(textBlockBitArray, X);

        // Restore result text from encodedBlock in normal to normal text
        resultText.append(restoreDataFromQBitArray(decodedBlock));
    }

    // Show it in the result text edit
    resultTextEdit->setText(deleteAllNullByteFromBack(resultText).toHex().toUpper());
}

DecodeElectronicCodeBookTask::~DecodeElectronicCodeBookTask() {}
