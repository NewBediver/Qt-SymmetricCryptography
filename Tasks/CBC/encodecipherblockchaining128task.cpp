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

        // XOR R1 with textBlockBitArray
        textBlockBitArray ^= R1;

        // Make main cycle and return encoded text in normal order
        QBitArray encodedBlock = kuznechikEncodeCicle(textBlockBitArray, X);

        // Restore result text from encodedBlock in normal to normal text
        resultText.append(restoreDataFromQBitArray(encodedBlock));

        // Get new R1 register from encrypted textBlockBitArray
        R1 = encodedBlock;
    }

    // Show it in the result text edit
    resultTextEdit->setPlainText(resultText.toHex().toUpper());
}

EncodeCipherBlockChaining128Task::~EncodeCipherBlockChaining128Task() {}
