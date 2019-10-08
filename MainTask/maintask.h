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
    QLabel* warningLabel;                    //
    QPushButton* makeActionPushButton;       //
    QHBoxLayout* taskLayout;                 //
    QVBoxLayout* mainLayout;                 //
    QLabel* keyLabel;                        //
    QLineEdit* keyLineEdit;                  //
    QFormLayout* keyFormLayout;              //
    //=======================================//

    // Only when need initial vector
    QLabel* IVLabel;
    QLineEdit* IVLineEdit;

    //===================================Parts of encryption/decryption schemas for Magma==========================================//
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
    // All bits in QBitArray& changes it's value with permutation matrix S (inside) and result returns in QBitArray                //
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


    // Creates vector of eight 32 bits arrays of key from input and fill them in normal order
    std::vector<QBitArray> getKey();
    // Creates QByteArray of text from input (divisible on 8 * 8 = 64 bits)
    QByteArray getText();
    // Get 64-bits QBitArray block of text from const QByteArray&
    QBitArray getBlockFromQByteArrayText(const QByteArray&, int);
    // Restore data from const QBitArray& to QByteArray (const QBitArray& should be in normal order)
    QByteArray restoreDataFromQBitArray(const QBitArray&);
    // Delete all null bytes from back of const QByteArray&
    QByteArray deleteAllNullByteFromBack(const QByteArray&);

    //===================================Parts of encryption/decryption schemas for Kuznechik======================================//
    // Sum const QBitArray& and const QBitArray& mod 2 and result returns in QBitArray                                             //
    QBitArray xConversionBlockForKuznechik(const QBitArray&, const QBitArray&);                                                    //
    // All bits in QBitArray& changes it's value with permutation matrix S (inside) and result returns in QBitArray                //
    QBitArray sTransformBlockForKuznechik(const QBitArray&);                                                                       //
    // All bits in QBitArray& changes it's value with reverse permutation matrix S (inside) and result returns in QBitArray        //
    QBitArray sReverseTransformBlockForKuznechik(const QBitArray&);                                                                //
    // Shift const QBitArray& on eight bit right and first eight bits fills with XOR of all GF8 multiplication with L[i] elements  //
    QBitArray rTransformBlockForKuznechik(const QBitArray&);                                                                       //
    // Shift const QBitArray& on eight bit left and last eight bits fills with XOR of all GF8 multiplication with L[i] elements    //
    QBitArray rReverseTransformBlockForKuznechik(const QBitArray&);                                                                //
    // Make 16 times function rTransformBlockForKuznechik(const QBitArray&) on const QBitArray&                                    //
    QBitArray lTransformBlockForKuznechik(const QBitArray&);                                                                       //
    // Make 16 times function rReverseTransformBlockForKuznechik(const QBitArray&) on const QBitArray&                             //
    QBitArray lReverseTransformBlockForKuznechik(const QBitArray&);                                                                //
    // One round of code (FP: 256 bit text block, SP: 128 bit round key)                                                           //
    QBitArray fTransformBlockForKuznechik(const QBitArray&, const QBitArray&);                                                     //
    // Get SynchroBlock from QByteArray and result returns in QBitArray                                                            //
    QBitArray getInitializing128Vector(const QByteArray&);                                                                         //
    // Sum const QBitArray& and const QBitArray& mod 2^32-1 and result returns in QBitArray                                        //
    QBitArray summator128mod2pow32minus1(const QBitArray&, const QBitArray&);                                                      //
    // Sum const QBitArray& and const QBitArray& mod 2^32 and result returns in QBitArray                                          //
    QBitArray summator128mod2pow32(const QBitArray&, const QBitArray&);                                                            //
    //=============================================================================================================================//

    // Main encode cicle returns encoded text in normal order (First parameter: 128-bits text, second parameter: 256-bits key)
    QBitArray kuznechikEncodeCicle(const QBitArray&, const std::vector<QBitArray>&);
    // Main decode cicle returns decoded text in normal order (First parameter: 128-bits text, second parameter: 256-bits key)
    QBitArray kuznechikDecodeCicle(const QBitArray&, const std::vector<QBitArray>&);

    // Creates QByteArray of text from input (divisible on 8 * 16 = 128 bits)
    QByteArray getTextForKuznechik();
    // Multiplication on Galua Field (p(x) = x^8 + x^7 + x^6 + x + 1)
    QBitArray GFMulForKuznechik(unsigned char, unsigned char);
    // Creates QByteArray of text from input (divisible on 8 * 16 = 128 bits)
    QBitArray  getBlock128FromQByteArrayText(const QByteArray&, int);
    // Creates vector of two 128 bits arrays of key from input and fill them in normal order
    std::vector<QBitArray> getKeyForKuznechik();

signals:

public slots:
    // Makes makeActionPushButton ba active only when taskTextEdit isn't empty
    void tryMakeActionPushButtonEnabled();
    void checkTaskTextEdit();
    bool checkValidTaskTextEdit(QRegExp);
    virtual void mainMethod() = 0;

};

#endif // MAINTASK_H
