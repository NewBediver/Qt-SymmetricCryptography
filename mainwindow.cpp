#include "mainwindow.h"
#include "MainTask/maintask.h"
#include "Tasks/ECB/encodeelectroniccodebooktask.h"
#include "Tasks/ECB/decodeelectroniccodebooktask.h"
#include "Tasks/Gamming/encodegammingtask.h"
#include "Tasks/Gamming/decodegammingtask.h"
#include "Tasks/Gamming_OFB/encodegammingoutputfeedbacktask.h"
#include "Tasks/Gamming_OFB/decodegammingoutputfeedbacktask.h"
#include "Tasks/CBC/encodecipherblockchaining.h"
#include "Tasks/CBC/decodecipherblockchaining.h"
#include "Tasks/Gamming_CFB/encodegammingcipherfeedbacktask.h"
#include "Tasks/Gamming_CFB/decodegammingcipherfeedbacktask.h"
#include "Tasks/Message_Authentication_Code/ECB_MAC/ecbmactask.h"
#include "Tasks/Message_Authentication_Code/CBC_MAC/cbcmactask.h"
#include "Tasks/Message_Authentication_Code/Gamming_MAC/gamminmactask.h"
#include "Tasks/Message_Authentication_Code/GammingOFB_MAC/gammingofbmactask.h"
#include "Tasks/Message_Authentication_Code/GammingCFB_MAC/gammingcfbmactask.h"
#include "AboutWindow/aboutwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    MainWindow::setWindowTitle(tr("Symmetric cryptography"));
    MainWindow::setWindowIcon(QIcon(":/res/appIcon.png"));
    MainWindow::resize(800, 600);
    centralWidget = nullptr;

    createStatusBar();
    createMenuBar();
    createAboutWindow();

    connect(encodeElectronicCodeBookAction, SIGNAL(triggered()), this, SLOT(createEncodeElectronicCodeBookTask()));
    connect(decodeElectronicCodeBookAction, SIGNAL(triggered()), this, SLOT(createDecodeElectronicCodeBookTask()));
    connect(encodeGammingAction, SIGNAL(triggered()), this, SLOT(createEncodeGammingTask()));
    connect(decodeGammingAction, SIGNAL(triggered()), this, SLOT(createDecodeGammingTask()));
    connect(encodeGammingOutputFeedbackAction, SIGNAL(triggered()), this, SLOT(createEncodeGammingOutputFeedbackTask()));
    connect(decodeGammingOutputFeedbackAction, SIGNAL(triggered()), this, SLOT(createDecodeGammingOutputFeedbackTask()));
    connect(encodeCipherBlockChainingAction, SIGNAL(triggered()), this, SLOT(createEncodeCipherBlockChainingTask()));
    connect(decodeCipherBlockChainingAction, SIGNAL(triggered()), this, SLOT(createDecodeCipherBlockChainingTask()));
    connect(encodeGammingCipherFeedbackAction, SIGNAL(triggered()), this, SLOT(createEncodeGammingCipherFeedbackTask()));
    connect(decodeGammingCipherFeedbackAction, SIGNAL(triggered()), this, SLOT(createDecodeGammingCipherFeedbackTask()));
    connect(messageAuthenticationCodeECBAction, SIGNAL(triggered()), this, SLOT(createECBMACTask()));
    connect(messageAuthenticationCodeCBCAction, SIGNAL(triggered()), this, SLOT(createCBCMACTask()));
    connect(messageAuthenticationCodeGammingAction, SIGNAL(triggered()), this, SLOT(createGammingMACTask()));
    connect(messageAuthenticationCodeGammingOFBAction, SIGNAL(triggered()), this, SLOT(createGammingOFBMACTask()));
    connect(messageAuthenticationCodeGammingCFBAction, SIGNAL(triggered()), this, SLOT(createGammingCFBMACTask()));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(createAboutWindow()));
}

