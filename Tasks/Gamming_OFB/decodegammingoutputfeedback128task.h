#ifndef DECODEGAMMINGOUTPUTFEEDBACK128TASK_H
#define DECODEGAMMINGOUTPUTFEEDBACK128TASK_H

#include "MainTask/maintask.h"

class DecodeGammingOutputFeedback128Task : public MainTask
{
    Q_OBJECT
public:
    explicit DecodeGammingOutputFeedback128Task(QWidget *parent = nullptr);
     ~DecodeGammingOutputFeedback128Task();

public slots:
    void mainMethod();
};

#endif // DECODEGAMMINGOUTPUTFEEDBACK128TASK_H
