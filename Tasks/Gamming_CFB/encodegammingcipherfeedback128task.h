#ifndef ENCODEGAMMINGCIPHERFEEDBACK128TASK_H
#define ENCODEGAMMINGCIPHERFEEDBACK128TASK_H

#include "MainTask/maintask.h"

class EncodeGammingCipherFeedback128Task : public MainTask
{
    Q_OBJECT
public:
    explicit EncodeGammingCipherFeedback128Task(QWidget *parent = nullptr);
     ~EncodeGammingCipherFeedback128Task();

public slots:
    void mainMethod();
};

#endif // ENCODEGAMMINGCIPHERFEEDBACK128TASK_H
