#include "maintask.h"

#include <QRegExpValidator>
#include <QBitArray>
#include <QByteArray>

MainTask::MainTask(QWidget *parent) : QWidget(parent)
{
    IVLabel = new QLabel();
    IVLineEdit = new QLineEdit();

    // Create warning label
    warningLabel = new QLabel();
    warningLabel->setText("ATTENTION! This program works only with HEX data. Please convert all your input into HEX format before you try to encode/decode it.");

    //Create task edit field
    taskTextEdit = new QTextEdit();
    connect(taskTextEdit, SIGNAL(textChanged()), this, SLOT(checkTaskTextEdit()));

    //Create task label
    taskLabel = new QLabel();
    changeTaskLabelText("Encoded text:");

    //Set taskLabel buddy
    taskLabel->setBuddy(taskTextEdit);

    //Create key label
    keyLabel = new QLabel();
    keyLabel->setText("Key:");

    //Create key edit field
    keyLineEdit = new QLineEdit();
    keyLineEdit->setToolTip("Enter key");
    keyLineEdit->setValidator(new QRegExpValidator(QRegExp("[A-Fa-f0-9]{0,64}")));

    //Set keyLabel buddy
    keyLabel->setBuddy(keyLineEdit);

    //Create task button
    makeActionPushButton = new QPushButton();
    makeActionPushButton->setEnabled(false);
    makeActionPushButton->setDefault(true);
    changeMakeActionPushButtonText("Do something");
    connect(taskTextEdit, SIGNAL(textChanged()), this, SLOT(tryMakeActionPushButtonEnabled()));
    connect(keyLineEdit, SIGNAL(textChanged(QString)), this, SLOT(tryMakeActionPushButtonEnabled()));

    //Create output text edit and make it ReadOnly
    resultTextEdit = new QTextEdit();
    resultTextEdit->setReadOnly(true);

    //Create result label
    resultLabel = new QLabel();
    changeResultLabelText("Result text:");

    //Set resultLabel buddy
    resultLabel->setBuddy(resultTextEdit);

    //Add key elements to form layout
    keyFormLayout = new QFormLayout();
    keyFormLayout->addRow(keyLabel, keyLineEdit);

    //Add task widgets to taskLayout
    taskLayout = new QHBoxLayout();
    taskLayout->addWidget(taskTextEdit);
    taskLayout->addWidget(makeActionPushButton);

    //Add everything to mainLayout
    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(warningLabel);
    mainLayout->addLayout(keyFormLayout);
    mainLayout->addWidget(taskLabel);
    mainLayout->addLayout(taskLayout);
    mainLayout->addWidget(resultLabel);
    mainLayout->addWidget(resultTextEdit);

    connect(makeActionPushButton, SIGNAL(clicked()), this, SLOT(mainMethod()));
}

void MainTask::tryMakeActionPushButtonEnabled()
{
    if (taskTextEdit->toPlainText().isEmpty() || keyLineEdit->text().isEmpty()) {
        makeActionPushButton->setEnabled(false);
    }
    else {
        makeActionPushButton->setEnabled(true);
    }
}

void MainTask::changeTaskLabelText(QString newText)
{
    taskLabel->setText(newText);
    taskTextEdit->setStatusTip(taskLabel->text().mid(0, taskLabel->text().length()-1));
}

void MainTask::changeResultLabelText(QString newText)
{
    resultLabel->setText(newText);
    resultTextEdit->setStatusTip(resultLabel->text().mid(0, resultLabel->text().length()-1));
}

void MainTask::changeMakeActionPushButtonText(QString newText)
{
    makeActionPushButton->setText(newText);
    makeActionPushButton->setStatusTip("Let's " + makeActionPushButton->text());
}

void MainTask::checkTaskTextEdit()
{
    if (!checkValidTaskTextEdit(QRegExp("[A-Fa-f0-9]*"))) {
        taskTextEdit->setText(taskTextEdit->toPlainText().remove(QRegExp("[^A-Fa-f0-9]")));
        taskTextEdit->moveCursor(QTextCursor::End);
    }
}

