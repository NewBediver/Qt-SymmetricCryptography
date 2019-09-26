#ifndef ENCODEGAMMINGTASK_H
#define ENCODEGAMMINGTASK_H

#include "MainTask/maintask.h"

class EncodeGammingTask : public MainTask
{
    Q_OBJECT
public:
    explicit EncodeGammingTask(QWidget *parent = nullptr);
     ~EncodeGammingTask();

public slots:
    void mainMethod();
};

#endif // ENCODEGAMMINGTASK_H