void MainWindow::createMenuBar()
{
    //Create new menu bar
    menuBar = new QMenuBar();

    //Create GOST 28147-89 menu
    magmaMenu = createMenuElement<QMenu>("&GOST 28147-89 (magma)", "Use GOST 28147-89");

    //Create menues to GOST 28147-89
    electronicCodeBookMenu = createMenuElement<QMenu>("&ECB", "Use GOST 28147-89 in Electronic CodeBook mode.", ":/res/menuIcon.png");
    gammingMenu = createMenuElement<QMenu>("&Gamming", "Use GOST 28147-89 in gamming mode.", ":/res/menuIcon.png");
    gammingOutputFeedbackMenu = createMenuElement<QMenu>("&Gamming OFB", "Use GOST 28147-89 in gamming Output FeedBack mode.", ":/res/menuIcon.png");
    cipherBlockChainingMenu = createMenuElement<QMenu>("&CBC", "Use GOST 28147-89 in Cipher Block Chaining mode.", ":/res/menuIcon.png");
    gammingCipherFeedbackMenu = createMenuElement<QMenu>("&Gamming CFB", "Use GOST 28147-89 in gamming Cipher FeedBack mode.", ":/res/menuIcon.png");
    messageAuthenticationCodeMenu = createMenuElement<QMenu>("&Message Authentication Code", "Use GOST 28147-89 in Message Authentication Code mode.", ":/res/menuIcon.png");

    //Create actions to L2 menues
    encodeElectronicCodeBookAction = createMenuElement<QAction>("&Encode", "Use GOST 28147-89 in ECB mode to encode some information.", ":/res/encodeIcon.png");
    decodeElectronicCodeBookAction = createMenuElement<QAction>("&Decode", "Use GOST 28147-89 in ECB mode to decode some information.", ":/res/decodeIcon.png");
    encodeGammingAction = createMenuElement<QAction>("&Encode", "Use GOST 28147-89 in gamming mode to encode some information.", ":/res/encodeIcon.png");
    decodeGammingAction = createMenuElement<QAction>("&Decode", "Use GOST 28147-89 in gamming mode to decode some information.", ":/res/decodeIcon.png");
    encodeGammingOutputFeedbackAction = createMenuElement<QAction>("&Encode", "Use GOST 28147-89 in gamming OFB mode to encode some information.", ":/res/encodeIcon.png");
    decodeGammingOutputFeedbackAction = createMenuElement<QAction>("&Decode", "Use GOST 28147-89 in gamming OFB mode to decode some information.", ":/res/decodeIcon.png");
    encodeCipherBlockChainingAction = createMenuElement<QAction>("&Encode", "Use GOST 28147-89 in CBC mode to encode some information.", ":/res/encodeIcon.png");
    decodeCipherBlockChainingAction = createMenuElement<QAction>("&Decode", "Use GOST 28147-89 in CBC mode to decode some information.", ":/res/decodeIcon.png");
    encodeGammingCipherFeedbackAction = createMenuElement<QAction>("&Encode", "Use GOST 28147-89 in gamming CFB mode to encode some information.", ":/res/encodeIcon.png");
    decodeGammingCipherFeedbackAction = createMenuElement<QAction>("&Decode", "Use GOST 28147-89 in gamming CFB mode to decode some information.", ":/res/decodeIcon.png");
    messageAuthenticationCodeECBAction = createMenuElement<QAction>("&ECB-MAC", "Use GOST 28147-89 in ECB-MAC mode to encode some information.", ":/res/encodeIcon.png");
    messageAuthenticationCodeCBCAction = createMenuElement<QAction>("&CBC-MAC", "Use GOST 28147-89 in CBC-MAC mode to encode some information.", ":/res/encodeIcon.png");
    messageAuthenticationCodeGammingAction = createMenuElement<QAction>("&Gamming-MAC", "Use GOST 28147-89 in Gamming-MAC mode to encode some information.", ":/res/encodeIcon.png");
    messageAuthenticationCodeGammingOFBAction = createMenuElement<QAction>("&Gamming OFB-MAC", "Use GOST 28147-89 in Gamming OFB-MAC mode to encode some information.", ":/res/encodeIcon.png");
    messageAuthenticationCodeGammingCFBAction = createMenuElement<QAction>("&Gamming CFB-MAC", "Use GOST 28147-89 in Gamming CFB-MAC mode to encode some information.", ":/res/encodeIcon.png");

    //Create action for credits menu
    aboutAction = createMenuElement<QAction>("&About", "Show information about author.");

    //Add decode/encode actions to menues
    electronicCodeBookMenu->addAction(encodeElectronicCodeBookAction);
    electronicCodeBookMenu->addAction(decodeElectronicCodeBookAction);
    gammingMenu->addAction(encodeGammingAction);
    gammingMenu->addAction(decodeGammingAction);
    gammingOutputFeedbackMenu->addAction(encodeGammingOutputFeedbackAction);
    gammingOutputFeedbackMenu->addAction(decodeGammingOutputFeedbackAction);
    cipherBlockChainingMenu->addAction(encodeCipherBlockChainingAction);
    cipherBlockChainingMenu->addAction(decodeCipherBlockChainingAction);
    gammingCipherFeedbackMenu->addAction(encodeGammingCipherFeedbackAction);
    gammingCipherFeedbackMenu->addAction(decodeGammingCipherFeedbackAction);
    messageAuthenticationCodeMenu->addAction(messageAuthenticationCodeECBAction);
    messageAuthenticationCodeMenu->addAction(messageAuthenticationCodeCBCAction);
    messageAuthenticationCodeMenu->addAction(messageAuthenticationCodeGammingAction);
    messageAuthenticationCodeMenu->addAction(messageAuthenticationCodeGammingOFBAction);
    messageAuthenticationCodeMenu->addAction(messageAuthenticationCodeGammingCFBAction);

    //Add L2 menues to L1 menu
    magmaMenu->addMenu(electronicCodeBookMenu);    
    magmaMenu->addMenu(cipherBlockChainingMenu);
    magmaMenu->addSeparator();
    magmaMenu->addMenu(gammingMenu);
    magmaMenu->addMenu(gammingOutputFeedbackMenu);
    magmaMenu->addMenu(gammingCipherFeedbackMenu);
    magmaMenu->addSeparator();
    magmaMenu->addMenu(messageAuthenticationCodeMenu);

    //Add L1 menues to menu bar
    menuBar->addMenu(magmaMenu);
    menuBar->addAction(aboutAction);

    //Add menu bar to main widget
    this->setMenuBar(menuBar);
}

