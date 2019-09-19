#ifndef DECODEIMITATIONINSERTTASK_H
#define DECODEIMITATIONINSERTTASK_H

#include "MainTask/maintask.h"

class DecodeImitationInsertTask : public MainTask
{
    Q_OBJECT
public:
    explicit DecodeImitationInsertTask(QWidget *parent = nullptr);
     ~DecodeImitationInsertTask();
};

#endif // DECODEIMITATIONINSERTTASK_H
