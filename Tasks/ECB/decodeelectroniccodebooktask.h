#ifndef DECODEELECTRONICCODEBOOKTASK_H
#define DECODEELECTRONICCODEBOOKTASK_H

#include "MainTask/maintask.h"

class DecodeElectronicCodeBookTask : public MainTask
{
    Q_OBJECT
public:
    explicit DecodeElectronicCodeBookTask(QWidget *parent = nullptr);
     ~DecodeElectronicCodeBookTask();

public slots:
    void mainMethod();

private:
    // Sum QBitArray& and const QBitArray& mod 2^32 and result returns in QBitArray
    QBitArray summatorCM1mod2pow32(const QBitArray&, const QBitArray&);
    // All bits in QBitArray& changes it's value with the const unsigned char[8][16] matrix and result returns in QBitArray
    QBitArray kTransformBlock(const QBitArray&, const unsigned char[8][16]);
    // Round rotate QBitArray& on 11 bits to elder bits and result returns in QBitArray
    QBitArray rRotation11Block(const QBitArray&);
    // Sum QBitArray& and const QBitArray& mod 2 and result returns in QBitArray
    QBitArray summatorCM2mod2pow1(const QBitArray&, const QBitArray&);
};

#endif // DECODEELECTRONICCODEBOOKTASK_H