bool MainTask::checkValidTaskTextEdit(QRegExp reg)
{
    return reg.exactMatch(taskTextEdit->toPlainText());
}

// MAGMA BLOCKS
QBitArray MainTask::main323CicleEncode(const QBitArray& text, const std::vector<QBitArray>& key)
{
    // Creates two 32 bits arrays N1 and N2 and fill them in normal order
    QBitArray N1(32);
    QBitArray N2(32);
    for (int i = 0; i < 32; ++i) {
        N1.setBit(i, text.at(32 + i));
        N2.setBit(i, text.at(i));
    }

    // Then we have 32 rounds of encryption
    // First 24 rounds use X0 X1 X2 X3 X4 X5 X6 X7 3 times
    for (int j = 0; j < 24; ++j) {
        // Save N1 source value
        QBitArray tempN1(N1);

        // Choose the right Xj (depends on round number)
        QBitArray X = key[j % 8];

        // Sum N1 and X mod 2^32 and result saves in N1
        N1 = summatorCM1mod2pow32(N1, X);

        // All bytes in N1 changes it's value with the S matrix and result saves in N1
        N1 = kTransformBlock(N1);

        // Round rotate N1 on 11 bits to elder bits and result saves in N1
        N1 = rRotation11Block(N1);

        // Sum N1 and N2 mod 2 and result saves in N1
        N1 = summatorCM2mod2(N1, N2);

        // Return old N1 value to N2
        N2 = tempN1;
    }
    // Last 8 rounds use X7 X6 X5 X4 X3 X2 X1 X0 1 time
    for (int j = 0; j < 8; ++j) {
        // Save N2 source value
        QBitArray tempN1(N1);

        // Choose the right Xj (depends on round number)
        QBitArray X = key[7 - (j % 8)];

        // Sum N1 and X mod 2^32 and result saves in N1
        N1 = summatorCM1mod2pow32(N1, X);

        // All bytes in N1 changes it's value with the S matrix and result saves in N1
        N1 = kTransformBlock(N1);

        // Round rotate N1 on 11 bits to elder bits and result saves in N1
        N1 = rRotation11Block(N1);

        // If it is not 32 round
        if (j != 7) {
            // Sum N1 and N2 mod 2 and result saves in N1
            N1 = summatorCM2mod2(N1, N2);

            // Return old N1 value to N2
            N2 = tempN1;
        }
        else {
            // Sum N1 and N2 mod 2 and result saves in N2
            N2 = summatorCM2mod2(N1, N2);

            // Return old N1 value to N1
            N1 = tempN1;
        }
    }

    // Create result block array in normal order to return
    QBitArray res(64);
    for (int i = 0; i < 32; ++i) {
        res.setBit(i + 32, N1.at(i));
        res.setBit(i, N2.at(i));
    }

    return res;
}

QBitArray MainTask::main32PCicleDecode(const QBitArray& text, const std::vector<QBitArray>& key)
{
    // Creates two 32 bits arrays N1 and N2 and fill them in normal order
    QBitArray N1(32);
    QBitArray N2(32);
    for (int i = 0; i < 32; ++i) {
        N1.setBit(i, text.at(32 + i));
        N2.setBit(i, text.at(i));
    }

    // Then we have 32 rounds of decryption
    // First 8 rounds use X0 X1 X2 X3 X4 X5 X6 X7 1 time
    for (int j = 0; j < 8; ++j) {
        // Save N1 source value
        QBitArray tempN1(N1);

        // Choose the right Xj (depends on round number)
        QBitArray X = key[j % 8];

        // Sum N1 and X mod 2^32 and result saves in N1
        N1 = summatorCM1mod2pow32(N1, X);

        // All bytes in N1 changes it's value with the S matrix and result saves in N1
        N1 = kTransformBlock(N1);

        // Round rotate N1 on 11 bits to elder bits and result saves in N1
        N1 = rRotation11Block(N1);

        // Sum N1 and N2 mod 2 and result saves in N1
        N1 = summatorCM2mod2(N1, N2);

        // Return old N1 value to N2
        N2 = tempN1;

    }
    // Last 24 rounds use X7 X6 X5 X4 X3 X2 X1 X0 3 times
    for (int j = 0; j < 24; ++j) {
        // Save N1 source value
        QBitArray tempN1(N1);

        // Choose the right Xj (depends on round number)
        QBitArray X = key[7 - (j % 8)];

        // Sum N1 and X mod 2^32 and result saves in N1
        N1 = summatorCM1mod2pow32(N1, X);

        // All bytes in N1 changes it's value with the S matrix and result saves in N1
        N1 = kTransformBlock(N1);

        // Round rotate N1 on 11 bits to elder bits and result saves in N1
        N1 = rRotation11Block(N1);

        // If it is not 32 round
        if (j != 23) {
            // Sum N1 and N2 mod 2 and result saves in N1
            N1 = summatorCM2mod2(N1, N2);

            // Return old N1 value to N2
            N2 = tempN1;
        }
        else {
            // Sum N1 and N2 mod 2 and result saves in N2
            N2 = summatorCM2mod2(N1, N2);

            // Return old N1 value to N1
            N1 = tempN1;
        }
    }

    // Create result block array in normal order to return
    QBitArray res(64);
    for (int i = 0; i < 32; ++i) {
        res.setBit(i + 32, N1.at(i));
        res.setBit(i, N2.at(i));
    }

    return res;
}

