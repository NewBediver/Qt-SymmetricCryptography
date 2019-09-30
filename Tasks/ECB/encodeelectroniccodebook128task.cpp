#include "encodeelectroniccodebook128task.h"

#include <QByteArray>
#include <QBitArray>

EncodeElectronicCodeBook128Task::EncodeElectronicCodeBook128Task(QWidget* parent) : MainTask(parent)
{
    changeTaskLabelText("Text to ECB encode:");
    changeResultLabelText("ECB encoded text:");
    changeMakeActionPushButtonText("Encode");
}

void EncodeElectronicCodeBook128Task::mainMethod()
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

        // Make main cycle and return encoded text in normal order
        QBitArray encodedBlock = kuznechikEncodeCicle(textBlockBitArray, X);

        // Restore result text from encodedBlock in normal to normal text
        resultText.append(restoreDataFromQBitArray(encodedBlock));
    }

    // Show it in the result text edit
    resultTextEdit->setPlainText(resultText.toHex().toUpper());
}

EncodeElectronicCodeBook128Task::~EncodeElectronicCodeBook128Task() {}
