#ifndef MAINTASK_H
#define MAINTASK_H

#include <QWidget>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

class MainTask : public QWidget
{
    Q_OBJECT
public:
    explicit MainTask(QWidget *parent = nullptr);
     ~MainTask();

private:


    // Elements on form
    QTextEdit* taskTextEdit;
    QTextEdit* resultTextEdit;
    QLabel* taskLabel;
    QLabel* resultLabel;
    QPushButton* makeActionPushButton;
    QHBoxLayout* taskLayout;
    QVBoxLayout* mainLayout;

signals:

public slots:
    // Makes makeActionPushButton ba active only when taskTextEdit isn't empty
    void tryMakeActionPushButtonEnabled();

};

#endif // MAINTASK_H