QBitArray MainTask::main163Cicle(const QBitArray& text, const std::vector<QBitArray>& key)
{
    // Creates two 32 bits arrays N1 and N2 and fill them in normal order
    QBitArray N1(32);
    QBitArray N2(32);
    for (int i = 0; i < 32; ++i) {
        N1.setBit(i, text.at(32 + i));
        N2.setBit(i, text.at(i));
    }

    // Then we have 16 rounds of encryption
    // 16 rounds use X0 X1 X2 X3 X4 X5 X6 X7 2 times
    for (int j = 0; j < 16; ++j) {
        // Save N1 source value
        QBitArray tempN1(N1);

        // Choose the right Xj (depends on round number)
        QBitArray X = key[j % 8];

        // Sum N1 and X mod 2^32 and result saves in N1
        N1 = summatorCM1mod2pow32(N1, X);

        // All bytes in N1 changes it's value with the S matrix and result saves in N1
        N1 = kTransformBlock(N1);

        // Round rotate N1 on 11 bits to elder bits and result saves in N1
        N1 = rRotation11Block(N1);

        // Sum N1 and N2 mod 2 and result saves in N1
        N1 = summatorCM2mod2(N1, N2);

        // Return old N1 value to N2
        N2 = tempN1;

    }

    // Create result block array in normal order to return
    QBitArray res(64);
    for (int i = 0; i < 32; ++i) {
        res.setBit(i + 32, N1.at(i));
        res.setBit(i, N2.at(i));
    }

    return res;
}

QBitArray MainTask::summatorCM1mod2pow32(const QBitArray& N1, const QBitArray& X)
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

QBitArray MainTask::summatorCM2mod2(const QBitArray& N1, const QBitArray& N2)
{
    QBitArray res(N1);
    res ^= N2;
    return res;
}

QBitArray MainTask::summatorCM3mod2pow32(const QBitArray& N3, const QBitArray& C2)
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

QBitArray MainTask::summatorCM4mod2pow32minus1(const QBitArray& N4, const QBitArray& C1)
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

QBitArray MainTask::summatorCM5mod2(const QBitArray& text, const QBitArray& gamma)
{
    QBitArray res(64);
    for (int i = 0; i < 64; ++i) {
        res[i] = text[i] ^ gamma[i];
    }
    return res;
}

