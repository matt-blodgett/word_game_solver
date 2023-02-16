#include "solver.h"


#include <QFile>


#include <QDebug>



Solver::Solver(QObject *parent) : QObject(parent)
{
    m_wordListPath = "wordlist.txt";
}

void Solver::setWordListPath(const QString &path)
{
    m_wordListPath = path;
}
QString Solver::wordListPath() const
{
    return m_wordListPath;
}

bool Solver::isValidWord(const QString &word)
{
    QFile inFile(m_wordListPath);
    if(!inFile.open(QIODevice::ReadOnly)) {
        qWarning() << "error opening file for read" << m_wordListPath;
        return false;
    }

    bool foundMatch = false;

    QTextStream inStream(&inFile);
    while (!inStream.atEnd()) {
        QString line = inStream.readLine();
        if (word == line) {
            foundMatch = true;
            break;
        }
    }

    inFile.close();

    return foundMatch;
}
QStringList Solver::findAllValidWords(QStringList wordList, const bool &sort)
{
    QStringList validWords;

    QFile inFile(m_wordListPath);
    if(!inFile.open(QIODevice::ReadOnly)) {
        qWarning() << "error opening file for read" << m_wordListPath;
        return validWords;
    }

    QTextStream inStream(&inFile);
    while (!inStream.atEnd()) {
        QString line = inStream.readLine();
        for (QString &word : wordList) {
            if (word == line) {
                validWords.push_back(word);
                break;
            }
        }
    }

    inFile.close();

    if (sort) {
        std::sort(validWords.begin(), validWords.end(),
            [] (const QString &a, const QString &b) { return a.size() > b.size(); }
        );
    }

    return validWords;
}


void Solver::generateOptimizedWordListFile(const QString &inPath, const QString &outPath, const int &minWordLength, const int &maxWordLength)
{
    QFile inFile(inPath);
    if(!inFile.open(QIODevice::ReadOnly)) {
        qWarning() << "error opening file for read" << inPath;
        return;
    }

    QFile outFile(outPath);
    if(!outFile.open(QIODevice::WriteOnly)) {
        qWarning() << "error opening file for read" << outPath;
        return;
    }

    QTextStream inStream(&inFile);
    QTextStream outStream(&outFile);

    while (!inStream.atEnd()) {
        QString line = inStream.readLine();
        if (line.length() >= minWordLength && line.length() <= maxWordLength) {
            outStream << line << Qt::endl;
        }
    }

    inFile.close();
    outFile.close();
}














