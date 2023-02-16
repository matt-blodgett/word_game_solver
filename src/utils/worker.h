#ifndef WORKER_H
#define WORKER_H


#include <QObject>


class Board;
class Solver;


class Worker : public QObject
{
    Q_OBJECT

public:
    explicit Worker(QObject *parent = nullptr);

    Board *board = nullptr;
    Solver *solver = nullptr;

public slots:
    void process(const int &min, const int &max);

signals:
    void resultReady(QStringList result);

};

#endif // WORKER_H
