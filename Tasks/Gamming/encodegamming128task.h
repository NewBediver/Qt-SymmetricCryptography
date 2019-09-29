#ifndef ENCODEGAMMING128TASK_H
#define ENCODEGAMMING128TASK_H

#include "MainTask/maintask.h"

class EncodeGamming128Task : public MainTask
{
    Q_OBJECT
public:
    explicit EncodeGamming128Task(QWidget *parent = nullptr);
     ~EncodeGamming128Task();

public slots:
    void mainMethod();
};

#endif // ENCODEGAMMING128TASK_H
