#ifndef DECODEGAMMINGCIPHERFEEDBACKTASK_H
#define DECODEGAMMINGCIPHERFEEDBACKTASK_H

#include "MainTask/maintask.h"

class DecodeGammingCipherFeedbackTask : public MainTask
{
    Q_OBJECT
public:
    explicit DecodeGammingCipherFeedbackTask(QWidget *parent = nullptr);
     ~DecodeGammingCipherFeedbackTask();
};


#endif // DECODEGAMMINGCIPHERFEEDBACKTASK_H
