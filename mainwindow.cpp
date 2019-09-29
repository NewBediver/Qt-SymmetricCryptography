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

#include "Tasks/ECB/encodeelectroniccodebook128task.h"
#include "Tasks/ECB/decodeelectroniccodebook128task.h"
#include "Tasks/Gamming/encodegamming128task.h"
#include "Tasks/Gamming/decodegamming128task.h"
#include "Tasks/Gamming_OFB/encodegammingoutputfeedback128task.h"
#include "Tasks/Gamming_OFB/decodegammingoutputfeedback128task.h"
#include "Tasks/CBC/encodecipherblockchaining128task.h"
#include "Tasks/CBC/decodecipherblockchaining128task.h"
#include "Tasks/Gamming_CFB/decodegammingcipherfeedback128task.h"
#include "Tasks/Gamming_CFB/encodegammingcipherfeedback128task.h"
#include "Tasks/Message_Authentication_Code/ECB_MAC/ecbmac128task.h"
#include "Tasks/Message_Authentication_Code/CBC_MAC/cbcmac128task.h"
#include "Tasks/Message_Authentication_Code/Gamming_MAC/gammingmac128task.h"
#include "Tasks/Message_Authentication_Code/GammingOFB_MAC/gammingofbmac128task.h"
#include "Tasks/Message_Authentication_Code/GammingCFB_MAC/gammingcfbmac128task.h"

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

    connect(encodeElectronicCodeBook128Action, SIGNAL(triggered()), this, SLOT(createEncodeElectronicCodeBook128Task()));
    connect(decodeElectronicCodeBook128Action, SIGNAL(triggered()), this, SLOT(createDecodeElectronicCodeBook128Task()));
    connect(encodeGamming128Action, SIGNAL(triggered()), this, SLOT(createEncodeGamming128Task()));
    connect(decodeGamming128Action, SIGNAL(triggered()), this, SLOT(createDecodeGamming128Task()));
    connect(encodeGammingOutputFeedback128Action, SIGNAL(triggered()), this, SLOT(createEncodeGammingOutputFeedback128Task()));
    connect(decodeGammingOutputFeedback128Action, SIGNAL(triggered()), this, SLOT(createDecodeGammingOutputFeedback128Task()));
    connect(encodeCipherBlockChaining128Action, SIGNAL(triggered()), this, SLOT(createEncodeCipherBlockChaining128Task()));
    connect(decodeCipherBlockChaining128Action, SIGNAL(triggered()), this, SLOT(createDecodeCipherBlockChaining128Task()));
    connect(encodeGammingCipherFeedback128Action, SIGNAL(triggered()), this, SLOT(createEncodeGammingCipherFeedback128Task()));
    connect(decodeGammingCipherFeedback128Action, SIGNAL(triggered()), this, SLOT(createDecodeGammingCipherFeedback128Task()));
    connect(messageAuthenticationCodeECB128Action, SIGNAL(triggered()), this, SLOT(createECBMAC128Task()));
    connect(messageAuthenticationCodeCBC128Action, SIGNAL(triggered()), this, SLOT(createCBCMAC128Task()));
    connect(messageAuthenticationCodeGamming128Action, SIGNAL(triggered()), this, SLOT(createGammingMAC128Task()));
    connect(messageAuthenticationCodeGammingOFB128Action, SIGNAL(triggered()), this, SLOT(createGammingOFBMAC128Task()));
    connect(messageAuthenticationCodeGammingCFB128Action, SIGNAL(triggered()), this, SLOT(createGammingCFBMAC128Task()));

    connect(aboutAction, SIGNAL(triggered()), this, SLOT(createAboutWindow()));
}

