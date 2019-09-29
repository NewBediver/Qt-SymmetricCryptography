#include "maintask.h"

#include <QRegExpValidator>
#include <QCryptographicHash>
#include <QBitArray>
#include <QByteArray>

MainTask::MainTask(QWidget *parent) : QWidget(parent)
{
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
    unsigned char S[8][16] = {
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

QBitArray MainTask::getInitializingVector(const QByteArray& keyArray)
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
    for (int i = 0; i < 8; ++i){
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

MainTask::~MainTask()
{
    delete taskTextEdit;
    delete resultTextEdit;
    delete taskLabel;
    delete resultLabel;
    delete makeActionPushButton;
    delete taskLayout;    
    delete keyLabel;
    delete keyLineEdit;
    delete keyFormLayout;
    delete mainLayout;  
}
