#ifndef ECBMAC128TASK_H
#define ECBMAC128TASK_H

#include "MainTask/maintask.h"

class ECBMAC128Task : public MainTask
{
    Q_OBJECT
public:
    explicit ECBMAC128Task(QWidget *parent = nullptr);
     ~ECBMAC128Task();

public slots:
    void mainMethod();
};

#endif // ECBMAC128TASK_H
