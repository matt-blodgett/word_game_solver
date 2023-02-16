#include "worker.h"


#include "board.h"
#include "solver.h"


#include <QDebug>


Worker::Worker(QObject *parent) : QObject(parent)
{

}

void Worker::process(const int &min, const int &max)
{
    qDebug() << "getting board strings";
    QStringList boardStrings = board->findAllValidStrings(min, max);

    qDebug() << "getting valid words";
    QStringList validWords = solver->findAllValidWords(boardStrings);

    qDebug() << "done";

    qDebug() << "board strings:" << boardStrings.size();
    qDebug() << "valid words:" << validWords.size();

    emit resultReady(validWords);
}