QBitArray MainTask::kTransformBlock(const QBitArray& N1)
{
    // S-matrix
    const unsigned char S[8][16] = {
        {12, 4, 6, 2, 10, 5, 11, 9, 14, 8, 13, 7, 0, 3, 15, 1},
        {6, 8, 2, 3, 9, 10, 5, 12, 1, 14, 4, 7, 1, 13, 0, 15},
        {11, 3, 5, 8, 2, 15, 10, 13, 14, 1, 7, 4, 12, 9, 6, 0},
        {12, 8, 2, 1, 13, 4, 15, 6, 7, 0, 10, 5, 3, 14, 9, 11},
        {7, 15, 5, 10, 8, 1, 6, 13, 0, 9, 3, 14, 11, 4, 2, 12},
        {5, 13, 15, 6, 9, 2, 12, 10, 11, 7, 8, 1, 4, 3, 14, 0},
        {8, 14, 2, 5, 6, 9, 1, 12, 15, 4, 11, 0, 13, 10, 3, 7},
        {1, 7, 14, 13, 0, 5, 8, 3, 4, 15, 10, 6, 9, 12, 11, 2}
    };

    QBitArray res(32);

    int fourBitBlock;
    for (int i = 0; i < 8; i++)
    {
        fourBitBlock = 0;
        // Takes first 4 bits
        for (int j = i * 4; j < i * 4 + 4; ++j) {
            fourBitBlock |= (N1[j] << (i * 4 + 3 - j));
        }
        //Takes new value from S
        fourBitBlock = S[7 - i][fourBitBlock];
        // Insert new value into the res
        for (int j = 0; j < 4; ++j) {
            res.setBit(i * 4 + j, (1 << (3 - j)) & fourBitBlock);
        }
    }

    return res;
}

QBitArray MainTask::rRotation11Block(const QBitArray& N1)
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

QBitArray MainTask::getInitializingVector(const QByteArray& key)
{
    QByteArray keyArray(key);
    keyArray.append(16 - keyArray.length(), 0x00);

    QBitArray res(64);
    for (int i = 0; i <= 7; ++i) {
        for (int j = 7; j >= 0; --j) {
            res.setBit(i * 8 + (7 - j), (1 << j) & keyArray[i]);
        }
    }
    return res;
}

std::vector<QBitArray> MainTask::getKey()
{
    // Key array 32 * 8 = 256 bits (0 padding if key less than 256 bits)
    QByteArray keyArray = QByteArray::fromHex(keyLineEdit->text().toLatin1());
    keyArray.append(32 - keyArray.length(), 0x00);

    // Creates vector of eight 32 bits arrays of key and fill them in normal order
    std::vector<QBitArray> X(8, QBitArray(32));
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 8; ++j) {
            X[0].setBit(i * 8 + j, (1 << (7 - j)) & keyArray[i]);
            X[1].setBit(i * 8 + j, (1 << (7 - j)) & keyArray[i + 4]);
            X[2].setBit(i * 8 + j, (1 << (7 - j)) & keyArray[i + 8]);
            X[3].setBit(i * 8 + j, (1 << (7 - j)) & keyArray[i + 12]);
            X[4].setBit(i * 8 + j, (1 << (7 - j)) & keyArray[i + 16]);
            X[5].setBit(i * 8 + j, (1 << (7 - j)) & keyArray[i + 20]);
            X[6].setBit(i * 8 + j, (1 << (7 - j)) & keyArray[i + 24]);
            X[7].setBit(i * 8 + j, (1 << (7 - j)) & keyArray[i + 28]);
        }
    }

    return X;
}

QByteArray MainTask::getText()
{
    QByteArray textArray = QByteArray::fromHex(taskTextEdit->toPlainText().toLatin1());
    if (textArray.length() % 8 != 0) {
        textArray.append(8 - textArray.length() % 8, 0x00);
    }
    return textArray;
}

QBitArray MainTask::getBlockFromQByteArrayText(const QByteArray& textArray, int numberOfBlock)
{
    QBitArray textBlockBitArray(64);
    for (int i = 8 * numberOfBlock; i < 8 * numberOfBlock + 8; ++i) {
        for (int j = 7; j >= 0; --j) {
            textBlockBitArray.setBit((i - 8 * numberOfBlock) * 8 + (7 - j), (1 << j) & static_cast<int>(textArray[i]));
        }
    }
    return textBlockBitArray;
}

QByteArray MainTask::restoreDataFromQBitArray(const QBitArray& text)
{
    QByteArray resultText;
    int numOfBlocks = text.size() / 8;
    for (int i = 0; i < numOfBlocks; ++i){
        char temp = 0x00;
        for (int j = 0; j < 8; ++j) {
            temp |= (text[i * 8 + j] << (7 - j));
        }
        resultText.append(temp);
    }
    return resultText;
}

