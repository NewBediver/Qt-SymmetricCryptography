#include "maintask.h"

#include <QRegExpValidator>

MainTask::MainTask(QWidget *parent) : QWidget(parent)
{
    //Create task edit field
    taskTextEdit = new QTextEdit();
    connect(taskTextEdit, SIGNAL(textChanged()), this, SLOT(checkTaskTextEdit()));

    //Create task label
    taskLabel = new QLabel();
    changeTaskLabelText("Encoded text:");

    //Set taskLabel buddy
    taskLabel->setBuddy(taskTextEdit);

    //Create key label
    keyLabel = new QLabel();
    keyLabel->setText("Key:");

    //Create key edit field
    keyLineEdit = new QLineEdit();
    keyLineEdit->setToolTip("Enter key");
    keyLineEdit->setValidator(new QRegExpValidator(QRegExp("[A-Fa-f0-9]{0,64}")));

    //Set keyLabel buddy
    keyLabel->setBuddy(keyLineEdit);

    //Create task button
    makeActionPushButton = new QPushButton();
    makeActionPushButton->setEnabled(false);
    makeActionPushButton->setDefault(true);
    changeMakeActionPushButtonText("Do something");
    connect(taskTextEdit, SIGNAL(textChanged()), this, SLOT(tryMakeActionPushButtonEnabled()));
    connect(keyLineEdit, SIGNAL(textChanged(QString)), this, SLOT(tryMakeActionPushButtonEnabled()));

    //Create output text edit and make it ReadOnly
    resultTextEdit = new QTextEdit();
    resultTextEdit->setReadOnly(true);

    //Create result label
    resultLabel = new QLabel();
    changeResultLabelText("Result text:");

    //Set resultLabel buddy
    resultLabel->setBuddy(resultTextEdit);

    //Add key elements to form layout
    keyFormLayout = new QFormLayout();
    keyFormLayout->addRow(keyLabel, keyLineEdit);

    //Add task widgets to taskLayout
    taskLayout = new QHBoxLayout();
    taskLayout->addWidget(taskTextEdit);
    taskLayout->addWidget(makeActionPushButton);

    //Add everything to mainLayout
    mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(keyFormLayout);
    mainLayout->addWidget(taskLabel);
    mainLayout->addLayout(taskLayout);
    mainLayout->addWidget(resultLabel);
    mainLayout->addWidget(resultTextEdit);

    connect(makeActionPushButton, SIGNAL(clicked()), this, SLOT(mainMethod()));
}

void MainTask::tryMakeActionPushButtonEnabled()
{
    if (taskTextEdit->toPlainText().isEmpty() || keyLineEdit->text().isEmpty()) {
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

void MainTask::checkTaskTextEdit()
{
    if (!checkValidTaskTextEdit(QRegExp("[A-Fa-f0-9]*"))) {
        taskTextEdit->setText(taskTextEdit->toPlainText().remove(QRegExp("[^A-Fa-f0-9]")));
        taskTextEdit->moveCursor(QTextCursor::End);
    }
}

bool MainTask::checkValidTaskTextEdit(QRegExp reg)
{
    return reg.exactMatch(taskTextEdit->toPlainText());
}

void MainTask::mainMethod() {}

MainTask::~MainTask()
{
    delete taskTextEdit;
    delete resultTextEdit;
    delete taskLabel;
    delete resultLabel;
    delete makeActionPushButton;
    delete taskLayout;    
    delete keyLabel;
    delete keyLineEdit;
    delete keyFormLayout;
    delete mainLayout;  
}
