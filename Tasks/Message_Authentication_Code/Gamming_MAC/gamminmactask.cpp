#include "gamminmactask.h"

#include <QBitArray>
#include <QByteArray>
#include <QRegExpValidator>

GammingMACTask::GammingMACTask(QWidget *parent) : MainTask(parent)
{
    changeTaskLabelText("Text to Gamming-MAC encode:");
    changeResultLabelText("Gamming-MAC encoded text:");
    changeMakeActionPushButtonText("Encode");

    IVLabel->setText("Initial vector:");

    IVLineEdit->setToolTip("Enter initial vector");
    IVLineEdit->setValidator(new QRegExpValidator(QRegExp("[A-Fa-f0-9]{0,16}")));

    IVLabel->setBuddy(IVLineEdit);

    keyFormLayout->addRow(IVLabel, IVLineEdit);
}

void GammingMACTask::mainMethod()
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

    // Get Synchro vector from keyArray
    QBitArray Synchro = getInitializingVector(QByteArray::fromHex(IVLineEdit->text().toLatin1()));

    // Make main cycle and return encoded text in normal order
    QBitArray encodedSynchro = main163Cicle(Synchro, X);

    // Fill N3 and N4 from encodedSynchro
    QBitArray N3(32);
    QBitArray N4(32);
    for (int i = 0; i < 32; ++i) {
        N3.setBit(i, encodedSynchro.at(32 + i));
        N4.setBit(i, encodedSynchro.at(i));
    }

    QBitArray encodedText;

    for (int numOfBlock = 0; numOfBlock < numOfBlocks; ++numOfBlock) {

        QBitArray C1(32);
        C1.setBit(7 , true);
        C1.setBit(15, true);
        C1.setBit(23, true);
        C1.setBit(29, true);
        QBitArray C2(32);
        C2.setBit(7 , true);
        C2.setBit(15, true);
        C2.setBit(23, true);
        C2.setBit(31, true);

        // Sum N4 and C1 mod 2^32-1
        N4 = summatorCM4mod2pow32minus1(N4, C1);
        // Sum N3 and C2 mod 2^32
        N3 = summatorCM3mod2pow32(N3, C2);

        //Return values to gammaBitArray
        QBitArray gammaBitArray(64);
        for (int i = 0; i < 32; ++i) {
            gammaBitArray.setBit(32 + i, N3.at(i));
            gammaBitArray.setBit(i, N4.at(i));
        }

        // Make main cycle and return encoded gamma in normal order
        QBitArray encodedGamma = main323CicleEncode(gammaBitArray, X);

        // Get block of data
        QBitArray textBlockBitArray = getBlockFromQByteArrayText(textArray, numOfBlock);

        if (numOfBlock == 0) {
            // Xor first block of text with gamma
            encodedText = summatorCM5mod2(encodedGamma, textBlockBitArray);
        }
        else {
            // Xor current encoded data with the encoded block
            encodedText = summatorCM5mod2(encodedText, summatorCM5mod2(encodedGamma, textBlockBitArray));
        }
    }

    // Show it in the result text edit
    resultTextEdit->setPlainText(restoreDataFromQBitArray(encodedText).toHex().toUpper());
}

GammingMACTask::~GammingMACTask() {}
