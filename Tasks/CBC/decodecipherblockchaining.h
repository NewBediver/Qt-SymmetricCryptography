#ifndef DECODECIPHERBLOCKCHAINING_H
#define DECODECIPHERBLOCKCHAINING_H

#include "MainTask/maintask.h"

class DecodeCipherBlockChaining : public MainTask
{
    Q_OBJECT
public:
    explicit DecodeCipherBlockChaining(QWidget *parent = nullptr);
     ~DecodeCipherBlockChaining();
};

#endif // DeCODECIPHERBLOCKCHAINING_H