QByteArray MainTask::deleteAllNullByteFromBack(const QByteArray& text)
{
    int countNullBytes = 0;
    for (int i = text.size() - 1; i >= 0; --i) {
        if (text.at(i) != 0x00) {
            break;
        }
        ++countNullBytes;
    }
    return text.mid(0, text.size() - countNullBytes);
}

// KUZNECHIK BLOCKS
QBitArray MainTask::getBlock128FromQByteArrayText(const QByteArray& textArray, int numberOfBlock)
{
    QBitArray textBlockBitArray(128);
    for (int i = 16 * numberOfBlock; i < 16 * numberOfBlock + 16; ++i) {
        for (int j = 7; j >= 0; --j) {
            textBlockBitArray.setBit((i - 16 * numberOfBlock) * 8 + (7 - j), (1 << j) & static_cast<int>(textArray[i]));
        }
    }
    return textBlockBitArray;
}

std::vector<QBitArray> MainTask::getKeyForKuznechik()
{
    // Key array 32 * 8 = 256 bits (0 padding if key less than 256 bits)
    QByteArray keyArray = QByteArray::fromHex(keyLineEdit->text().toLatin1());
    keyArray.append(32 - keyArray.length(), 0x00);

    QBitArray K(256);
    // Creates vector of two 128 bits arrays of key and fill them in normal order
    std::vector<QBitArray> X(10, QBitArray(128));
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 8; ++j) {
            X[0].setBit(i * 8 + j, (1 << (7 - j)) & keyArray[i]);
            X[1].setBit(i * 8 + j, (1 << (7 - j)) & keyArray[i + 16]);
            K.setBit(i * 8 + j, (1 << (7 - j)) & keyArray[i]);
            K.setBit(128 + (i * 8 + j), (1 << (7 - j)) & keyArray[i + 16]);
        }
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = i * 8 + 1; j <= i * 8 + 8; ++j) {
            QBitArray currC(128);
            int temp = j;
            int index = 127;
            while (temp > 0) {
                if (temp % 2 == 0) {
                    currC.setBit(index, false);
                }
                else {
                    currC.setBit(index, true);
                }
                temp >>= 1;
                --index;
            }
            K = fTransformBlockForKuznechik(K, lTransformBlockForKuznechik(currC));
        }

        for (int j = 0; j < 128; ++j) {
            X[static_cast<unsigned int>((i+1)*2)].setBit(j, K[j]);
            X[static_cast<unsigned int>((i+1)*2+1)].setBit(j, K[128 + j]);
        }
    }

    return X;
}

QByteArray MainTask::getTextForKuznechik()
{
    QByteArray textArray = QByteArray::fromHex(taskTextEdit->toPlainText().toLatin1());
    if (textArray.length() % 16 != 0) {
        textArray.append(16 - textArray.length() % 16, 0x00);
    }
    return textArray;
}

QBitArray MainTask::xConversionBlockForKuznechik(const QBitArray& vec1, const QBitArray& vec2)
{
    QBitArray res(128);
    for (int i = 0; i < 128; ++i) {
        res[i] = vec1[i] ^ vec2[i];
    }
    return res;
}

