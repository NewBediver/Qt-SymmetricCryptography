#ifndef DECODEGAMMINGCIPHERFEEDBACK128TASK_H
#define DECODEGAMMINGCIPHERFEEDBACK128TASK_H

#include "MainTask/maintask.h"

class DecodeGammingCipherFeedback128Task : public MainTask
{
    Q_OBJECT
public:
    explicit DecodeGammingCipherFeedback128Task(QWidget *parent = nullptr);
     ~DecodeGammingCipherFeedback128Task();

public slots:
    void mainMethod();
};

#endif // DECODEGAMMINGCIPHERFEEDBACK128TASK_H
