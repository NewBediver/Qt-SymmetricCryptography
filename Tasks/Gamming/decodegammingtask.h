#ifndef DECODEGAMMINGTASK_H
#define DECODEGAMMINGTASK_H

#include "MainTask/maintask.h"

class DecodeGammingTask : public MainTask
{
    Q_OBJECT
public:
    explicit DecodeGammingTask(QWidget *parent = nullptr);
     ~DecodeGammingTask();

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
    // Sum QBitArray& and const QBitArray& mod 2^32-1 and result returns in QBitArray
    QBitArray summatorCM4mod2pow32minus1(const QBitArray&, const QBitArray&);
    // Sum QBitArray& and const QBitArray& mod 2^32 and result returns in QBitArray
    QBitArray summatorCM3mod2pow32(const QBitArray&, const QBitArray&);
    // Sum QBitArray&+QBitArray& and const QBitArray&+QBitArray& mod 2^32 and result returns in QBitArray
    QBitArray summatorCM5mod2(const QBitArray&, const QBitArray&, const QBitArray&, const QBitArray&);

    // Get SynchroBlock from QByteArray and result returns in QBitArray
    QBitArray getInitializingVector(const QByteArray&);

};

#endif // DECODEGAMMINGTASK_H