QBitArray MainTask::sTransformBlockForKuznechik(const QBitArray& text)
{
    // S-matrix
    const unsigned char S[256] = {
        252, 238, 221, 17, 207, 110, 49, 22, 251, 196, 250, 218, 35, 197, 4, 77, 233, 119, 240, 219, 147, 46,
        153, 186, 23, 54, 241, 187, 20, 205, 95, 193, 249, 24, 101, 90, 226, 92, 239, 33, 129, 28, 60, 66 , 139, 1, 142,
        79, 5, 132, 2, 174, 227, 106, 143, 160, 6, 11, 237, 152, 127, 212, 211, 31, 235, 52, 44, 81, 234, 200, 72, 171,
        242, 42, 104, 162, 253, 58, 206, 204, 181, 112, 14, 86, 8 , 12, 118, 18, 191, 114, 19, 71, 156, 183, 93, 135,
        21, 161, 150, 41, 16, 123, 154, 199, 243, 145, 120, 111, 157, 158, 178, 177, 50, 117, 25, 61, 255, 53, 138,
        126, 109, 84, 198, 128, 195, 189, 13, 87, 223, 245, 36, 169, 62, 168, 67, 201, 215, 121, 214, 246, 124, 34,
        185, 3, 224, 15, 236, 222, 122, 148, 176, 188, 220, 232, 40, 80, 78, 51, 10, 74, 167, 151, 96, 115, 30, 0, 98,
        68, 26, 184, 56, 130, 100, 159, 38, 65, 173, 69, 70, 146, 39, 94, 85, 47, 140, 163, 165, 125, 105, 213, 149,
        59, 7, 88, 179, 64, 134, 172, 29, 247, 48, 55, 107, 228, 136, 217, 231, 137, 225, 27, 131, 73, 76, 63, 248,
        254, 141, 83, 170, 144, 202, 216, 133, 97, 32, 113, 103, 164, 45, 43, 9, 91,203, 155, 37, 208, 190, 229, 108,
        82, 89, 166, 116, 210, 230, 244, 180, 192, 209, 102, 175, 194, 57, 75, 99, 182
    };

    QBitArray res(128);

    int eightBitBlock;
    for (int i = 0; i < 16; i++)
    {
        eightBitBlock = 0;
        // Takes first 8 bits
        for (int j = i * 8; j < i * 8 + 8; ++j) {
            eightBitBlock |= (text[j] << (i * 8 + 7 - j));
        }
        //Takes new value from S
        eightBitBlock = S[eightBitBlock];
        // Insert new value into the res
        for (int j = 0; j < 8; ++j) {
            res.setBit(i * 8 + j, (1 << (7 - j)) & eightBitBlock);
        }
    }

    return res;
}

QBitArray MainTask::sReverseTransformBlockForKuznechik(const QBitArray& text)
{
    // S-matrix
    const unsigned char S[256] = {
        0xA5, 0x2D, 0x32, 0x8F, 0x0E, 0x30, 0x38, 0xC0, 0x54, 0xE6, 0x9E, 0x39, 0x55, 0x7E, 0x52, 0x91,
        0x64, 0x03, 0x57, 0x5A, 0x1C, 0x60, 0x07, 0x18, 0x21, 0x72, 0xA8, 0xD1, 0x29, 0xC6, 0xA4, 0x3F,
        0xE0, 0x27, 0x8D, 0x0C, 0x82, 0xEA, 0xAE, 0xB4, 0x9A, 0x63, 0x49, 0xE5, 0x42, 0xE4, 0x15, 0xB7,
        0xC8, 0x06, 0x70, 0x9D, 0x41, 0x75, 0x19, 0xC9, 0xAA, 0xFC, 0x4D, 0xBF, 0x2A, 0x73, 0x84, 0xD5,
        0xC3, 0xAF, 0x2B, 0x86, 0xA7, 0xB1, 0xB2, 0x5B, 0x46, 0xD3, 0x9F, 0xFD, 0xD4, 0x0F, 0x9C, 0x2F,
        0x9B, 0x43, 0xEF, 0xD9, 0x79, 0xB6, 0x53, 0x7F, 0xC1, 0xF0, 0x23, 0xE7, 0x25, 0x5E, 0xB5, 0x1E,
        0xA2, 0xDF, 0xA6, 0xFE, 0xAC, 0x22, 0xF9, 0xE2, 0x4A, 0xBC, 0x35, 0xCA, 0xEE, 0x78, 0x05, 0x6B,
        0x51, 0xE1, 0x59, 0xA3, 0xF2, 0x71, 0x56, 0x11, 0x6A, 0x89, 0x94, 0x65, 0x8C, 0xBB, 0x77, 0x3C,
        0x7B, 0x28, 0xAB, 0xD2, 0x31, 0xDE, 0xC4, 0x5F, 0xCC, 0xCF, 0x76, 0x2C, 0xB8, 0xD8, 0x2E, 0x36,
        0xDB, 0x69, 0xB3, 0x14, 0x95, 0xBE, 0x62, 0xA1, 0x3B, 0x16, 0x66, 0xE9, 0x5C, 0x6C, 0x6D, 0xAD,
        0x37, 0x61, 0x4B, 0xB9, 0xE3, 0xBA, 0xF1, 0xA0, 0x85, 0x83, 0xDA, 0x47, 0xC5, 0xB0, 0x33, 0xFA,
        0x96, 0x6F, 0x6E, 0xC2, 0xF6, 0x50, 0xFF, 0x5D, 0xA9, 0x8E, 0x17, 0x1B, 0x97, 0x7D, 0xEC, 0x58,
        0xF7, 0x1F, 0xFB, 0x7C, 0x09, 0x0D, 0x7A, 0x67, 0x45, 0x87, 0xDC, 0xE8, 0x4F, 0x1D, 0x4E, 0x04,
        0xEB, 0xF8, 0xF3, 0x3E, 0x3D, 0xBD, 0x8A, 0x88, 0xDD, 0xCD, 0x0B, 0x13, 0x98, 0x02, 0x93, 0x80,
        0x90, 0xD0, 0x24, 0x34, 0xCB, 0xED, 0xF4, 0xCE, 0x99, 0x10, 0x44, 0x40, 0x92, 0x3A, 0x01, 0x26,
        0x12, 0x1A, 0x48, 0x68, 0xF5, 0x81, 0x8B, 0xC7, 0xD6, 0x20, 0x0A, 0x08, 0x00, 0x4C, 0xD7, 0x74
    };

    QBitArray res(128);

    int eightBitBlock;
    for (int i = 0; i < 16; i++)
    {
        eightBitBlock = 0;
        // Takes first 8 bits
        for (int j = i * 8; j < i * 8 + 8; ++j) {
            eightBitBlock |= (text[j] << (i * 8 + 7 - j));
        }
        //Takes new value from S
        eightBitBlock = S[eightBitBlock];
        // Insert new value into the res
        for (int j = 0; j < 8; ++j) {
            res.setBit(i * 8 + j, (1 << (7 - j)) & eightBitBlock);
        }
    }

    return res;
}

