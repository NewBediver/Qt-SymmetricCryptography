#ifndef DECODEGAMMINGOUTPUTFEEDBACKTASK_H
#define DECODEGAMMINGOUTPUTFEEDBACKTASK_H

#include "MainTask/maintask.h"

class DecodeGammingOutputFeedbackTask : public MainTask
{
    Q_OBJECT
public:
    explicit DecodeGammingOutputFeedbackTask(QWidget *parent = nullptr);
     ~DecodeGammingOutputFeedbackTask();
};

#endif // DECODEGAMMINGOUTPUTFEEDBACKTASK_H
