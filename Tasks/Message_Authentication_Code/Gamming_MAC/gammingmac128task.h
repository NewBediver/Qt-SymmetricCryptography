#ifndef GAMMINGMAC128TASK_H
#define GAMMINGMAC128TASK_H

#include "MainTask/maintask.h"

class GammingMAC128Task : public MainTask
{
    Q_OBJECT
public:
    explicit GammingMAC128Task(QWidget *parent = nullptr);
     ~GammingMAC128Task();

public slots:
    void mainMethod();
};

#endif // GAMMINGMAC128TASK_H
