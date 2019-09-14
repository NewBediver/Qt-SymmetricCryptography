#include "maintask.h"

MainTask::MainTask(QWidget *parent) : QWidget(parent)
{
    //Create task labal
    taskLabel = new QLabel();
    taskLabel->setText("Encoded text:");

    //Create task edit field
    taskTextEdit = new QTextEdit();

    //Create task button
    makeActionPushButton = new QPushButton();
    makeActionPushButton->setText("Do something");
    makeActionPushButton->setEnabled(false);
    connect(taskTextEdit, SIGNAL(textChanged()), this, SLOT(tryMakeActionPushButtonEnabled()));

    //Create result label
    resultLabel = new QLabel();
    resultLabel->setText("Result text:");

    //Create output text edit and make it ReadOnly
    resultTextEdit = new QTextEdit();
    resultTextEdit->setReadOnly(true);

    //Add task widgets to taskLayout
    taskLayout = new QHBoxLayout();
    taskLayout->addWidget(taskTextEdit);
    taskLayout->addWidget(makeActionPushButton);

    //Add everything to mainLayout
    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(taskLabel);
    mainLayout->addLayout(taskLayout);
    mainLayout->addWidget(resultLabel);
    mainLayout->addWidget(resultTextEdit);
}

void MainTask::tryMakeActionPushButtonEnabled()
{
    if (taskTextEdit->toPlainText().isEmpty()) {
        makeActionPushButton->setEnabled(false);
    }
    else {
        makeActionPushButton->setEnabled(true);
    }
}

MainTask::~MainTask()
{

}
