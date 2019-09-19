#ifndef ENCODEGAMMINGCIPHERFEEDBACKTASK_H
#define ENCODEGAMMINGCIPHERFEEDBACKTASK_H

#include "MainTask/maintask.h"

class EncodeGammingCipherFeedbackTask : public MainTask
{
    Q_OBJECT
public:
    explicit EncodeGammingCipherFeedbackTask(QWidget *parent = nullptr);
     ~EncodeGammingCipherFeedbackTask();
};

#endif // ENCODEGAMMINGCIPHERFEEDBACKTASK_H
