#include "decodegammingtask.h"

#include <QByteArray>
#include <QBitArray>
#include <QCryptographicHash>

DecodeGammingTask::DecodeGammingTask(QWidget* parent) : MainTask(parent)
{
    changeTaskLabelText("Text to Gamming decode:");
    changeResultLabelText("Gamming decoded text:");
    changeMakeActionPushButtonText("Decode");
}

void DecodeGammingTask::mainMethod()
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
    QByteArray keyArray = QByteArray::fromHex(keyLineEdit->text().toLatin1());
    keyArray.append(32 - keyArray.length(), 0x00);

    // Creates eight 32 bits arrays of key and fill them in reverse order
    QBitArray X0(32), X1(32), X2(32), X3(32), X4(32), X5(32), X6(32), X7(32);
    for (int i = 3; i >= 0; --i) {
        for (int j = 0; j <= 7; ++j) {
            X0.setBit((3 - i) * 8 + j, (1 << j) & keyArray[i]);
            X1.setBit((3 - i) * 8 + j, (1 << j) & keyArray[i + 4]);
            X2.setBit((3 - i) * 8 + j, (1 << j) & keyArray[i + 8]);
            X3.setBit((3 - i) * 8 + j, (1 << j) & keyArray[i + 12]);
            X4.setBit((3 - i) * 8 + j, (1 << j) & keyArray[i + 16]);
            X5.setBit((3 - i) * 8 + j, (1 << j) & keyArray[i + 20]);
            X6.setBit((3 - i) * 8 + j, (1 << j) & keyArray[i + 24]);
            X7.setBit((3 - i) * 8 + j, (1 << j) & keyArray[i + 28]);
        }
    }

    // Text array (divisible on 8 * 8 = 64 bits)
    QByteArray textArray = QByteArray::fromHex(taskTextEdit->toPlainText().toLatin1());
    if (textArray.length() % 8 != 0) {
        textArray.append(8 - textArray.length() % 8, 0x00);
    }

    // Get Synchro vector from keyArray
    QBitArray Synchro = getInitializingVector(keyArray);

    // Fill N1 and N2 with Synchro vector
    QBitArray N1(32);
    QBitArray N2(32);
    for (int i = 63; i >= 32; --i) {
        N1.setBit(63 - i, Synchro.at(i));
        N2.setBit(63 - i, Synchro.at(i-32));
    }

    // Then we have 32 rounds of encryption
    // First 24 rounds use X0 X1 X2 X3 X4 X5 X6 X7 3 times
    for (int j = 0; j < 24; ++j) {
        // Save N1 source value
        QBitArray tempN1(N1);

        // Choose the right Xj (depends on round number)
        QBitArray X;
        if (j % 8 == 0) {
            X = X0;
        }
        else if (j % 8 == 1) {
            X = X1;
        }
        else if (j % 8 == 2) {
            X = X2;
        }
        else if (j % 8 == 3) {
            X = X3;
        }
        else if (j % 8 == 4) {
            X = X4;
        }
        else if (j % 8 == 5) {
            X = X5;
        }
        else if (j % 8 == 6) {
            X = X6;
        }
        else if (j % 8 == 7) {
            X = X7;
        }

        // Sum N1 and X mod 2^32 and result saves in N1
        N1 = summatorCM1mod2pow32(N1, X);

        // All bytes in N1 changes it's value with the S matrix and result saves in N1
        N1 = kTransformBlock(N1, S);

        // Round rotate N1 on 11 bits to elder bits and result saves in N1
        N1 = rRotation11Block(N1);

        // Sum N1 and N2 mod 2 and result saves in N1
        N1 = summatorCM2mod2pow1(N1, N2);

        // Return old N1 value to N2
        N2 = tempN1;

    }
    // Last 8 rounds use X7 X6 X5 X4 X3 X2 X1 X0 1 time
    for (int j = 0; j < 8; ++j) {
        // Save N1 source value
        QBitArray tempN1(N1);

        // Choose the right Xj (depends on round number)
        QBitArray X;
        if (j % 8 == 0) {
            X = X7;
        }
        else if (j % 8 == 1) {
            X = X6;
        }
        else if (j % 8 == 2) {
            X = X5;
        }
        else if (j % 8 == 3) {
            X = X4;
        }
        else if (j % 8 == 4) {
            X = X3;
        }
        else if (j % 8 == 5) {
            X = X2;
        }
        else if (j % 8 == 6) {
            X = X1;
        }
        else if (j % 8 == 7) {
            X = X0;
        }

        // Sum N1 and X mod 2^32 and result saves in N1
        N1 = summatorCM1mod2pow32(N1, X);

        // All bytes in N1 changes it's value with the S matrix and result saves in N1
        N1 = kTransformBlock(N1, S);

        // Round rotate N1 on 11 bits to elder bits and result saves in N1
        N1 = rRotation11Block(N1);

        // If it is not 32 round
        if (j != 7) {
            // Sum N1 and N2 mod 2 and result saves in N1
            N1 = summatorCM2mod2pow1(N1, N2);

            // Return old N1 value to N2
            N2 = tempN1;
        }
        else {
            // Sum N1 and N2 mod 2 and result saves in N2
            N2 = summatorCM2mod2pow1(N1, N2);

            // Return old N1 value to N1
            N1 = tempN1;
        }
    }


    QByteArray resultText;

    // Get number of blocks
    int numOfBlocks = textArray.length() / 8;
    for (int i = 0; i < numOfBlocks; ++i) {

        // Fill N3 and N4 with N1 and N2 accordinly
        QBitArray N3 = N1;
        QBitArray N4 = N2;
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

        //Return values to N1 and N2
        N1 = N3;
        N2 = N4;

        // Then we have 32 rounds of encryption
        // First 24 rounds use X0 X1 X2 X3 X4 X5 X6 X7 3 times
        for (int j = 0; j < 24; ++j) {
            // Save N1 source value
            QBitArray tempN1(N1);

            // Choose the right Xj (depends on round number)
            QBitArray X;
            if (j % 8 == 0) {
                X = X0;
            }
            else if (j % 8 == 1) {
                X = X1;
            }
            else if (j % 8 == 2) {
                X = X2;
            }
            else if (j % 8 == 3) {
                X = X3;
            }
            else if (j % 8 == 4) {
                X = X4;
            }
            else if (j % 8 == 5) {
                X = X5;
            }
            else if (j % 8 == 6) {
                X = X6;
            }
            else if (j % 8 == 7) {
                X = X7;
            }

            // Sum N1 and X mod 2^32 and result saves in N1
            N1 = summatorCM1mod2pow32(N1, X);

            // All bytes in N1 changes it's value with the S matrix and result saves in N1
            N1 = kTransformBlock(N1, S);

            // Round rotate N1 on 11 bits to elder bits and result saves in N1
            N1 = rRotation11Block(N1);

            // Sum N1 and N2 mod 2 and result saves in N1
            N1 = summatorCM2mod2pow1(N1, N2);

            // Return old N1 value to N2
            N2 = tempN1;

        }
        // Last 8 rounds use X7 X6 X5 X4 X3 X2 X1 X0 1 time
        for (int j = 0; j < 8; ++j) {
            // Save N1 source value
            QBitArray tempN1(N1);

            // Choose the right Xj (depends on round number)
            QBitArray X;
            if (j % 8 == 0) {
                X = X7;
            }
            else if (j % 8 == 1) {
                X = X6;
            }
            else if (j % 8 == 2) {
                X = X5;
            }
            else if (j % 8 == 3) {
                X = X4;
            }
            else if (j % 8 == 4) {
                X = X3;
            }
            else if (j % 8 == 5) {
                X = X2;
            }
            else if (j % 8 == 6) {
                X = X1;
            }
            else if (j % 8 == 7) {
                X = X0;
            }

            // Sum N1 and X mod 2^32 and result saves in N1
            N1 = summatorCM1mod2pow32(N1, X);

            // All bytes in N1 changes it's value with the S matrix and result saves in N1
            N1 = kTransformBlock(N1, S);

            // Round rotate N1 on 11 bits to elder bits and result saves in N1
            N1 = rRotation11Block(N1);

            // If it is not 32 round
            if (j != 7) {
                // Sum N1 and N2 mod 2 and result saves in N1
                N1 = summatorCM2mod2pow1(N1, N2);

                // Return old N1 value to N2
                N2 = tempN1;
            }
            else {
                // Sum N1 and N2 mod 2 and result saves in N2
                N2 = summatorCM2mod2pow1(N1, N2);

                // Return old N1 value to N1
                N1 = tempN1;
            }
        }

        // Get iblock of text
        QBitArray text1(32), text2(32);
        for (int j = 8 * i; j < 8 * i + 4; ++j) {
            for (int k = 7; k >= 0; --k) {
                text1.setBit((j - 8 * i) * 8 + (7 - k), (1 << k) & static_cast<int>(textArray[j]));
            }
        }
        for (int j = 8 * i + 4; j < 8 * i + 8; ++j) {
            for (int k = 7; k >= 0; --k) {
                text2.setBit((j - (8 * i + 4)) * 8 + (7 - k), (1 << k) & static_cast<int>(textArray[j]));
            }
        }

        // Get result text from Gamma(N1 + N2) and open text
        QBitArray resultBlock =  summatorCM5mod2(N1, N2, text1, text2);

        // Restore result text from resultBlock
        for (int j = 0; j < 8; ++j){
            char temp = 0x00;
            for (int k = 0; k < 8; ++k) {
                temp |= (resultBlock[j * 8 + k] << (7 - k));
            }
            resultText.append(temp);
        }
    }

    // Delete all null byte from back
    QString res = resultText.toHex().toUpper();
    int index = res.length() - 1;
    while (res[index] == '0' && res[index-1] == '0') {
        res.remove(index-1, 2);
        index -= 2;
    }

    // Show it in the result text edit
    resultTextEdit->setPlainText(res);
}

