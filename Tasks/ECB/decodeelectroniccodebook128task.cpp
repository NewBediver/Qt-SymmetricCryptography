#include "decodeelectroniccodebook128task.h"

#include <QByteArray>
#include <QBitArray>

DecodeElectronicCodeBook128Task::DecodeElectronicCodeBook128Task(QWidget* parent) : MainTask(parent)
{
    changeTaskLabelText("Text to ECB decode:");
    changeResultLabelText("ECB decoded text:");
    changeMakeActionPushButtonText("Decode");
}

void DecodeElectronicCodeBook128Task::mainMethod()
{
    // Get key
    std::vector<QBitArray> X = getKeyForKuznechik();

    // Text array (divisible on 8 * 16 = 128 bits)
    QByteArray textArray = getTextForKuznechik();

    QByteArray resultText;

    // Get number of blocks
    int numOfBlocks = textArray.length() / 16;
    for (int numOfBlock = 0; numOfBlock < numOfBlocks; ++numOfBlock) {
        // Get necessary block in QBitArray
        QBitArray textBlockBitArray = getBlock128FromQByteArrayText(textArray, numOfBlock);

        // Make main cycle and return decoded text in normal order
        QBitArray decodedBlock = kuznechikDecodeCicle(textBlockBitArray, X);

        // Restore result text from decodedBlock in normal to normal text
        resultText.append(restoreDataFromQBitArray(decodedBlock));
    }

    // Show it in the result text edit
    resultTextEdit->setPlainText(deleteAllNullByteFromBack(resultText).toHex().toUpper());
}

DecodeElectronicCodeBook128Task::~DecodeElectronicCodeBook128Task() {}
