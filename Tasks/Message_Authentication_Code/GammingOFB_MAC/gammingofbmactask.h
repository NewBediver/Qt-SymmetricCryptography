#ifndef GAMMINGOFBMACTASK_H
#define GAMMINGOFBMACTASK_H

#include "MainTask/maintask.h"

class GammingOFBMACTask : public MainTask
{
    Q_OBJECT
public:
    explicit GammingOFBMACTask(QWidget *parent = nullptr);
     ~GammingOFBMACTask();

public slots:
    void mainMethod();
};

#endif // GAMMINGOFBMACTASK_H
