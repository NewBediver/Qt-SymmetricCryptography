#include "ecbmactask.h"

#include <QBitArray>
#include <QByteArray>

ECBMACTask::ECBMACTask(QWidget *parent) : MainTask(parent)
{
    changeTaskLabelText("Text to ECB-MAC encode:");
    changeResultLabelText("ECB-MAC encoded text:");
    changeMakeActionPushButtonText("Encode");
}

void ECBMACTask::mainMethod()
{
    // Get key
    std::vector<QBitArray> X = getKey();

    // Text array (divisible on 8 * 8 = 64 bits)
    QByteArray textArray = getText();

    QByteArray resultText;

    // Get number of blocks
    int numOfBlocks = textArray.length() / 8;

    // If we got less than 2 blocks of data
    if (numOfBlocks < 2) {
        resultTextEdit->setPlainText("Enter more than 64 bits of data!");
        return;
    }

    // Get 0 block of data
    QBitArray textBlockBitArray = getBlockFromQByteArrayText(textArray, 0);

    // Make main cycle and return encoded text in normal order
    QBitArray encodedBlock = main163Cicle(textBlockBitArray, X);

    for (int numOfBlock = 1; numOfBlock < numOfBlocks; ++numOfBlock) {
        // Get block of data
        textBlockBitArray = getBlockFromQByteArrayText(textArray, numOfBlock);

        // Make main cycle and return encoded text in normal order
        QBitArray nextEncodedBlock = main163Cicle(textBlockBitArray, X);

        // Xor current encoded data with the next block
        encodedBlock = summatorCM5mod2(encodedBlock, nextEncodedBlock);
    }

    // Show it in the result text edit
    resultTextEdit->setPlainText(restoreDataFromQBitArray(encodedBlock).toHex().toUpper());
}

ECBMACTask::~ECBMACTask() {}
