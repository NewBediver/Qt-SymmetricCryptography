#include "encodeelectroniccodebooktask.h"

#include <QByteArray>
#include <QBitArray>

EncodeElectronicCodeBookTask::EncodeElectronicCodeBookTask(QWidget* parent) : MainTask(parent)
{
    changeTaskLabelText("Text to ECB encode:");
    changeResultLabelText("ECB encoded text:");
    changeMakeActionPushButtonText("Encode");
}

void EncodeElectronicCodeBookTask::mainMethod()
{
    // S-matrix
    unsigned char S[8][16] = {
        {0x09, 0x03, 0x03, 0x02, 0x08, 0x0B, 0x01, 0x07, 0x0A, 0x04, 0x0E, 0x0F, 0x0C, 0x00, 0x0D, 0x05},
        {0x03, 0x07, 0x0E, 0x09, 0x08, 0x0A, 0x0F, 0x00, 0x05, 0x02, 0x06, 0x0C, 0x0B, 0x04, 0x0D, 0x01},
        {0x0E, 0x04, 0x06, 0x02, 0x0B, 0x03, 0x0D, 0x08, 0x0C, 0x0F, 0x05, 0x0A, 0x00, 0x07, 0x01, 0x09},
        {0x0E, 0x07, 0x0A, 0x0C, 0x0D, 0x01, 0x03, 0x09, 0x00, 0x02, 0x0B, 0x04, 0x0F, 0x08, 0x05, 0x06},
        {0x0B, 0x05, 0x01, 0x09, 0x08, 0x0D, 0x0F, 0x00, 0x0E, 0x04, 0x02, 0x03, 0x0C, 0x07, 0x0A, 0x06},
        {0x03, 0x0A, 0x0D, 0x0C, 0x01, 0x02, 0x00, 0x0B, 0x07, 0x05, 0x09, 0x04, 0x08, 0x0F, 0x0E, 0x06},
        {0x01, 0x0D, 0x02, 0x09, 0x07, 0x0A, 0x06, 0x00, 0x08, 0x0C, 0x04, 0x05, 0x0F, 0x03, 0x0B, 0x0E},
        {0x0B, 0x0A, 0x0F, 0x05, 0x00, 0x0C, 0x0E, 0x08, 0x06, 0x02, 0x03, 0x09, 0x01, 0x07, 0x0D, 0x04}
    };

    // Key array 32 * 8 = 256 bits (0 padding if key less than 256 bits)
    QByteArray keyArray = keyLineEdit->text().toUtf8();
    keyArray.append(32 - keyArray.length(), 0x00);

    // Creates eight 32 bits arrays of key and fill them in reverse order
    QByteArray X0, X1, X2, X3, X4, X5, X6, X7;
    for (int i = 1; i <= 4; ++i) {
        X0.append(keyArray.at(4 - i));
        X1.append(keyArray.at(8 - i));
        X2.append(keyArray.at(12 - i));
        X3.append(keyArray.at(16 - i));
        X4.append(keyArray.at(20 - i));
        X5.append(keyArray.at(24 - i));
        X6.append(keyArray.at(28 - i));
        X7.append(keyArray.at(32 - i));
    }

    // Text array (divisible on 8 * 8 = 64 bits)
    QByteArray textArray = taskTextEdit->toPlainText().toUtf8();
    if (textArray.length() % 8 != 0) {
        textArray.append(8 - textArray.length() % 8, 0x00);
    }

    QByteArray resultText;

    // Get number of blocks
    int numOfBlocks = textArray.length() / 8;
    for (int i = 0; i < numOfBlocks; ++i) {
        // Creates two 32 bits arrays N1 and N2 and fill them in reverse order
        QByteArray N1;
        QByteArray N2;
        for (int j = 8 * i + 3; j >= 8 * i; --j) {
            N1.append(textArray.at(j));
        }
        for (int j = 8 * i + 7; j >= 8 * i + 4; --j) {
            N2.append(textArray.at(j));
        }

        // Then we have 32 rounds of encryption
        // First 24 rounds use X0 X1 X2 X3 X4 X5 X6 X7 3 times
        for (int j = 0; j < 24; ++j) {
            // Save N1 source value
            QByteArray tempN1(N1);

            // Choose the right Xj (depends on round number)
            QByteArray X;
            if (j % 8 == 0) {
                X.append(X0);
            }
            else if (j % 8 == 1) {
                X.append(X1);
            }
            else if (j % 8 == 2) {
                X.append(X2);
            }
            else if (j % 8 == 3) {
                X.append(X3);
            }
            else if (j % 8 == 4) {
                X.append(X4);
            }
            else if (j % 8 == 5) {
                X.append(X5);
            }
            else if (j % 8 == 6) {
                X.append(X6);
            }
            else if (j % 8 == 7) {
                X.append(X7);
            }

            // Sum N1 and X mod 2^32 and result saves in N1
            summatorCM1mod2pow32(N1, X);

            // All bytes in N1 changes it's value with the S matrix and result saves in N1
            kTransformBlock(N1, S);

            // Round rotate N1 on 11 bits to elder bits and result saves in N1
            rRotation11Block(N1);

            // Sum N1 and N2 mod 2 and result saves in N1
            summatorCM2mod2pow1(N1, N2);

            // Return old N1 value to N2
            N2 = tempN1;

        }
        // Last 8 rounds use X7 X6 X5 X4 X3 X2 X1 X0 1 time
        for (int j = 0; j < 8; ++j) {
            // Save N1 source value
            QByteArray tempN1(N1);

            // Choose the right Xj (depends on round number)
            QByteArray X;
            if (j % 8 == 0) {
                X.append(X7);
            }
            else if (j % 8 == 1) {
                X.append(X6);
            }
            else if (j % 8 == 2) {
                X.append(X5);
            }
            else if (j % 8 == 3) {
                X.append(X4);
            }
            else if (j % 8 == 4) {
                X.append(X3);
            }
            else if (j % 8 == 5) {
                X.append(X2);
            }
            else if (j % 8 == 6) {
                X.append(X1);
            }
            else if (j % 8 == 7) {
                X.append(X0);
            }

            // Sum N1 and X mod 2^32 and result saves in N1
            summatorCM1mod2pow32(N1, X);

            // All bytes in N1 changes it's value with the S matrix and result saves in N1
            kTransformBlock(N1, S);

            // Round rotate N1 on 11 bits to elder bits and result saves in N1
            rRotation11Block(N1);

            // Sum N1 and N2 mod 2 and result saves in N1
            summatorCM2mod2pow1(N1, N2);

            // Return old N1 value to N2
            N2 = tempN1;
        }

        // Restore result text from N1 and N2 int normal order
        for (int i = N1.length() - 1; i >= 0; --i){
            resultText.append(N1);
        }
        for (int i = N2.length() - 1; i >= 0; --i){
            resultText.append(N2);
        }
    }

    // Show it in the result text edit
    resultTextEdit->setText(QString::fromUtf8(resultText));
}

