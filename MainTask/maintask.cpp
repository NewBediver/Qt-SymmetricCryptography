#include "maintask.h"

MainTask::MainTask(QWidget *parent) : QWidget(parent)
{
    //Create task edit field
    taskTextEdit = new QTextEdit();

    //Create task label
    taskLabel = new QLabel();
    changeTaskLabelText("Encoded text:");

    //Set taskLabel buddy
    taskLabel->setBuddy(taskTextEdit);

    //Create task button
    makeActionPushButton = new QPushButton();
    makeActionPushButton->setEnabled(false);
    changeMakeActionPushButtonText("Do something");
    connect(taskTextEdit, SIGNAL(textChanged()), this, SLOT(tryMakeActionPushButtonEnabled()));    

    //Create output text edit and make it ReadOnly
    resultTextEdit = new QTextEdit();
    resultTextEdit->setReadOnly(true);

    //Create result label
    resultLabel = new QLabel();
    changeResultLabelText("Result text:");

    //Set resultLabel buddy
    resultLabel->setBuddy(resultTextEdit);

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

void MainTask::changeTaskLabelText(QString newText)
{
    taskLabel->setText(newText);
    taskTextEdit->setStatusTip(taskLabel->text().mid(0, taskLabel->text().length()-1));
}

void MainTask::changeResultLabelText(QString newText)
{
    resultLabel->setText(newText);
    resultTextEdit->setStatusTip(resultLabel->text().mid(0, resultLabel->text().length()-1));
}

void MainTask::changeMakeActionPushButtonText(QString newText)
{
    makeActionPushButton->setText(newText);
    makeActionPushButton->setStatusTip("Let's " + makeActionPushButton->text());
}

MainTask::~MainTask()
{
    delete taskTextEdit;
    delete resultTextEdit;
    delete taskLabel;
    delete resultLabel;
    delete makeActionPushButton;
    delete taskLayout;
    delete mainLayout;
}
