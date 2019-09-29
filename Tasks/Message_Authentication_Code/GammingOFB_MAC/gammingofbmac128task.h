#ifndef GAMMINGOFBMAC128TASK_H
#define GAMMINGOFBMAC128TASK_H

#include "MainTask/maintask.h"

class GammingOFBMAC128Task : public MainTask
{
    Q_OBJECT
public:
    explicit GammingOFBMAC128Task(QWidget *parent = nullptr);
     ~GammingOFBMAC128Task();

public slots:
    void mainMethod();
};

#endif // GAMMINGOFBMAC128TASK_H
