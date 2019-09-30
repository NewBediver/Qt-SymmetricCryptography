#include "decodecipherblockchaining128task.h"

#include <QBitArray>
#include <QByteArray>
#include <QCryptographicHash>

DecodeCipherBlockChaining128Task::DecodeCipherBlockChaining128Task(QWidget* parent) : MainTask(parent)
{
    changeTaskLabelText("Text to CBC decode:");
    changeResultLabelText("CBC decoded text:");
    changeMakeActionPushButtonText("Decode");
}

void DecodeCipherBlockChaining128Task::mainMethod()
{
    // Get key
    std::vector<QBitArray> X = getKeyForKuznechik();

    // Text array (divisible on 8 * 16 = 128 bits)
    QByteArray textArray = getTextForKuznechik();

    // Get IV vector from keyArray
    QBitArray R1 = getInitializing128Vector(QByteArray::fromHex(keyLineEdit->text().toLatin1()));

    QByteArray resultText;

    // Get number of blocks
    int numOfBlocks = textArray.length() / 16;
    for (int numOfBlock = 0; numOfBlock < numOfBlocks; ++numOfBlock) {
        // Get necessary block in QBitArray
        QBitArray textBlockBitArray = getBlock128FromQByteArrayText(textArray, numOfBlock);

        // Get new R1 register from encryptedBlock of text
        QBitArray newR1 = textBlockBitArray;

        // Make main cycle and return decoded text in normal order
        QBitArray decodedBlock = kuznechikDecodeCicle(textBlockBitArray, X);

        // XOR R1 with decodedBlock
        decodedBlock ^= R1;

        // Restore result text from encodedBlock in normal to normal text
        resultText.append(restoreDataFromQBitArray(decodedBlock));

        // Define R1 with encrypted newR1
        R1 = newR1;
    }

    // Show it in the result text edit
    resultTextEdit->setPlainText(deleteAllNullByteFromBack(resultText).toHex().toUpper());
}

DecodeCipherBlockChaining128Task::~DecodeCipherBlockChaining128Task() {}
