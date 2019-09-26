#include "encodecipherblockchaining.h"

#include <QBitArray>
#include <QByteArray>
#include <QCryptographicHash>

EncodeCipherBlockChaining::EncodeCipherBlockChaining(QWidget* parent) : MainTask(parent)
{
    changeTaskLabelText("Text to CBC encode:");
    changeResultLabelText("CBC encoded text:");
    changeMakeActionPushButtonText("Encode");
}

void EncodeCipherBlockChaining::mainMethod()
{
    // Get key
    std::vector<QBitArray> X = getKey();

    // Text array (divisible on 8 * 8 = 64 bits)
    QByteArray textArray = getText();

    // Get IV vector from keyArray
    QBitArray R1 = getInitializingVector(QByteArray::fromHex(keyLineEdit->text().toLatin1()));

    QByteArray resultText;

    // Get number of blocks
    int numOfBlocks = textArray.length() / 8;
    for (int numOfBlock = 0; numOfBlock < numOfBlocks; ++numOfBlock) {
        // Get necessary block in QBitArray
        QBitArray textBlockBitArray = getBlockFromQByteArrayText(textArray, numOfBlock);

        // XOR R1 with textBlockBitArray
        textBlockBitArray ^= R1;

        // Make main cycle and return encoded text in normal order
        QBitArray encodedBlock = main323CicleEncode(textBlockBitArray, X);

        // Restore result text from encodedBlock in normal to normal text
        resultText.append(restoreDataFromQBitArray(encodedBlock));

        // Get new R1 register from encrypted textBlockBitArray
        R1 = encodedBlock;
    }

    // Show it in the result text edit
    resultTextEdit->setPlainText(resultText.toHex().toUpper());
}

EncodeCipherBlockChaining::~EncodeCipherBlockChaining() {}
