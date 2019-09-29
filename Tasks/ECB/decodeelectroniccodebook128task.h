#ifndef DECODEELECTRONICCODEBOOK128TASK_H
#define DECODEELECTRONICCODEBOOK128TASK_H

#include "MainTask/maintask.h"

class DecodeElectronicCodeBook128Task : public MainTask
{
    Q_OBJECT
public:
    explicit DecodeElectronicCodeBook128Task(QWidget *parent = nullptr);
     ~DecodeElectronicCodeBook128Task();

public slots:
    void mainMethod();
};

#endif // DECODEELECTRONICCODEBOOK128TASK_H
