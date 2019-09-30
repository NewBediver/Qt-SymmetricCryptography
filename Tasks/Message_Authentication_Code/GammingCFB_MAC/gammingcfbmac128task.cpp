#include "gammingcfbmac128task.h"

#include <QBitArray>
#include <QByteArray>

GammingCFBMAC128Task::GammingCFBMAC128Task(QWidget *parent) : MainTask(parent)
{
    changeTaskLabelText("Text to Gamming CFB-MAC encode:");
    changeResultLabelText("Gamming CFB-MAC encoded text:");
    changeMakeActionPushButtonText("Encode");
}

void GammingCFBMAC128Task::mainMethod()
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

    // Get Synchro vector from keyArray
    QBitArray Synchro = getInitializing128Vector(QByteArray::fromHex(keyLineEdit->text().toLatin1()));

    // Make main cycle and return encoded Synchro text in normal order
    QBitArray encodedGamma = kuznechikEncodeCicle(Synchro, X);

    QBitArray encodedText;

    for (int numOfBlock = 0; numOfBlock < numOfBlocks; ++numOfBlock) {

        // Fill left and right from encodedSynchro
        QBitArray right(64);
        QBitArray left(64);
        for (int i = 0; i < 64; ++i) {
            right.setBit(i, encodedGamma.at(64 + i));
            left.setBit(i, encodedGamma.at(i));
        }

        QBitArray C1(64);
        C1.setBit(56, true);
        C1.setBit(48, true);
        C1.setBit(40, true);
        C1.setBit(32, true);
        C1.setBit(24, true);
        C1.setBit(16, true);
        C1.setBit(8, true);
        C1.setBit(2, true);
        QBitArray C2(64);
        C2.setBit(56, true);
        C2.setBit(48, true);
        C2.setBit(40, true);
        C2.setBit(32, true);
        C2.setBit(24, true);
        C2.setBit(16, true);
        C2.setBit(8, true);
        C2.setBit(0, true);

        // Sum left and C1 mod 2^32-1
        left = summator128mod2pow32minus1(left, C1);
        // Sum right and C2 mod 2^32
        right = summator128mod2pow32(right, C2);

        //Return values to gammaBitArray
        QBitArray gammaBitArray(128);
        for (int i = 0; i < 64; ++i) {
            gammaBitArray.setBit(64 + i, right.at(i));
            gammaBitArray.setBit(i, left.at(i));
        }

        // Make main cycle and return encoded gamma in normal order
        encodedGamma = kuznechikEncodeCicle(gammaBitArray, X);

        // Get necessary block in QBitArray
        QBitArray textBlockBitArray = getBlock128FromQByteArrayText(textArray, numOfBlock);

        if (numOfBlock == 0) {
            // Xor first block of text with gamma
            encodedText = encodedGamma ^ textBlockBitArray;
        }
        else {
            // Xor current encoded data with the encoded block
            encodedText ^= encodedGamma ^ textBlockBitArray;
        }

        encodedGamma = encodedText;
    }

    // Show it in the result text edit
    resultTextEdit->setPlainText(restoreDataFromQBitArray(encodedText).toHex().toUpper());
}

GammingCFBMAC128Task::~GammingCFBMAC128Task() {}