QBitArray MainTask::rTransformBlockForKuznechik(const QBitArray& text)
{
    const unsigned char L[16] = {
        148, 32, 133, 16, 194, 192, 1, 251,
        1, 192, 194, 16, 133, 32, 148, 1
    };

    QBitArray res(128);

    // Move all bits on 8 bits right
    for (int i = 0; i < text.size() - 8; ++i) {
        res.setBit(i + 8, text[i]);
    }

    QBitArray a(8);
    // Count first 8 bits
    for (int i = 0; i < 16; ++i)
    {
        unsigned char eightBitBlock = 0;
        // Takes first 8 bits
        for (int j = i * 8; j < i * 8 + 8; ++j) {
            eightBitBlock |= (text[j] << (i * 8 + 7 - j));
        }
        a ^= GFMulForKuznechik(eightBitBlock, L[i]);
    }
    // Insert new value into the res
    for (int i = 0; i < 8; ++i) {
        res.setBit(i, a[i]);
    }

    return res;
}

QBitArray MainTask::rReverseTransformBlockForKuznechik(const QBitArray& text)
{
    const unsigned char L[16] = {
        148, 32, 133, 16, 194, 192, 1, 251,
        1, 192, 194, 16, 133, 32, 148, 1
    };

    QBitArray res(128);

    // Move all bits on 8 bits left
    for (int i = 8; i < text.size(); ++i) {
        res.setBit(i - 8, text[i]);
    }

    QBitArray a(8);
    // Takes first 8 bits
    for (int i = 0; i < 8; ++i) {
        a.setBit(i, text[i]);
    }

    // Count last 8 bits
    for (int i = 1; i < 16; ++i)
    {
        unsigned char eightBitBlock = 0;
        // Takes first 8 bits
        for (int j = i * 8; j < i * 8 + 8; ++j) {
            eightBitBlock |= (text[j] << (i * 8 + 7 - j));
        }
        a ^= GFMulForKuznechik(eightBitBlock, L[i - 1]);
    }

    // Insert new value into the res
    for (int i = 0; i < 8; ++i) {
        res.setBit(120 + i, a[i]);
    }

    return res;
}

