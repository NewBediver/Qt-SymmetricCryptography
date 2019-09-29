#ifndef GAMMINGCFBMAC128TASK_H
#define GAMMINGCFBMAC128TASK_H

#include "MainTask/maintask.h"

class GammingCFBMAC128Task : public MainTask
{
    Q_OBJECT
public:
    explicit GammingCFBMAC128Task(QWidget *parent = nullptr);
     ~GammingCFBMAC128Task();

public slots:
    void mainMethod();
};

#endif // GAMMINGCFBMAC128TASK_H