void MainWindow::createMenuBar()
{
    //Create new menu bar
    menuBar = new QMenuBar();

    //Create GOST 28147-89 menu
    magmaMenu = createMenuElement<QMenu>("&GOST 28147-89 (magma)", "Use GOST 28147-89");
    //Create GOST 34.12-2018
    kuznechikMenu = createMenuElement<QMenu>("&GOST 34.12-2018 (kuznechik)", "Use GOST 32.12-2018");

    //Create menues to GOST 28147-89
    electronicCodeBookMenu = createMenuElement<QMenu>("&ECB", "Use GOST 28147-89 in Electronic CodeBook mode.", ":/res/menuIcon.png");
    gammingMenu = createMenuElement<QMenu>("&Gamming", "Use GOST 28147-89 in gamming mode.", ":/res/menuIcon.png");
    gammingOutputFeedbackMenu = createMenuElement<QMenu>("&Gamming OFB", "Use GOST 28147-89 in gamming Output FeedBack mode.", ":/res/menuIcon.png");
    cipherBlockChainingMenu = createMenuElement<QMenu>("&CBC", "Use GOST 28147-89 in Cipher Block Chaining mode.", ":/res/menuIcon.png");
    gammingCipherFeedbackMenu = createMenuElement<QMenu>("&Gamming CFB", "Use GOST 28147-89 in gamming Cipher FeedBack mode.", ":/res/menuIcon.png");
    messageAuthenticationCodeMenu = createMenuElement<QMenu>("&Message Authentication Code", "Use GOST 28147-89 in Message Authentication Code mode.", ":/res/menuIcon.png");
    //Create menues to GOST 34.12-2018
    electronicCodeBook128Menu = createMenuElement<QMenu>("&ECB", "Use GOST 34.12-2018 in Electronic CodeBook mode.", ":/res/menuIcon.png");
    gamming128Menu = createMenuElement<QMenu>("&Gamming", "Use GOST 34.12-2018 in gamming mode.", ":/res/menuIcon.png");
    gammingOutputFeedback128Menu = createMenuElement<QMenu>("&Gamming OFB", "Use 34.12-2018 in gamming Output FeedBack mode.", ":/res/menuIcon.png");
    cipherBlockChaining128Menu = createMenuElement<QMenu>("&CBC", "Use GOST 34.12-2018 in Cipher Block Chaining mode.", ":/res/menuIcon.png");
    gammingCipherFeedback128Menu = createMenuElement<QMenu>("&Gamming CFB", "Use GOST 34.12-2018 in gamming Cipher FeedBack mode.", ":/res/menuIcon.png");
    messageAuthenticationCode128Menu = createMenuElement<QMenu>("&Message Authentication Code", "Use GOST 34.12-2018 in Message Authentication Code mode.", ":/res/menuIcon.png");

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
    //Create actions to L2 menues
    encodeElectronicCodeBook128Action = createMenuElement<QAction>("&Encode", "Use GOST 34.12-2018 in ECB mode to encode some information.", ":/res/encodeIcon.png");
    decodeElectronicCodeBook128Action = createMenuElement<QAction>("&Decode", "Use GOST 34.12-2018 in ECB mode to decode some information.", ":/res/decodeIcon.png");
    encodeGamming128Action = createMenuElement<QAction>("&Encode", "Use GOST 34.12-2018 in gamming mode to encode some information.", ":/res/encodeIcon.png");
    decodeGamming128Action = createMenuElement<QAction>("&Decode", "Use GOST 34.12-2018 in gamming mode to decode some information.", ":/res/decodeIcon.png");
    encodeGammingOutputFeedback128Action = createMenuElement<QAction>("&Encode", "Use GOST 34.12-2018 in gamming OFB mode to encode some information.", ":/res/encodeIcon.png");
    decodeGammingOutputFeedback128Action = createMenuElement<QAction>("&Decode", "Use GOST 34.12-2018 in gamming OFB mode to decode some information.", ":/res/decodeIcon.png");
    encodeCipherBlockChaining128Action = createMenuElement<QAction>("&Encode", "Use GOST 34.12-2018 in CBC mode to encode some information.", ":/res/encodeIcon.png");
    decodeCipherBlockChaining128Action = createMenuElement<QAction>("&Decode", "Use GOST 34.12-2018 in CBC mode to decode some information.", ":/res/decodeIcon.png");
    encodeGammingCipherFeedback128Action = createMenuElement<QAction>("&Encode", "Use GOST 34.12-2018 in gamming CFB mode to encode some information.", ":/res/encodeIcon.png");
    decodeGammingCipherFeedback128Action = createMenuElement<QAction>("&Decode", "Use GOST 34.12-2018 in gamming CFB mode to decode some information.", ":/res/decodeIcon.png");
    messageAuthenticationCodeECB128Action = createMenuElement<QAction>("&ECB-MAC", "Use GOST 34.12-2018 in ECB-MAC mode to encode some information.", ":/res/encodeIcon.png");
    messageAuthenticationCodeCBC128Action = createMenuElement<QAction>("&CBC-MAC", "Use GOST 34.12-2018 in CBC-MAC mode to encode some information.", ":/res/encodeIcon.png");
    messageAuthenticationCodeGamming128Action = createMenuElement<QAction>("&Gamming-MAC", "Use GOST 34.12-2018 in Gamming-MAC mode to encode some information.", ":/res/encodeIcon.png");
    messageAuthenticationCodeGammingOFB128Action = createMenuElement<QAction>("&Gamming OFB-MAC", "Use GOST 34.12-2018 in Gamming OFB-MAC mode to encode some information.", ":/res/encodeIcon.png");
    messageAuthenticationCodeGammingCFB128Action = createMenuElement<QAction>("&Gamming CFB-MAC", "Use GOST 34.12-2018 in Gamming CFB-MAC mode to encode some information.", ":/res/encodeIcon.png");

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
    //Add decode/encode actions to menues
    electronicCodeBook128Menu->addAction(encodeElectronicCodeBook128Action);
    electronicCodeBook128Menu->addAction(decodeElectronicCodeBook128Action);
    gamming128Menu->addAction(encodeGamming128Action);
    gamming128Menu->addAction(decodeGamming128Action);
    gammingOutputFeedback128Menu->addAction(encodeGammingOutputFeedback128Action);
    gammingOutputFeedback128Menu->addAction(decodeGammingOutputFeedback128Action);
    cipherBlockChaining128Menu->addAction(encodeCipherBlockChaining128Action);
    cipherBlockChaining128Menu->addAction(decodeCipherBlockChaining128Action);
    gammingCipherFeedback128Menu->addAction(encodeGammingCipherFeedback128Action);
    gammingCipherFeedback128Menu->addAction(decodeGammingCipherFeedback128Action);
    messageAuthenticationCode128Menu->addAction(messageAuthenticationCodeECB128Action);
    messageAuthenticationCode128Menu->addAction(messageAuthenticationCodeCBC128Action);
    messageAuthenticationCode128Menu->addAction(messageAuthenticationCodeGamming128Action);
    messageAuthenticationCode128Menu->addAction(messageAuthenticationCodeGammingOFB128Action);
    messageAuthenticationCode128Menu->addAction(messageAuthenticationCodeGammingCFB128Action);

    //Add L2 menues to L1 menu
    magmaMenu->addMenu(electronicCodeBookMenu);    
    magmaMenu->addMenu(cipherBlockChainingMenu);
    magmaMenu->addSeparator();
    magmaMenu->addMenu(gammingMenu);
    magmaMenu->addMenu(gammingOutputFeedbackMenu);
    magmaMenu->addMenu(gammingCipherFeedbackMenu);
    magmaMenu->addSeparator();
    magmaMenu->addMenu(messageAuthenticationCodeMenu);
    //Add L2 menues to L1 menu
    kuznechikMenu->addMenu(electronicCodeBook128Menu);
    kuznechikMenu->addMenu(cipherBlockChaining128Menu);
    kuznechikMenu->addSeparator();
    kuznechikMenu->addMenu(gamming128Menu);
    kuznechikMenu->addMenu(gammingOutputFeedback128Menu);
    kuznechikMenu->addMenu(gammingCipherFeedback128Menu);
    kuznechikMenu->addSeparator();
    kuznechikMenu->addMenu(messageAuthenticationCode128Menu);

    //Add L1 menues to menu bar
    menuBar->addMenu(magmaMenu);
    menuBar->addMenu(kuznechikMenu);
    menuBar->addSeparator();
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

// MAGMA BLOCK
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

// KUZNECHIK BLOCK
void MainWindow::createEncodeElectronicCodeBook128Task()
{
    if (centralWidget != nullptr) {
        delete centralWidget;
    }
    centralWidget = new EncodeElectronicCodeBook128Task(this);
    MainWindow::setCentralWidget(centralWidget);
}

void MainWindow::createDecodeElectronicCodeBook128Task()
{
    if (centralWidget != nullptr) {
        delete centralWidget;
    }
    centralWidget = new DecodeElectronicCodeBook128Task(this);
    MainWindow::setCentralWidget(centralWidget);
}

void MainWindow::createEncodeGamming128Task()
{
    if (centralWidget != nullptr) {
        delete centralWidget;
    }
    centralWidget = new EncodeGamming128Task(this);
    MainWindow::setCentralWidget(centralWidget);
}

void MainWindow::createDecodeGamming128Task()
{
    if (centralWidget != nullptr) {
        delete centralWidget;
    }
    centralWidget = new DecodeGamming128Task(this);
    MainWindow::setCentralWidget(centralWidget);
}

void MainWindow::createEncodeGammingOutputFeedback128Task()
{
    if (centralWidget != nullptr) {
        delete centralWidget;
    }
    centralWidget = new EncodeGammingOutputFeedback128Task(this);
    MainWindow::setCentralWidget(centralWidget);
}

void MainWindow::createDecodeGammingOutputFeedback128Task()
{
    if (centralWidget != nullptr) {
        delete centralWidget;
    }
    centralWidget = new DecodeGammingOutputFeedback128Task(this);
    MainWindow::setCentralWidget(centralWidget);
}

void MainWindow::createEncodeCipherBlockChaining128Task()
{
    if (centralWidget != nullptr) {
        delete centralWidget;
    }
    centralWidget = new EncodeCipherBlockChaining128Task(this);
    MainWindow::setCentralWidget(centralWidget);
}

void MainWindow::createDecodeCipherBlockChaining128Task()
{
    if (centralWidget != nullptr) {
        delete centralWidget;
    }
    centralWidget = new DecodeCipherBlockChaining128Task(this);
    MainWindow::setCentralWidget(centralWidget);
}

void MainWindow::createEncodeGammingCipherFeedback128Task()
{
    if (centralWidget != nullptr) {
        delete centralWidget;
    }
    centralWidget = new EncodeGammingCipherFeedback128Task(this);
    MainWindow::setCentralWidget(centralWidget);
}

void MainWindow::createDecodeGammingCipherFeedback128Task()
{
    if (centralWidget != nullptr) {
        delete centralWidget;
    }
    centralWidget = new DecodeGammingCipherFeedback128Task(this);
    MainWindow::setCentralWidget(centralWidget);
}

void MainWindow::createECBMAC128Task()
{
    if (centralWidget != nullptr) {
        delete centralWidget;
    }
    centralWidget = new ECBMAC128Task(this);
    MainWindow::setCentralWidget(centralWidget);
}

void MainWindow::createCBCMAC128Task()
{
    if (centralWidget != nullptr) {
        delete centralWidget;
    }
    centralWidget = new CBCMAC128Task(this);
    MainWindow::setCentralWidget(centralWidget);
}

void MainWindow::createGammingMAC128Task()
{
    if (centralWidget != nullptr) {
        delete centralWidget;
    }
    centralWidget = new GammingMAC128Task(this);
    MainWindow::setCentralWidget(centralWidget);
}

void MainWindow::createGammingOFBMAC128Task()
{
    if (centralWidget != nullptr) {
        delete centralWidget;
    }
    centralWidget = new GammingOFBMAC128Task(this);
    MainWindow::setCentralWidget(centralWidget);
}

void MainWindow::createGammingCFBMAC128Task()
{
    if (centralWidget != nullptr) {
        delete centralWidget;
    }
    centralWidget = new GammingCFBMAC128Task(this);
    MainWindow::setCentralWidget(centralWidget);
}

// OTHER BLOCK
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
    delete kuznechikMenu;
    delete electronicCodeBook128Menu;
    delete gamming128Menu;
    delete gammingOutputFeedback128Menu;
    delete cipherBlockChaining128Menu;
    delete gammingCipherFeedback128Menu;
    delete messageAuthenticationCode128Menu;
    delete encodeElectronicCodeBook128Action;
    delete decodeElectronicCodeBook128Action;
    delete encodeGamming128Action;
    delete decodeGamming128Action;
    delete encodeGammingOutputFeedback128Action;
    delete decodeGammingOutputFeedback128Action;
    delete encodeCipherBlockChaining128Action;
    delete decodeCipherBlockChaining128Action;
    delete encodeGammingCipherFeedback128Action;
    delete decodeGammingCipherFeedback128Action;
    delete messageAuthenticationCodeECB128Action;
    delete messageAuthenticationCodeCBC128Action;
    delete messageAuthenticationCodeGamming128Action;
    delete messageAuthenticationCodeGammingOFB128Action;
    delete messageAuthenticationCodeGammingCFB128Action;
    delete aboutAction;
}
