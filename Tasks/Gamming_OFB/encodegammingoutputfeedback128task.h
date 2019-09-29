#ifndef ENCODEGAMMINGOUTPUTFEEDBACK128TASK_H
#define ENCODEGAMMINGOUTPUTFEEDBACK128TASK_H

#include "MainTask/maintask.h"

class EncodeGammingOutputFeedback128Task : public MainTask
{
    Q_OBJECT
public:
    explicit EncodeGammingOutputFeedback128Task(QWidget *parent = nullptr);
     ~EncodeGammingOutputFeedback128Task();

public slots:
    void mainMethod();
};

#endif // ENCODEGAMMINGOUTPUTFEEDBACK128TASK_H
