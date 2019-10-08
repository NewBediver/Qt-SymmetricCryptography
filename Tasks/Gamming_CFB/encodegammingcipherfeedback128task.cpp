#include "encodegammingcipherfeedback128task.h"

#include <QBitArray>
#include <QByteArray>
#include <QRegExpValidator>

EncodeGammingCipherFeedback128Task::EncodeGammingCipherFeedback128Task(QWidget* parent) : MainTask(parent)
{
    changeTaskLabelText("Text to Gamming CFB encode:");
    changeResultLabelText("Gamming CFB encoded text:");
    changeMakeActionPushButtonText("Encode");

    IVLabel->setText("Initial vector:");

    IVLineEdit->setToolTip("Enter initial vector");
    IVLineEdit->setValidator(new QRegExpValidator(QRegExp("[A-Fa-f0-9]{0,32}")));

    IVLabel->setBuddy(IVLineEdit);

    keyFormLayout->addRow(IVLabel, IVLineEdit);
}

void EncodeGammingCipherFeedback128Task::mainMethod()
{
    // Get key
    std::vector<QBitArray> X = getKeyForKuznechik();

    // Text array (divisible on 8 * 16 = 128 bits)
    QByteArray textArray = getTextForKuznechik();

    // Get Synchro vector from keyArray
    QBitArray Synchro = getInitializing128Vector(QByteArray::fromHex(IVLineEdit->text().toLatin1()));

    // Make main cycle and return encoded Synchro text in normal order
    QBitArray gammaBitArray = kuznechikEncodeCicle(Synchro, X);

    QByteArray resultText;

    // Get number of blocks
    int numOfBlocks = textArray.length() / 16;
    for (int numOfBlock = 0; numOfBlock < numOfBlocks; ++numOfBlock) {
        // Fill left and right from encodedSynchro
        QBitArray right(64);
        QBitArray left(64);
        for (int i = 0; i < 64; ++i) {
            right.setBit(i, gammaBitArray.at(64 + i));
            left.setBit(i, gammaBitArray.at(i));
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

        // Fill gammaBitArray with encodedGamma
        gammaBitArray = resultBlock;

        // Restore result text from encodedBlock in normal to normal text
        resultText.append(restoreDataFromQBitArray(resultBlock));
    }

    // Show it in the result text edit
    resultTextEdit->setPlainText(resultText.toHex().toUpper());
}

EncodeGammingCipherFeedback128Task::~EncodeGammingCipherFeedback128Task() {}
