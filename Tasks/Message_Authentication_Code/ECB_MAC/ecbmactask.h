#ifndef ECBMACTASK_H
#define ECBMACTASK_H

#include "MainTask/maintask.h"

class ECBMACTask : public MainTask
{
    Q_OBJECT
public:
    explicit ECBMACTask(QWidget *parent = nullptr);
     ~ECBMACTask();

public slots:
    void mainMethod();
};

#endif // ECBMACTASK_H
