#ifndef DECODECIPHERBLOCKCHAINING128TASK_H
#define DECODECIPHERBLOCKCHAINING128TASK_H

#include "MainTask/maintask.h"

class DecodeCipherBlockChaining128Task : public MainTask
{
    Q_OBJECT
public:
    explicit DecodeCipherBlockChaining128Task(QWidget *parent = nullptr);
     ~DecodeCipherBlockChaining128Task();

public slots:
    void mainMethod();
};

#endif // DECODECIPHERBLOCKCHAINING128TASK_H