QBitArray DecodeGammingTask::summatorCM1mod2pow32(const QBitArray& N1, const QBitArray& X)
{
    QBitArray res(N1);

    bool rem = false;
    for (int i = res.size() - 1; i >= 0; --i) {
        if (res.at(i) && X.at(i)) {
            if (rem) {
                res[i] = true;
            }
            else {
                res[i] = false;
            }
            rem = true;
        }
        else if (res.at(i) || X.at(i)) {
            if (rem) {
                res[i] = false;
            }
            else {
                res[i] = true;
            }
        }
        else {
            res[i] = rem;
            rem = false;
        }
    }

    return res;
}

QBitArray DecodeGammingTask::kTransformBlock(const QBitArray& N1, const unsigned char S[8][16])
{
    QBitArray res(32);

    int firstPartByte, secPartByte;
    for (int i = 0; i < 4; i++)
    {
        firstPartByte = 0;
        secPartByte = 0;
        // Takes the first 4-bits part of byte
        for (int j = i * 8; j <= i * 8 + 3; ++j){
            firstPartByte |= (N1.at(j) << ((i * 8 + 3) - j));
        }
        // Takes the second 4-bits part of byte
        for (int j = i * 8 + 4; j <= i * 8 + 7; ++j){
            secPartByte |= (N1.at(j) << ((i * 8 + 7) - j));
        }
        // Makes the swap whis the S matrix
        firstPartByte = S[i * 2][firstPartByte];
        secPartByte = S[i * 2 + 1][secPartByte];
        // Concatenates two 4-bits parts back to byte
        for (int j = i * 8; j <= i * 8 + 3; ++j) {
            res[j] = (firstPartByte >> ((i * 8 + 3) - j)) & 0x01;
        }
        for (int j = i * 8 + 4; j <= i * 8 + 7; ++j) {
            res[j] = (secPartByte >> ((i * 8 + 7) - j)) & 0x01;
        }
    }

    return res;
}

