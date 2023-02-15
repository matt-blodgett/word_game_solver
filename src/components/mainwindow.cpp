#include "mainwindow.h"

#include "boardview.h"
#include "controlsview.h"
#include "wordlistview.h"

#include "utils/board.h"
#include "utils/solver.h"


#include <QStyleOption>
#include <QPainter>

#include <QGridLayout>
#include <QMenuBar>

#include <QFile>


#include <QDebug>


#include <QDir>

#include <QApplication>



QString lettersRow0 = "ABCD";
QString lettersRow1 = "EFGH";
QString lettersRow2 = "IJKL";
QString lettersRow3 = "MNOP";


//QProgressBar *m_barProgress = nullptr;

//#include <QProgressBar>
//void ControlsView::test()
//{
//    int val = m_barProgress->value();
//    m_barProgress->setValue(val + 10);
//}

//m_barProgress = new QProgressBar(this);
//m_barProgress->setOrientation(Qt::Horizontal);
//m_barProgress->setTextVisible(true);
//m_barProgress->setRange(0, 100);
//m_barProgress->setValue(0);


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

}

void MainWindow::initializeObjects()
{
    m_board = new Board(this);
    m_solver = new Solver(this);

    m_frmBoardView = new BoardView(this);
    m_frmControlsView = new ControlsView(this);
    m_frmWordListView = new WordListView(this);

    connect(m_frmBoardView, &BoardView::editingStatusChanged, m_frmControlsView, &ControlsView::setDisabled);
    connect(m_frmControlsView, &ControlsView::processStarted, this, &MainWindow::process);
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
    gridMain->addWidget(m_frmControlsView, 0, 0, 1, 1);
    gridMain->addWidget(m_frmBoardView, 0, 2, 1, 1);
    gridMain->addWidget(m_frmWordListView, 0, 4, 1, 1);
//    gridMain->setColumnStretch(1, 1);
//    gridMain->setColumnStretch(3, 1);
//    gridMain->setColumnMinimumWidth(0, 60);
//    gridMain->setColumnMinimumWidth(1, 40);
//    gridMain->setColumnMinimumWidth(2, 60);
//    gridMain->setColumnMinimumWidth(3, 40);
//    gridMain->setColumnMinimumWidth(4, 60);
//    gridMain->setColumnStretch(2, 1);
    gridMain->setRowStretch(1, 1);
//    gridMain->setContentsMargins(0, 0, 0, 0);
//    gridMain->setHorizontalSpacing(0);
//    gridMain->setVerticalSpacing(0);
    windowMain->setLayout(gridMain);

    setFixedSize(700, 450);

    setWindowTitle("Game Pidgeon Solver");

    setCentralWidget(windowMain);
}
void MainWindow::initializeState()
{
    QString letters = lettersRow0 + lettersRow1 + lettersRow2 + lettersRow3;
    int gridSize = 4;
    m_board->setup(letters, gridSize);
    m_frmBoardView->setBoard(m_board);
}
void MainWindow::initializeStyle()
{
    QString inPath = QDir::currentPath() + QDir::separator() + "assets" + QDir::separator() + "test.qss";
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
void MainWindow::saveSettings()
{

}


void MainWindow::process()
{
    qDebug() << "test";

//    QStringList boardWords = m_board->getAllWords();
//    QStringList validWords = m_solver->filterInvalidWords(boardWords);

//    for (QString &word : validWords) {
//        qDebug() << word;
//    }

//    qDebug() << "total board word count: " << boardWords.size();
//    qDebug() << "total valid word count: " << validWords.size();
//    qDebug() << "done";
}




void MainWindow::closeEvent(QCloseEvent *event)
{
    saveSettings();
    QMainWindow::closeEvent(event);
}
void MainWindow::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);

    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

    QWidget::paintEvent(event);
}













