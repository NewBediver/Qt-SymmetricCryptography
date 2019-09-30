#include "decodegamming128task.h"

#include <QBitArray>
#include <QByteArray>
#include <QCryptographicHash>

DecodeGamming128Task::DecodeGamming128Task(QWidget* parent) : MainTask(parent)
{
    changeTaskLabelText("Text to Gamming decode:");
    changeResultLabelText("Gamming decoded text:");
    changeMakeActionPushButtonText("Decode");
}

void DecodeGamming128Task::mainMethod()
{
    // Get key
    std::vector<QBitArray> X = getKeyForKuznechik();

    // Text array (divisible on 8 * 16 = 128 bits)
    QByteArray textArray = getTextForKuznechik();

    // Get Synchro vector from keyArray
    QBitArray Synchro = getInitializing128Vector(QByteArray::fromHex(keyLineEdit->text().toLatin1()));

    // Make main cycle and return encoded Synchro text in normal order
    QBitArray encodedSynchro = kuznechikEncodeCicle(Synchro, X);

    QByteArray resultText;

    // Fill left and right from encodedSynchro
    QBitArray right(64);
    QBitArray left(64);
    for (int i = 0; i < 64; ++i) {
        right.setBit(i, encodedSynchro.at(64 + i));
        left.setBit(i, encodedSynchro.at(i));
    }

    // Get number of blocks
    int numOfBlocks = textArray.length() / 16;
    for (int numOfBlock = 0; numOfBlock < numOfBlocks; ++numOfBlock) {

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
        QBitArray encodedGamma = kuznechikEncodeCicle(gammaBitArray, X);

        // Get necessary block in QBitArray
        QBitArray textBlockBitArray = getBlock128FromQByteArrayText(textArray, numOfBlock);

        // Get result text from Gamma(N1 + N2) and open text
        QBitArray resultBlock = textBlockBitArray ^ encodedGamma;

        // Restore result text from encodedBlock in normal to normal text
        resultText.append(restoreDataFromQBitArray(resultBlock));
    }

    // Show it in the result text edit
    resultTextEdit->setPlainText(deleteAllNullByteFromBack(resultText).toHex().toUpper());
}

DecodeGamming128Task::~DecodeGamming128Task() {}
