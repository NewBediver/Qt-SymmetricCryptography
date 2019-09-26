#ifndef ENCODEGAMMINGCIPHERFEEDBACKTASK_H
#define ENCODEGAMMINGCIPHERFEEDBACKTASK_H

#include "MainTask/maintask.h"

class EncodeGammingCipherFeedbackTask : public MainTask
{
    Q_OBJECT
public:
    explicit EncodeGammingCipherFeedbackTask(QWidget *parent = nullptr);
     ~EncodeGammingCipherFeedbackTask();

public slots:
    void mainMethod();
};

#endif // ENCODEGAMMINGCIPHERFEEDBACKTASK_H
