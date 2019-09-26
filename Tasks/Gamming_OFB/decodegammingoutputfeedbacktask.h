#ifndef DECODEGAMMINGOUTPUTFEEDBACKTASK_H
#define DECODEGAMMINGOUTPUTFEEDBACKTASK_H

#include "MainTask/maintask.h"

class DecodeGammingOutputFeedbackTask : public MainTask
{
    Q_OBJECT
public:
    explicit DecodeGammingOutputFeedbackTask(QWidget *parent = nullptr);
     ~DecodeGammingOutputFeedbackTask();

public slots:
    void mainMethod();
};

#endif // DECODEGAMMINGOUTPUTFEEDBACKTASK_H
