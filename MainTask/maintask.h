#ifndef MAINTASK_H
#define MAINTASK_H

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>

class MainTask : public QWidget
{
    Q_OBJECT
public:
    explicit MainTask(QWidget *parent = nullptr);
     ~MainTask();

protected:
    // Change form elements text
    void changeTaskLabelText(QString);
    void changeResultLabelText(QString);
    void changeMakeActionPushButtonText(QString);

protected:
    // Elements on form
    QTextEdit* taskTextEdit;
    QTextEdit* resultTextEdit;
    QLabel* taskLabel;
    QLabel* resultLabel;
    QPushButton* makeActionPushButton;
    QHBoxLayout* taskLayout;
    QVBoxLayout* mainLayout;
    QLabel* keyLabel;
    QLineEdit* keyLineEdit;
    QFormLayout* keyFormLayout;

signals:

public slots:
    // Makes makeActionPushButton ba active only when taskTextEdit isn't empty
    void tryMakeActionPushButtonEnabled();
    void checkTaskTextEdit();
    bool checkValidTaskTextEdit(QRegExp);
    virtual void mainMethod();

};

#endif // MAINTASK_H
