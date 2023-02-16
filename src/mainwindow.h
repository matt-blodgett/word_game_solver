#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>


#include <QThread>



class Board;
class Solver;

class FrameBoard;
class FrameControls;
class FrameWordList;


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

private:
    Board *m_board = nullptr;
    Solver *m_solver = nullptr;

private:
    FrameBoard *m_frmBoard = nullptr;
    FrameControls *m_frmControls = nullptr;
    FrameWordList *m_frmWordList = nullptr;

private slots:
    void process(const int &min, const int &max);

private:
    QThread workerThread;
    void handleResults(QStringList result);

signals:
    void operate(const int &min, const int &max);
};



#endif // MAINWINDOW_H
