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
};

#endif // DECODEELECTRONICCODEBOOKTASK_H
