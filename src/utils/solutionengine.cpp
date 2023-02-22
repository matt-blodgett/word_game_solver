#include "solutionengine.h"


//#include "board.h"
#include "wordvalidator.h"


#include <QDebug>


SolutionEngine::SolutionEngine(QObject *parent) : QObject(parent)
{

}

void SolutionEngine::initialize(Board *board)
{
    m_board = new Board(this);
    m_wordValidator = new WordValidator(this);

    m_board->initialize(board->letters(), board->gridSize());
}

void SolutionEngine::process(const int &min, const int &max)
{
    qDebug() << "getting board strings";
    QMap<QString, PointList> boardStrings = m_board->findAllValidStrings(min, max);
    QStringList validStrings = boardStrings.keys();

    qDebug() << "getting valid words";
    QStringList validWords = m_wordValidator->findAllValidWords(validStrings);

    qDebug() << "done";

    qDebug() << "board strings:" << boardStrings.size();
    qDebug() << "valid words:" << validWords.size();

    QMap<QString, PointList> ret;
    for (QString &word : validWords) {
        ret[word] = boardStrings[word];
    }

    emit processFinished(ret);
}
