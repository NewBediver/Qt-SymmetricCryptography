#include "cbcmactask.h"

#include <QBitArray>
#include <QByteArray>
#include <QRegExpValidator>

CBCMACTask::CBCMACTask(QWidget *parent) : MainTask(parent)
{
    changeTaskLabelText("Text to CBC-MAC encode:");
    changeResultLabelText("CBC-MAC encoded text:");
    changeMakeActionPushButtonText("Encode");
}

void CBCMACTask::mainMethod()
{
    // Get key
    std::vector<QBitArray> X = getKey();

    // Text array (divisible on 8 * 8 = 64 bits)
    QByteArray textArray = getText();

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

        // Xor current encoded data with the next block
        textBlockBitArray = summatorCM5mod2(textBlockBitArray, encodedBlock);

        // Make main cycle and return encoded text in normal order
        encodedBlock = main163Cicle(textBlockBitArray, X);
    }

    // Show it in the result text edit
    resultTextEdit->setPlainText(restoreDataFromQBitArray(encodedBlock).toHex().toUpper());
}

CBCMACTask::~CBCMACTask() {}