void MainWindow::createStatusBar()
{
    statusBar = new QStatusBar();
    this->setStatusBar(statusBar);
}

template <class Creature>
Creature* MainWindow::createMenuElement(QString name, QString statusTip, QString iconPath)
{
    Creature* element = new Creature(name);
    element->setIcon(QIcon(iconPath));
    element->setStatusTip(statusTip);
    return element;
}

template <class Creature>
Creature* MainWindow::createMenuElement(QString name, QString statusTip)
{
    Creature* element = new Creature(name);
    element->setStatusTip(statusTip);
    return element;
}

template <class Creature>
Creature* MainWindow::createMenuElement(QString name)
{
    Creature* element = new Creature(name);
    return element;
}

void MainWindow::createEncodeElectronicCodeBookTask()
{
    if (centralWidget != nullptr) {
        delete centralWidget;
    }
    centralWidget = new EncodeElectronicCodeBookTask(this);
    MainWindow::setCentralWidget(centralWidget);
}

void MainWindow::createDecodeElectronicCodeBookTask()
{
    if (centralWidget != nullptr) {
        delete centralWidget;
    }
    centralWidget = new DecodeElectronicCodeBookTask(this);
    MainWindow::setCentralWidget(centralWidget);
}

void MainWindow::createEncodeGammingTask()
{
    if (centralWidget != nullptr) {
        delete centralWidget;
    }
    centralWidget = new EncodeGammingTask(this);
    MainWindow::setCentralWidget(centralWidget);
}

void MainWindow::createDecodeGammingTask()
{
    if (centralWidget != nullptr) {
        delete centralWidget;
    }
    centralWidget = new DecodeGammingTask(this);
    MainWindow::setCentralWidget(centralWidget);
}

