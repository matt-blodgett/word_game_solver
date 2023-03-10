#ifndef SOLUTIONENGINE_H
#define SOLUTIONENGINE_H


#include <QObject>


#include "utils/board.h"
//class Board;
class WordValidator;


class SolutionEngine : public QObject
{
    Q_OBJECT

public:
    explicit SolutionEngine(QObject *parent = nullptr);

public:
    void initialize(Board *board);

private:
    Board *m_board = nullptr;
    WordValidator *m_wordValidator = nullptr;

public slots:
    void process(const int &min, const int &max);

signals:
    void processFinished(QMap<QString, PointList> validWords);

};

#endif // SOLUTIONENGINE_H
