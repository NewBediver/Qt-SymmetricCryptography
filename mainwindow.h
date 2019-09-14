#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QStatusBar>
#include <QString>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    void createMenuBar();
    void createStatusBar();

    //====================Methods which create menues and actions====================//
    template <class Creature>                                                        //
    Creature* createMenuElement(QString name, QString statusTip, QString iconPath);  //
    template <class Creature>                                                        //
    Creature* createMenuElement(QString name, QString statusTip);                    //
    template <class Creature>                                                        //
    Creature* createMenuElement(QString name);                                       //
    //===============================================================================//

    //===============Status bar=============//
    QStatusBar* statusBar;                  //
    //======================================//

    //====================Menu bar==================//
    QMenuBar* menuBar;                              //
    // GOST 28147-89(magma) menu                    //
    QMenu* magmaMenu;                               //
    // GOST 28147-89(magma) menu                    //
    QMenu* electronicCodeBookMenu;      //(Electronic CodeBook, ECB) - simple replacement
    QMenu* gammingMenu;                             //
    QMenu* gammingOutputFeedbackMenu;   //(Output FeedBack, OFB)
    QMenu* cipherBlockChainingMenu;     //(Cipher Block Chaining, CBC)
    QMenu* gammingCipherFeedbackMenu;   //(Cipher Feedback, CFB)
    QMenu* imitationInsertMenu;                     //
                                                    //
    // Encode/Decode actions                        //
    QAction* encodeElectronicCodeBookAction;        //
    QAction* decodeElectronicCodeBookAction;        //
    QAction* encodeGammingAction;                   //
    QAction* decodeGammingAction;                   //
    QAction* encodeGammingOutputFeedbackAction;     //
    QAction* decodeGammingOutputFeedbackAction;     //
    QAction* encodeCipherBlockChainingAction;       //
    QAction* decodeCipherBlockChainingAction;       //
    QAction* encodeGammingCipherFeedbackAction;     //
    QAction* decodeGammingCipherFeedbackAction;     //
    QAction* encodeImitationInsertAction;           //
    QAction* decodeImitationInsertAction;           //
    //==============================================//

};

#endif // MAINWINDOW_H
