#ifndef GAMMINMACTASK_H
#define GAMMINMACTASK_H

#include "MainTask/maintask.h"

class GammingMACTask : public MainTask
{
    Q_OBJECT
public:
    explicit GammingMACTask(QWidget *parent = nullptr);
     ~GammingMACTask();

public slots:
    void mainMethod();
};

#endif // GAMMINMACTASK_H
