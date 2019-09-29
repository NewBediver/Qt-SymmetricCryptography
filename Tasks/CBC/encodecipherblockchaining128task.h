#ifndef ENCODECIPHERBLOCKCHAINING128TASK_H
#define ENCODECIPHERBLOCKCHAINING128TASK_H

#include "MainTask/maintask.h"

class EncodeCipherBlockChaining128Task : public MainTask
{
    Q_OBJECT
public:
    explicit EncodeCipherBlockChaining128Task(QWidget *parent = nullptr);
     ~EncodeCipherBlockChaining128Task();

public slots:
    void mainMethod();
};

#endif // ENCODECIPHERBLOCKCHAINING128TASK_H
