#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>


//QT_BEGIN_NAMESPACE
//class QPushButton;
//QT_END_NAMESPACE


class Board;
class Solver;

class BoardView;
class ControlsView;
class WordListView;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initializeObjects();
    void initializeMainMenu();
    void initializeLayout();
    void initializeState();
    void initializeStyle();
    void saveSettings();

private:
    Board *m_board = nullptr;
    Solver *m_solver = nullptr;

private:
    BoardView *m_frmBoardView = nullptr;
    ControlsView *m_frmControlsView = nullptr;
    WordListView *m_frmWordListView = nullptr;

private slots:
    void process();

protected:
    void closeEvent(QCloseEvent *event);
    void paintEvent(QPaintEvent *event);
};



#endif // MAINWINDOW_H
