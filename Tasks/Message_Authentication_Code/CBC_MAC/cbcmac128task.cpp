#include "cbcmac128task.h"

#include <QBitArray>
#include <QByteArray>

CBCMAC128Task::CBCMAC128Task(QWidget *parent) : MainTask(parent)
{
    changeTaskLabelText("Text to CBC-MAC encode:");
    changeResultLabelText("CBC-MAC encoded text:");
    changeMakeActionPushButtonText("Encode");
}

void CBCMAC128Task::mainMethod()
{
    // Get key
    std::vector<QBitArray> X = getKeyForKuznechik();

    // Text array (divisible on 8 * 16 = 128 bits)
    QByteArray textArray = getTextForKuznechik();

    // Get number of blocks
    int numOfBlocks = textArray.length() / 16;

    // If we got less than 2 blocks of data
    if (numOfBlocks < 2) {
        resultTextEdit->setPlainText("Enter more than 128 bits of data!");
        return;
    }

    // Get 0 block in QBitArray
    QBitArray textBlockBitArray = getBlock128FromQByteArrayText(textArray, 0);

    // Make main cycle and return encoded text in normal order
    QBitArray encodedBlock = kuznechikEncodeCicle(textBlockBitArray, X);

    for (int numOfBlock = 1; numOfBlock < numOfBlocks; ++numOfBlock) {
        // Get block of data
        textBlockBitArray = getBlock128FromQByteArrayText(textArray, numOfBlock);

        // Xor current encoded data with the next block
        textBlockBitArray = textBlockBitArray ^ encodedBlock;

        // Make main cycle and return encoded text in normal order
        encodedBlock = kuznechikEncodeCicle(textBlockBitArray, X);
    }

    // Show it in the result text edit
    resultTextEdit->setPlainText(restoreDataFromQBitArray(encodedBlock).toHex().toUpper());
}

CBCMAC128Task::~CBCMAC128Task() {}
