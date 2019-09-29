#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "MainTask/maintask.h"

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
    MainWindow(QWidget *parent = nullptr);
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

    //===============Task=============//
    QWidget* centralWidget;           //
    //================================//

    //===============Status bar=============//
    QStatusBar* statusBar;                  //
    //======================================//

    //====================Menu bar==================//
    QMenuBar* menuBar;                              //
    // GOST 28147-89(magma) menu                    //
    QMenu* magmaMenu;                               //
    // GOST 34.12-2018(kuznechik) menu              //
    QMenu* kuznechikMenu;                           //
                                                    //
    // GOST 28147-89(magma) menu                    //
    QMenu* electronicCodeBookMenu;      //(Electronic CodeBook, ECB) - simple replacement
    QMenu* gammingMenu;                             //
    QMenu* gammingOutputFeedbackMenu;   //(Output FeedBack, OFB)
    QMenu* cipherBlockChainingMenu;     //(Cipher Block Chaining, CBC)
    QMenu* gammingCipherFeedbackMenu;   //(Cipher Feedback, CFB)
    QMenu* messageAuthenticationCodeMenu;           //
                                                    //
    // GOST 34.12-2018(kuznechik) menu              //
    QMenu* electronicCodeBook128Menu;      //(Electronic CodeBook, ECB) - simple replacement
    QMenu* gamming128Menu;                          //
    QMenu* gammingOutputFeedback128Menu;   //(Output FeedBack, OFB)
    QMenu* cipherBlockChaining128Menu;     //(Cipher Block Chaining, CBC)
    QMenu* gammingCipherFeedback128Menu;   //(Cipher Feedback, CFB)
    QMenu* messageAuthenticationCode128Menu;        //
                                                    //
                                                    //
    // Encode/Decode actions (magma)                //
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
    QAction* messageAuthenticationCodeECBAction;    //
    QAction* messageAuthenticationCodeCBCAction;    //
    QAction* messageAuthenticationCodeGammingAction;//
    QAction* messageAuthenticationCodeGammingOFBAction;//
    QAction* messageAuthenticationCodeGammingCFBAction;//
                                                    //
    // Encode/Decode actions (kuznechik)            //
    QAction* encodeElectronicCodeBook128Action;     //
    QAction* decodeElectronicCodeBook128Action;     //
    QAction* encodeGamming128Action;                //
    QAction* decodeGamming128Action;                //
    QAction* encodeGammingOutputFeedback128Action;  //
    QAction* decodeGammingOutputFeedback128Action;  //
    QAction* encodeCipherBlockChaining128Action;    //
    QAction* decodeCipherBlockChaining128Action;    //
    QAction* encodeGammingCipherFeedback128Action;  //
    QAction* decodeGammingCipherFeedback128Action;  //
    QAction* messageAuthenticationCodeECB128Action; //
    QAction* messageAuthenticationCodeCBC128Action; //
    QAction* messageAuthenticationCodeGamming128Action;//
    QAction* messageAuthenticationCodeGammingOFB128Action;//
    QAction* messageAuthenticationCodeGammingCFB128Action;//
                                                    //
    // Credits action                               //
    QAction* aboutAction;                           //
    //==============================================//

private slots:
    //====================Task slots==================//
    void createEncodeElectronicCodeBookTask();        //
    void createDecodeElectronicCodeBookTask();        //
    void createEncodeGammingTask();                   //
    void createDecodeGammingTask();                   //
    void createEncodeGammingOutputFeedbackTask();     //
    void createDecodeGammingOutputFeedbackTask();     //
    void createEncodeCipherBlockChainingTask();       //
    void createDecodeCipherBlockChainingTask();       //
    void createEncodeGammingCipherFeedbackTask();     //
    void createDecodeGammingCipherFeedbackTask();     //    
    void createECBMACTask();                          //
    void createCBCMACTask();                          //
    void createGammingMACTask();                      //
    void createGammingOFBMACTask();                   //
    void createGammingCFBMACTask();                   //

    void createEncodeElectronicCodeBook128Task();     //
    void createDecodeElectronicCodeBook128Task();     //
    void createEncodeGamming128Task();                //
    void createDecodeGamming128Task();                //
    void createEncodeGammingOutputFeedback128Task();  //
    void createDecodeGammingOutputFeedback128Task();  //
    void createEncodeCipherBlockChaining128Task();    //
    void createDecodeCipherBlockChaining128Task();    //
    void createEncodeGammingCipherFeedback128Task();  //
    void createDecodeGammingCipherFeedback128Task();  //
    void createECBMAC128Task();                       //
    void createCBCMAC128Task();                       //
    void createGammingMAC128Task();                   //
    void createGammingOFBMAC128Task();                //
    void createGammingCFBMAC128Task();                //

    void createAboutWindow();                         //
    //================================================//

};

#endif // MAINWINDOW_H
