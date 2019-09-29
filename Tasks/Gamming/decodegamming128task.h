#ifndef DECODEGAMMING128TASK_H
#define DECODEGAMMING128TASK_H

#include "MainTask/maintask.h"

class DecodeGamming128Task : public MainTask
{
    Q_OBJECT
public:
    explicit DecodeGamming128Task(QWidget *parent = nullptr);
     ~DecodeGamming128Task();

public slots:
    void mainMethod();
};

#endif // DECODEGAMMING128TASK_H