QBitArray MainTask::lTransformBlockForKuznechik(const QBitArray& text)
{
    QBitArray res = text;
    for (int i = 0; i < 16; ++i) {
        res = rTransformBlockForKuznechik(res);
    }
    return res;
}

QBitArray MainTask::lReverseTransformBlockForKuznechik(const QBitArray& text)
{
    QBitArray res = text;
    for (int i = 0; i < 16; ++i) {
        res = rReverseTransformBlockForKuznechik(res);
    }
    return res;
}

QBitArray MainTask::fTransformBlockForKuznechik(const QBitArray& text, const QBitArray& k)
{
    QBitArray a1(128), a0(128);
    for (int i = 0; i < 128; ++i) {
        a1.setBit(i, text[i]);
        a0.setBit(i, text[i+128]);
    }

    QBitArray tempA1 = a1;

    QBitArray encodedBlock = xConversionBlockForKuznechik(k, a1);
    encodedBlock = sTransformBlockForKuznechik(encodedBlock);
    encodedBlock = lTransformBlockForKuznechik(encodedBlock);

    encodedBlock ^= a0;

    QBitArray res(256);
    for (int i = 0; i < 128; ++i) {
        res.setBit(i, encodedBlock[i]);
        res.setBit(i + 128, tempA1[i]);
    }

    return res;
}

QBitArray MainTask::summator128mod2pow32minus1(const QBitArray& text, const QBitArray& C1)
{
    QBitArray res(text);

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
        QBitArray C(64);
        C.setBit(63, true);

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

QBitArray MainTask::summator128mod2pow32(const QBitArray& text, const QBitArray& C2)
{
    QBitArray res(text);

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

QBitArray MainTask::kuznechikEncodeCicle(const QBitArray& text, const std::vector<QBitArray>& K)
{
    QBitArray res = text;
    for (size_t i = 0; i < K.size() - 1; ++i) {
        res = xConversionBlockForKuznechik(res, K[i]);
        res = sTransformBlockForKuznechik(res);
        res = lTransformBlockForKuznechik(res);
    }
    return xConversionBlockForKuznechik(res, K.back());
}

QBitArray MainTask::kuznechikDecodeCicle(const QBitArray& text, const std::vector<QBitArray>& K)
{
    QBitArray res = text;
    for (size_t i = K.size()-1; i > 0; --i) {
        res = xConversionBlockForKuznechik(res, K[i]);
        res = lReverseTransformBlockForKuznechik(res);
        res = sReverseTransformBlockForKuznechik(res);
    }
    return xConversionBlockForKuznechik(res, K.front());
}

QBitArray MainTask::getInitializing128Vector(const QByteArray& key)
{
    QByteArray keyArray(key);
    keyArray.append(32 - keyArray.length(), 0x00);

    QBitArray res(128);
    for (int i = 0; i < 16; ++i) {
        for (int j = 7; j >= 0; --j) {
            res.setBit(i * 8 + (7 - j), (1 << j) & keyArray[i]);
        }
    }
    return res;
}

QBitArray MainTask::GFMulForKuznechik(unsigned char eightBitBlock, unsigned char l)
{
    unsigned char z = 0;
    while (l > 0) {
        if (l & 1) {
            z ^= eightBitBlock;
        }
        eightBitBlock = static_cast<unsigned char>(eightBitBlock << 1) ^ (eightBitBlock & 0x80 ? 0xC3 : 0x00);
        l >>= 1;
    }

    QBitArray res(8);
    // Insert z value into the res
    for (int i = 0; i < 8; ++i) {
        res.setBit(i, (1 << (7 - i)) & z);
    }
    return res;
}

MainTask::~MainTask()
{
    delete taskTextEdit;
    delete resultTextEdit;
    delete taskLabel;
    delete resultLabel;
    delete warningLabel;
    delete makeActionPushButton;
    delete taskLayout;    
    delete keyLabel;
    delete keyLineEdit;
    delete IVLabel;
    delete IVLineEdit;
    delete keyFormLayout;
    delete mainLayout;  
}
