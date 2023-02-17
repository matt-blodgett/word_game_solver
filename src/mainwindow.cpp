#include "mainwindow.h"

#include "version.h"

#include "utils/board.h"
#include "utils/solutionengine.h"

#include "frames/frameboard.h"
#include "frames/framecontrols.h"
#include "frames/framewordlist.h"



#include <QGridLayout>

#include <QMenuBar>

#include <QFile>
#include <QDir>


#include <QDebug>





QString lettersRow0 = "ABCD";
QString lettersRow1 = "EFGH";
QString lettersRow2 = "IJKL";
QString lettersRow3 = "MNOP";



MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    initializeObjects();
    initializeMainMenu();
    initializeLayout();
    initializeState();
    initializeStyle();
    centralWidget()->show();
}
MainWindow::~MainWindow()
{
    engineThread.quit();
    engineThread.wait();
}

void MainWindow::initializeObjects()
{
    m_board = new Board(this);

    m_frmBoard = new FrameBoard(this);
    m_frmControls = new FrameControls(this);
    m_frmWordList = new FrameWordList(this);

    connect(m_frmBoard, &FrameBoard::editingStatusChanged, m_frmControls, &FrameControls::setDisabled);
    connect(m_frmControls, &FrameControls::startProcessClicked, this, &MainWindow::process);
}
void MainWindow::initializeMainMenu()
{
    QMenuBar *menuMain = menuBar();

    QAction *actWndExit = new QAction(menuMain);

    actWndExit->setText("Exit");

    QMenu *menuFile = new QMenu(menuMain);

    menuFile->setTitle("File");

    menuMain->addMenu(menuFile);
    menuFile->addAction(actWndExit);

    connect(actWndExit, &QAction::triggered, this, [this](){window()->close();});
}
void MainWindow::initializeLayout()
{
    QWidget *windowMain = new QWidget(this);
    QGridLayout *gridMain = new QGridLayout(windowMain);

    gridMain->setRowStretch(0, 1);
    gridMain->setColumnStretch(0, 1);
    gridMain->addWidget(m_frmBoard, 1, 1, 1, 1);
    gridMain->setRowStretch(2, 1);
    gridMain->setColumnStretch(2, 1);

    gridMain->addWidget(m_frmWordList, 0, 3, 3, 1);

    gridMain->addWidget(m_frmControls, 3, 0, 1, 5);



//    gridMain->setContentsMargins(0, 0, 0, 0);
//    gridMain->setHorizontalSpacing(0);
//    gridMain->setVerticalSpacing(0);
    windowMain->setLayout(gridMain);

//    m_frmBoard->setFixedSize(200, 200);
    m_frmWordList->setFixedWidth(150);

    setMinimumSize(650, 550);
//    setFixedSize(550, 550);

    setCentralWidget(windowMain);

    setWindowTitle("Word Game Solver v" + QString(VERSION_STRING));
    setWindowIcon(QIcon(":/icons/temp.ico"));
}
void MainWindow::initializeState()
{
    QString letters = lettersRow0 + lettersRow1 + lettersRow2 + lettersRow3;
    int gridSize = 4;
    m_board->initialize(letters, gridSize);
    m_frmBoard->setBoard(m_board);
}
void MainWindow::initializeStyle()
{
    QString inPath(":/files/style.qss");
    QFile inFile(inPath);
    if(!inFile.open(QIODevice::ReadOnly)) {
        qWarning() << "error opening file for read" << inPath;
        return;
    }

    QTextStream inStream(&inFile);
    QString qss = inStream.readAll();

    inFile.close();

    setStyleSheet(qss);
}


void MainWindow::process(const int &min, const int &max)
{
//    Q_UNUSED(min)
//    Q_UNUSED(max)

    SolutionEngine *engine = new SolutionEngine;
    engine->initialize(m_board);
    engine->moveToThread(&engineThread);

    connect(&engineThread, &QThread::finished, engine, &QObject::deleteLater);
    connect(this, &MainWindow::operate, engine, &SolutionEngine::process);
    connect(engine, &SolutionEngine::processFinished, this, &MainWindow::handleResults);
    engineThread.start();

    emit operate(min, max);
}

void MainWindow::handleResults(QStringList result)
{
    m_frmWordList->setWordList(result);
}









