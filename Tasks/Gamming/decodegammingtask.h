#ifndef DECODEGAMMINGTASK_H
#define DECODEGAMMINGTASK_H

#include "MainTask/maintask.h"

class DecodeGammingTask : public MainTask
{
    Q_OBJECT
public:
    explicit DecodeGammingTask(QWidget *parent = nullptr);
     ~DecodeGammingTask();

public slots:
    void mainMethod();
};

#endif // DECODEGAMMINGTASK_H
