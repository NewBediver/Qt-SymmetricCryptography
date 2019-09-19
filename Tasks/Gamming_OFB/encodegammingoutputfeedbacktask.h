#ifndef ENCODEGAMMINGOUTPUTFEEDBACKTASK_H
#define ENCODEGAMMINGOUTPUTFEEDBACKTASK_H

#include "MainTask/maintask.h"

class EncodeGammingOutputFeedbackTask : public MainTask
{
    Q_OBJECT
public:
    explicit EncodeGammingOutputFeedbackTask(QWidget *parent = nullptr);
     ~EncodeGammingOutputFeedbackTask();
};

#endif // ENCODEGAMMINGOUTPUTFEEDBACKTASK_H