void MainWindow::createEncodeGammingOutputFeedbackTask()
{
    if (centralWidget != nullptr) {
        delete centralWidget;
    }
    centralWidget = new EncodeGammingOutputFeedbackTask(this);
    MainWindow::setCentralWidget(centralWidget);
}

void MainWindow::createDecodeGammingOutputFeedbackTask()
{
    if (centralWidget != nullptr) {
        delete centralWidget;
    }
    centralWidget = new DecodeGammingOutputFeedbackTask(this);
    MainWindow::setCentralWidget(centralWidget);
}

void MainWindow::createEncodeCipherBlockChainingTask()
{
    if (centralWidget != nullptr) {
        delete centralWidget;
    }
    centralWidget = new EncodeCipherBlockChaining(this);
    MainWindow::setCentralWidget(centralWidget);
}

void MainWindow::createDecodeCipherBlockChainingTask()
{
    if (centralWidget != nullptr) {
        delete centralWidget;
    }
    centralWidget = new DecodeCipherBlockChaining(this);
    MainWindow::setCentralWidget(centralWidget);
}

void MainWindow::createEncodeGammingCipherFeedbackTask()
{
    if (centralWidget != nullptr) {
        delete centralWidget;
    }
    centralWidget = new EncodeGammingCipherFeedbackTask(this);
    MainWindow::setCentralWidget(centralWidget);
}

void MainWindow::createDecodeGammingCipherFeedbackTask()
{
    if (centralWidget != nullptr) {
        delete centralWidget;
    }
    centralWidget = new DecodeGammingCipherFeedbackTask(this);
    MainWindow::setCentralWidget(centralWidget);
}

void MainWindow::createECBMACTask()
{
    if (centralWidget != nullptr) {
        delete centralWidget;
    }
    centralWidget = new ECBMACTask(this);
    MainWindow::setCentralWidget(centralWidget);
}

void MainWindow::createCBCMACTask()
{
    if (centralWidget != nullptr) {
        delete centralWidget;
    }
    centralWidget = new CBCMACTask(this);
    MainWindow::setCentralWidget(centralWidget);
}

void MainWindow::createGammingMACTask()
{
    if (centralWidget != nullptr) {
        delete centralWidget;
    }
    centralWidget = new GammingMACTask(this);
    MainWindow::setCentralWidget(centralWidget);
}

void MainWindow::createGammingOFBMACTask()
{
    if (centralWidget != nullptr) {
        delete centralWidget;
    }
    centralWidget = new GammingOFBMACTask(this);
    MainWindow::setCentralWidget(centralWidget);
}

void MainWindow::createGammingCFBMACTask()
{
    if (centralWidget != nullptr) {
        delete centralWidget;
    }
    centralWidget = new GammingCFBMACTask(this);
    MainWindow::setCentralWidget(centralWidget);
}

void MainWindow::createAboutWindow()
{
    if (centralWidget != nullptr) {
        delete centralWidget;
    }
    centralWidget = new AboutWindow(this);
    MainWindow::setCentralWidget(centralWidget);
}



MainWindow::~MainWindow()
{
    delete centralWidget;
    delete statusBar;
    delete menuBar;
    delete magmaMenu;
    delete electronicCodeBookMenu;
    delete gammingMenu;
    delete gammingOutputFeedbackMenu;
    delete cipherBlockChainingMenu;
    delete gammingCipherFeedbackMenu;
    delete messageAuthenticationCodeMenu;
    delete encodeElectronicCodeBookAction;
    delete decodeElectronicCodeBookAction;
    delete encodeGammingAction;
    delete decodeGammingAction;
    delete encodeGammingOutputFeedbackAction;
    delete decodeGammingOutputFeedbackAction;
    delete encodeCipherBlockChainingAction;
    delete decodeCipherBlockChainingAction;
    delete encodeGammingCipherFeedbackAction;
    delete decodeGammingCipherFeedbackAction;
    delete messageAuthenticationCodeECBAction;
    delete messageAuthenticationCodeCBCAction;
    delete messageAuthenticationCodeGammingAction;
    delete messageAuthenticationCodeGammingOFBAction;
    delete messageAuthenticationCodeGammingCFBAction;
    delete aboutAction;
}
