#include "decodegammingoutputfeedbacktask.h"

#include <QBitArray>
#include <QByteArray>
#include <QCryptographicHash>

DecodeGammingOutputFeedbackTask::DecodeGammingOutputFeedbackTask(QWidget* parent) : MainTask(parent)
{
    changeTaskLabelText("Text to Gamming OFB decode:");
    changeResultLabelText("Gamming OFB decoded text:");
    changeMakeActionPushButtonText("Decode");
}

void DecodeGammingOutputFeedbackTask::mainMethod()
{
    // Get key
    std::vector<QBitArray> X = getKey();

    // Text array (divisible on 8 * 8 = 64 bits)
    QByteArray textArray = getText();

    // Get Synchro vector from keyArray
    QBitArray Synchro = getInitializingVector(QByteArray::fromHex(keyLineEdit->text().toLatin1()));
    // Make main cycle and return encoded Synchro text in normal order
    QBitArray gammaBitArray = main323CicleEncode(Synchro, X);

    QByteArray resultText;

    // Get number of blocks
    int numOfBlocks = textArray.length() / 8;
    for (int numOfBlock = 0; numOfBlock < numOfBlocks; ++numOfBlock) {
        // Fill N3 and N4 from encodedSynchro
        QBitArray N3(32);
        QBitArray N4(32);
        for (int i = 0; i < 32; ++i) {
            N3.setBit(i, gammaBitArray.at(32 + i));
            N4.setBit(i, gammaBitArray.at(i));
        }

        QBitArray C1(32);
        C1.setBit(24, true);
        C1.setBit(16, true);
        C1.setBit(8, true);
        C1.setBit(2, true);
        QBitArray C2(32);
        C1.setBit(24, true);
        C1.setBit(16, true);
        C1.setBit(8, true);
        C1.setBit(0, true);

        // Sum N4 and C1 mod 2^32-1
        N4 = summatorCM4mod2pow32minus1(N4, C1);
        // Sum N3 and C2 mod 2^32
        N3 = summatorCM3mod2pow32(N3, C2);

        //Return values to gammaBitArray
        for (int i = 0; i < 32; ++i) {
            gammaBitArray.setBit(32 + i, N3.at(i));
            gammaBitArray.setBit(i, N4.at(i));
        }

        // Make main cycle and return encoded gamma in normal order
        QBitArray encodedGamma = main323CicleEncode(gammaBitArray, X);

        // Fill gammaBitArray with encodedGamma
        gammaBitArray = encodedGamma;

        // Get necessary block in QBitArray
        QBitArray textBlockBitArray = getBlockFromQByteArrayText(textArray, numOfBlock);

        // Get result text from Gamma(N1 + N2) and open text
        QBitArray resultBlock = summatorCM5mod2(textBlockBitArray, encodedGamma);

        // Restore result text from resultBlock in normal to normal text
        resultText.append(restoreDataFromQBitArray(resultBlock));
    }

    // Show it in the result text edit
    resultTextEdit->setPlainText(deleteAllNullByteFromBack(resultText).toHex().toUpper());
}

DecodeGammingOutputFeedbackTask::~DecodeGammingOutputFeedbackTask() {}
