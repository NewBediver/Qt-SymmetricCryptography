#include "decodecipherblockchaining.h"

#include <QByteArray>
#include <QBitArray>
#include <QRegExpValidator>

DecodeCipherBlockChaining::DecodeCipherBlockChaining(QWidget* parent) : MainTask(parent)
{
    changeTaskLabelText("Text to CBC decode:");
    changeResultLabelText("CBC decoded text:");
    changeMakeActionPushButtonText("Decode");

    IVLabel->setText("Initial vector:");

    IVLineEdit->setToolTip("Enter initial vector");
    IVLineEdit->setValidator(new QRegExpValidator(QRegExp("[A-Fa-f0-9]{0,16}")));

    IVLabel->setBuddy(IVLineEdit);

    keyFormLayout->addRow(IVLabel, IVLineEdit);
}

void DecodeCipherBlockChaining::mainMethod()
{
    // Get key
    std::vector<QBitArray> X = getKey();

    // Text array (divisible on 8 * 8 = 64 bits)
    QByteArray textArray = getText();

    // Get IV vector from keyArray
    QBitArray R1 = getInitializingVector(QByteArray::fromHex(IVLineEdit->text().toLatin1()));

    QByteArray resultText;

    // Get number of blocks
    int numOfBlocks = textArray.length() / 8;
    for (int numOfBlock = 0; numOfBlock < numOfBlocks; ++numOfBlock) {
        // Get necessary block in QBitArray
        QBitArray textBlockBitArray = getBlockFromQByteArrayText(textArray, numOfBlock);

        // Get new R1 register from encrypted N1 and N2
        QBitArray newR1 = textBlockBitArray;

        // Make main cycle and return decoded text in normal order
        QBitArray decodedBlock = main32PCicleDecode(textBlockBitArray, X);

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

DecodeCipherBlockChaining::~DecodeCipherBlockChaining() {}
