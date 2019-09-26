#ifndef CBCMACTASK_H
#define CBCMACTASK_H

#include "MainTask/maintask.h"

class CBCMACTask : public MainTask
{
    Q_OBJECT
public:
    explicit CBCMACTask(QWidget *parent = nullptr);
     ~CBCMACTask();

public slots:
    void mainMethod();
};

#endif // CBCMACTASK_H
