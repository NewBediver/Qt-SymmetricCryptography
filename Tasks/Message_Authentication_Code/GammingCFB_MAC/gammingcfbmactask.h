#ifndef GAMMINGCFBMACTASK_H
#define GAMMINGCFBMACTASK_H

#include "MainTask/maintask.h"

class GammingCFBMACTask : public MainTask
{
    Q_OBJECT
public:
    explicit GammingCFBMACTask(QWidget *parent = nullptr);
     ~GammingCFBMACTask();

public slots:
    void mainMethod();
};

#endif // GAMMINGCFBMACTASK_H