void EncodeElectronicCodeBookTask::summatorCM1mod2pow32(QByteArray& N1, const QByteArray& X)
{
    unsigned int internal = 0;
    for (int i = N1.length()-1; i >= 0; --i)
    {
        internal = static_cast<unsigned int>(N1.at(i)) + static_cast<unsigned int>(X.at(i)) + (internal >> 8);
        N1[i] = static_cast<char>(internal & 0xff);
    }
}

void EncodeElectronicCodeBookTask::kTransformBlock(QByteArray& N1, const unsigned char S[8][16])
{
    int firstPartByte, secPartByte;
    for (int i = 0; i < 4; i++)
    {
        // Takes the first 4-bits part of byte
        firstPartByte = (N1[i] & 0xf0) >> 4;
        // Takes the second 4-bits part of byte
        secPartByte = (N1[i] & 0x0f);
        // Makes the swap whis the S matrix
        firstPartByte = S[i * 2][firstPartByte];
        secPartByte = S[i * 2 + 1][secPartByte];
        // Concatenates two 4-bits parts back to byte
        N1[i] = static_cast<char>((firstPartByte << 4) | secPartByte);
    }
}

void EncodeElectronicCodeBookTask::rRotation11Block(QByteArray& N1)
{
    // Create 32-bits vector and translate N1 there
    QBitArray bitArray(32);
    int pos = 0;
    for (int i = 0; i < N1.length(); ++i) {
        for (int j = 1; j < (1 << 8); j <<= 1){
            bitArray.setBit(pos, N1.at(i) & j);
            ++pos;
        }
    }

    // Takes the first 11 bits
    QBitArray first11Bits(11);
    for (int i = 0; i < 11; ++i) {
        first11Bits.setBit(i, bitArray.at(i));
    }

    // Rotate last 21 bits to the start positions and add the last 11 bits to the end
    for (int i = 11; i < bitArray.size(); ++i) {
        bitArray.setBit(i - 11, bitArray.at(i));
    }
    for (int i = 0; i < first11Bits.size(); ++i) {
        bitArray.setBit(21 + i, first11Bits.at(i));
    }

    // Translate bit vector into byte vector N1
    for (int i = 0; i < 4; ++i) {
        unsigned char temp = 0;
        for (int j = i * 8; j < i * 8 + 8; ++j) {
            temp = static_cast<unsigned char>(bitArray.at(j) << (j % 8));
        }
        N1[i] = static_cast<char>(temp);
    }
}

void EncodeElectronicCodeBookTask::summatorCM2mod2pow1(QByteArray& N1, const QByteArray& N2)
{
    for (int i = 0; i < N1.length(); i++) {
       N1[i] = N1[i] ^ N2[i];
    }
}

EncodeElectronicCodeBookTask::~EncodeElectronicCodeBookTask() {}
