#ifndef ENCODEELECTRONICCODEBOOKTASK_H
#define ENCODEELECTRONICCODEBOOKTASK_H

#include "MainTask/maintask.h"

class EncodeElectronicCodeBookTask : public MainTask
{
    Q_OBJECT
public:
    explicit EncodeElectronicCodeBookTask(QWidget *parent = nullptr);
     ~EncodeElectronicCodeBookTask();
};

#endif // ENCODEELECTRONICCODEBOOKTASK_H
