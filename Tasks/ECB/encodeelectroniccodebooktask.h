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
};

#endif // ENCODEELECTRONICCODEBOOKTASK_H
