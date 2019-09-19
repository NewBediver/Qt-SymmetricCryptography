#ifndef ENCODEIMITATIONINSERTTASK_H
#define ENCODEIMITATIONINSERTTASK_H

#include "MainTask/maintask.h"

class EncodeImitationInsertTask : public MainTask
{
    Q_OBJECT
public:
    explicit EncodeImitationInsertTask(QWidget *parent = nullptr);
     ~EncodeImitationInsertTask();
};

#endif // ENCODEIMITATIONINSERTTASK_H
