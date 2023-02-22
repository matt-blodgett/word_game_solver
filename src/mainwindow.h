#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>


#include <QThread>



#include "utils/board.h"
//class Board;


class FrameBoard;
class FrameControls;


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

private:
    FrameBoard *m_frmBoard = nullptr;
    FrameControls *m_frmControls = nullptr;

private slots:
    void test();

    void process(const int &min, const int &max);
    void reset();

private:
    QThread engineThread;
    void handleResults(QMap<QString, PointList> result);

signals:
    void operate(const int &min, const int &max);
};



#endif // MAINWINDOW_H
