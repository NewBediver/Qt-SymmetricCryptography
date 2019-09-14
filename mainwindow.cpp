#include "mainwindow.h"
#include "MainTask/maintask.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    MainWindow::setWindowTitle(tr("Symmetric cryptography"));
    MainWindow::setWindowIcon(QIcon(":/res/appIcon.png"));
    MainWindow::resize(800, 600);

    createStatusBar();
    createMenuBar();

    // Test
    /*MainTask* widget = new MainTask(this);
    MainWindow::setCentralWidget(widget);*/
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
    gammingCipherFeedbackMenu = createMenuElement<QMenu>("&Gamming CBC", "Use GOST 28147-89 in gamming Cipher Block Chaining mode.", ":/res/menuIcon.png");
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
    encodeGammingCipherFeedbackAction = createMenuElement<QAction>("&Encode", "Use GOST 28147-89 in gamming CBC mode to encode some information.", ":/res/encodeIcon.png");
    decodeGammingCipherFeedbackAction = createMenuElement<QAction>("&Decode", "Use GOST 28147-89 in gamming CBC mode to decode some information.", ":/res/decodeIcon.png");
    encodeImitationInsertAction = createMenuElement<QAction>("&Encode", "Use GOST 28147-89 in imitation insert mode to encode some information.", ":/res/encodeIcon.png");
    decodeImitationInsertAction = createMenuElement<QAction>("&Decode", "Use GOST 28147-89 in imitation insert mode to decode some information.", ":/res/decodeIcon.png");

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

MainWindow::~MainWindow()
{

}
