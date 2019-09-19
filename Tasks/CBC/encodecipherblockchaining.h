#ifndef ENCODECIPHERBLOCKCHAINING_H
#define ENCODECIPHERBLOCKCHAINING_H

#include "MainTask/maintask.h"

class EncodeCipherBlockChaining : public MainTask
{
    Q_OBJECT
public:
    explicit EncodeCipherBlockChaining(QWidget *parent = nullptr);
     ~EncodeCipherBlockChaining();
};

#endif // ENCODECIPHERBLOCKCHAINING_H
