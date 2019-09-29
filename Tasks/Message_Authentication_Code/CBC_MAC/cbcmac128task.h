#ifndef CBCMAC128TASK_H
#define CBCMAC128TASK_H

#include "MainTask/maintask.h"

class CBCMAC128Task : public MainTask
{
    Q_OBJECT
public:
    explicit CBCMAC128Task(QWidget *parent = nullptr);
     ~CBCMAC128Task();

public slots:
    void mainMethod();
};

#endif // CBCMAC128TASK_H