QBitArray DecodeGammingTask::rRotation11Block(const QBitArray& N1)
{
    QBitArray res(32);
    // Rotate last 21 bits to the start positions and add the last 11 bits to the end
    for (int i = 11; i < N1.size(); ++i) {
        res.setBit(i - 11, N1.at(i));
    }
    for (int i = 0; i < 11; ++i) {
        res.setBit(21 + i, N1.at(i));
    }
    return res;
}

QBitArray DecodeGammingTask::summatorCM2mod2pow1(const QBitArray& N1, const QBitArray& N2)
{
    QBitArray res(N1);
    res ^= N2;
    return res;
}

QBitArray DecodeGammingTask::summatorCM4mod2pow32minus1(const QBitArray& N4, const QBitArray& C1)
{
    QBitArray res(N4);

    bool rem = false;
    for (int i = res.size() - 1; i >= 0; --i) {
        if (res.at(i) && C1.at(i)) {
            if (rem) {
                res[i] = true;
            }
            else {
                res[i] = false;
            }
            rem = true;
        }
        else if (res.at(i) || C1.at(i)) {
            if (rem) {
                res[i] = false;
            }
            else {
                res[i] = true;
            }
        }
        else {
            res[i] = rem;
            rem = false;
        }
    }

    if (rem) {
        rem = false;
        QBitArray C(32);
        C.setBit(31, true);

        for (int i = res.size() - 1; i >= 0; --i) {
            if (res.at(i) && C.at(i)) {
                if (rem) {
                    res[i] = true;
                }
                else {
                    res[i] = false;
                }
                rem = true;
            }
            else if (res.at(i) || C.at(i)) {
                if (rem) {
                    res[i] = false;
                }
                else {
                    res[i] = true;
                }
            }
            else {
                res[i] = rem;
                rem = false;
            }
        }
    }

    return res;
}

