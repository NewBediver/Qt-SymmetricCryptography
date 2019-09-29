#ifndef ENCODEELECTRONICCODEBOOK128TASK_H
#define ENCODEELECTRONICCODEBOOK128TASK_H

#include "MainTask/maintask.h"

class EncodeElectronicCodeBook128Task : public MainTask
{
    Q_OBJECT
public:
    explicit EncodeElectronicCodeBook128Task(QWidget *parent = nullptr);
     ~EncodeElectronicCodeBook128Task();

public slots:
    void mainMethod();
};

#endif // ENCODEELECTRONICCODEBOOK128TASK_H
