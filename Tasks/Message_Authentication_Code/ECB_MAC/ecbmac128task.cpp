#include "ecbmac128task.h"

#include <QBitArray>
#include <QByteArray>

ECBMAC128Task::ECBMAC128Task(QWidget *parent) : MainTask(parent)
{
    changeTaskLabelText("Text to ECB-MAC encode:");
    changeResultLabelText("ECB-MAC encoded text:");
    changeMakeActionPushButtonText("Encode");
}

void ECBMAC128Task::mainMethod()
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

        // Make main cycle and return encoded text in normal order
        QBitArray nextEncodedBlock = kuznechikEncodeCicle(textBlockBitArray, X);

        // Xor current encoded data with the next block
        encodedBlock = encodedBlock ^ nextEncodedBlock;
    }

    // Show it in the result text edit
    resultTextEdit->setPlainText(restoreDataFromQBitArray(encodedBlock).toHex().toUpper());
}

ECBMAC128Task::~ECBMAC128Task() {}
