#include "encodegammingcipherfeedbacktask.h"

#include <QBitArray>
#include <QByteArray>
#include <QCryptographicHash>

EncodeGammingCipherFeedbackTask::EncodeGammingCipherFeedbackTask(QWidget* parent) : MainTask(parent)
{
    changeTaskLabelText("Text to Gamming CFB encode:");
    changeResultLabelText("Gamming CFB encoded text:");
    changeMakeActionPushButtonText("Encode");
}

void EncodeGammingCipherFeedbackTask::mainMethod()
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
        // Fill N3 and N4 from gammaBitArray
        QBitArray N3(32);
        QBitArray N4(32);
        for (int i = 0; i < 32; ++i) {
            N3.setBit(i, gammaBitArray.at(31 - i));
            N4.setBit(i, gammaBitArray.at(63 - i));
        }

        QBitArray C1(32);
        C1.setBit(7 , true);
        C1.setBit(15, true);
        C1.setBit(23, true);
        C1.setBit(29, true);
        QBitArray C2(32);
        C1.setBit(7 , true);
        C1.setBit(15, true);
        C1.setBit(23, true);
        C1.setBit(31, true);

        // Sum N4 and C1 mod 2^32-1
        N4 = summatorCM4mod2pow32minus1(N4, C1);
        // Sum N3 and C2 mod 2^32
        N3 = summatorCM3mod2pow32(N3, C2);

        //Return values to gammaBitArray
        for (int i = 0; i < 32; ++i) {
            gammaBitArray.setBit(i, N3.at(31 - i));
            gammaBitArray.setBit(i + 32, N4.at(31-i));
        }

        // Make main cycle and return encoded gamma in normal order
        QBitArray encodedGamma = main323CicleEncode(gammaBitArray, X);

        // Get necessary block in QBitArray
        QBitArray textBlockBitArray = getBlockFromQByteArrayText(textArray, numOfBlock);

        // Get result text from Gamma(N1 + N2) and open text
        QBitArray resultBlock = summatorCM5mod2(textBlockBitArray, encodedGamma);

        // Fill gammaBitArray with resultBlock
        gammaBitArray = resultBlock;

        // Restore result text from resultBlock in normal to normal text
        resultText.append(restoreDataFromQBitArray(resultBlock));
    }

    // Show it in the result text edit
    resultTextEdit->setPlainText(resultText.toHex().toUpper());
}

EncodeGammingCipherFeedbackTask::~EncodeGammingCipherFeedbackTask() {}