QBitArray DecodeGammingTask::summatorCM3mod2pow32(const QBitArray& N3, const QBitArray& C2)
{
    QBitArray res(N3);

    bool rem = false;
    for (int i = res.size() - 1; i >= 0; --i) {
        if (res.at(i) && C2.at(i)) {
            if (rem) {
                res[i] = true;
            }
            else {
                res[i] = false;
            }
            rem = true;
        }
        else if (res.at(i) || C2.at(i)) {
            if (rem) {
                res[i] = false;
            }
            else {
                res[i] = true;
            }
        }
        else {
            res[i] = rem;
            rem = false;
        }
    }

    return res;
}

QBitArray DecodeGammingTask::summatorCM5mod2(const QBitArray& N1, const QBitArray& N2, const QBitArray& text1, const QBitArray& text2)
{
    QBitArray res(64);
    for (int i = 0; i < 32; ++i) {
        res[i] = N1[i] ^ text1[i];
        res[32+i] = N2[i] ^ text2[i];
    }
    return res;
}

QBitArray DecodeGammingTask::getInitializingVector(const QByteArray& keyArray)
{
    QCryptographicHash hashFunction(QCryptographicHash::Sha3_512);
    QByteArray keyHash = hashFunction.hash(keyArray, QCryptographicHash::Sha3_512);
    QByteArray initializationVectorArray = keyHash.mid(36, 8);
    QBitArray res(64);
    for (int i = 0; i <= 7; ++i) {
        for (int j = 7; j >= 0; --j) {
            res.setBit(i * 8 + (7 - j), (1 << j) & keyArray[i]);
        }
    }
    return res;
}

DecodeGammingTask::~DecodeGammingTask() {}
