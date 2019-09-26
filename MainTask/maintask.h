#ifndef MAINTASK_H
#define MAINTASK_H

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>

class MainTask : public QWidget
{
    Q_OBJECT
public:
    explicit MainTask(QWidget *parent = nullptr);
     ~MainTask();

protected:
    // Change form elements text
    void changeTaskLabelText(QString);
    void changeResultLabelText(QString);
    void changeMakeActionPushButtonText(QString);

protected:
    //============Elements on form===========//
    QTextEdit* taskTextEdit;                 //
    QTextEdit* resultTextEdit;               //
    QLabel* taskLabel;                       //
    QLabel* resultLabel;                     //
    QPushButton* makeActionPushButton;       //
    QHBoxLayout* taskLayout;                 //
    QVBoxLayout* mainLayout;                 //
    QLabel* keyLabel;                        //
    QLineEdit* keyLineEdit;                  //
    QFormLayout* keyFormLayout;              //
    //=======================================//

    //===================================Parts of encryption/decryption schemas====================================================//
    // Sum const QBitArray& and const QBitArray& mod 2^32 and result returns in QBitArray                                          //
    QBitArray summatorCM1mod2pow32(const QBitArray&, const QBitArray&);                                                            //
    // Sum const QBitArray& and const QBitArray& mod 2 and result returns in QBitArray                                             //
    QBitArray summatorCM2mod2(const QBitArray&, const QBitArray&);                                                                 //
    // Sum const QBitArray& and const QBitArray& mod 2^32 and result returns in QBitArray                                          //
    QBitArray summatorCM3mod2pow32(const QBitArray&, const QBitArray&);                                                            //
    // Sum const QBitArray& and const QBitArray& mod 2^32-1 and result returns in QBitArray                                        //
    QBitArray summatorCM4mod2pow32minus1(const QBitArray&, const QBitArray&);                                                      //
    // Sum const QBitArray& and const QBitArray& mod 2 and result returns in QBitArray                                             //
    QBitArray summatorCM5mod2(const QBitArray&, const QBitArray&);                                                                 //
    // All bits in QBitArray& changes it's value with permutation matrix S (inside) matrix and result returns in QBitArray         //
    QBitArray kTransformBlock(const QBitArray&);                                                                                   //
    // Round rotate QBitArray& on 11 bits to elder bits and result returns in QBitArray                                            //
    QBitArray rRotation11Block(const QBitArray&);                                                                                  //
    // Get SynchroBlock from QByteArray and result returns in QBitArray                                                            //
    QBitArray getInitializingVector(const QByteArray&);                                                                            //
    //=============================================================================================================================//


    // Main encode cicle returns encoded text in normal order (First parameter: 64-bits text, second parameter: 256-bits key)
    QBitArray main323CicleEncode(const QBitArray&, const std::vector<QBitArray>&);
    // Main decode cicle (First parameter: 64-bits text, second parameter: 256-bits key)
    QBitArray main32PCicleDecode(const QBitArray&, const std::vector<QBitArray>&);
    // Main half-encode cicle (First parameter: 64-bits text, second parameter: 256-bits key)
    QBitArray main163Cicle(const QBitArray&, const std::vector<QBitArray>&);


    // Creates vector of eight 32 bits arrays of key from input and fill them in reverse order
    std::vector<QBitArray> getKey();
    // Creates QByteArray of text from input (divisible on 8 * 8 = 64 bits)
    QByteArray getText();
    // Get 64-bits QBitArray block of text from const QByteArray&
    QBitArray getBlockFromQByteArrayText(const QByteArray&, int);
    // Restore data from const QBitArray& to QByteArray (const QBitArray& should be in normal order)
    QByteArray restoreDataFromQBitArray(const QBitArray&);
    // Delete all null bytes from back of const QByteArray&
    QByteArray deleteAllNullByteFromBack(const QByteArray&);

signals:

public slots:
    // Makes makeActionPushButton ba active only when taskTextEdit isn't empty
    void tryMakeActionPushButtonEnabled();
    void checkTaskTextEdit();
    bool checkValidTaskTextEdit(QRegExp);
    virtual void mainMethod() = 0;

};

#endif // MAINTASK_H
