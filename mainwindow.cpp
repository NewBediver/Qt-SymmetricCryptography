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
#include "Tasks/Imitation_Insert/encodeimitationinserttask.h"
#include "Tasks/Imitation_Insert/decodeimitationinserttask.h"
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
    connect(encodeImitationInsertAction, SIGNAL(triggered()), this, SLOT(createEncodeImitationInsertTask()));
    connect(decodeImitationInsertAction, SIGNAL(triggered()), this, SLOT(createDecodeImitationInsertTask()));
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
    gammingCipherFeedbackMenu = createMenuElement<QMenu>("&Gamming CFB", "Use GOST 28147-89 in gamming Cipher FeedBAck mode.", ":/res/menuIcon.png");
    imitationInsertMenu = createMenuElement<QMenu>("&Imitation Insert", "Use GOST 28147-89 in imitation insert mode.", ":/res/menuIcon.png");

    //Create actions to electronicCodeBookAction
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
    encodeImitationInsertAction = createMenuElement<QAction>("&Encode", "Use GOST 28147-89 in imitation insert mode to encode some information.", ":/res/encodeIcon.png");
    decodeImitationInsertAction = createMenuElement<QAction>("&Decode", "Use GOST 28147-89 in imitation insert mode to decode some information.", ":/res/decodeIcon.png");

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
    imitationInsertMenu->addAction(encodeImitationInsertAction);
    imitationInsertMenu->addAction(decodeImitationInsertAction);

    //Add L2 menues to L1 menu
    magmaMenu->addMenu(electronicCodeBookMenu);
    magmaMenu->addMenu(gammingMenu);
    magmaMenu->addMenu(gammingOutputFeedbackMenu);
    magmaMenu->addMenu(cipherBlockChainingMenu);
    magmaMenu->addMenu(gammingCipherFeedbackMenu);
    magmaMenu->addMenu(imitationInsertMenu);

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

void MainWindow::createEncodeImitationInsertTask()
{
    if (centralWidget != nullptr) {
        delete centralWidget;
    }
    centralWidget = new EncodeImitationInsertTask(this);
    MainWindow::setCentralWidget(centralWidget);
}

void MainWindow::createDecodeImitationInsertTask()
{
    if (centralWidget != nullptr) {
        delete centralWidget;
    }
    centralWidget = new DecodeImitationInsertTask(this);
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
    delete imitationInsertMenu;
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
    delete encodeImitationInsertAction;
    delete decodeImitationInsertAction;
    delete aboutAction;
}
