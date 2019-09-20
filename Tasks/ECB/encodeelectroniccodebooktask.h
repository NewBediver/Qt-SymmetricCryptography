#ifndef ENCODEELECTRONICCODEBOOKTASK_H
#define ENCODEELECTRONICCODEBOOKTASK_H

#include "MainTask/maintask.h"

class EncodeElectronicCodeBookTask : public MainTask
{
    Q_OBJECT
public:
    explicit EncodeElectronicCodeBookTask(QWidget *parent = nullptr);
     ~EncodeElectronicCodeBookTask();

public slots:
    void mainMethod();

private:
    // Sum QByteArray& and const QByteArray& mod 2^32 and result saves in QByteArray&
    void summatorCM1mod2pow32(QByteArray&, const QByteArray&);
    // All bytes in QByteArray& changes it's value with the const unsigned char[8][16] matrix and result saves in QByteArray&
    void kTransformBlock(QByteArray&, const unsigned char[8][16]);
    // Round rotate QByteArray& on 11 bits to elder bits and result saves in QByteArray&
    void rRotation11Block(QByteArray&);
    // Sum QByteArray& and const QByteArray& mod 2 and result saves in QByteArray&
    void summatorCM2mod2pow1(QByteArray&, const QByteArray&);

};

#endif // ENCODEELECTRONICCODEBOOKTASK_H
