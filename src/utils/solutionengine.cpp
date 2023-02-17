#include "solutionengine.h"


#include "board.h"
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
    QStringList boardStrings = m_board->findAllValidStrings(min, max);

    qDebug() << "getting valid words";
    QStringList validWords = m_wordValidator->findAllValidWords(boardStrings);

    qDebug() << "done";

    qDebug() << "board strings:" << boardStrings.size();
    qDebug() << "valid words:" << validWords.size();

    emit processFinished(validWords);
}
