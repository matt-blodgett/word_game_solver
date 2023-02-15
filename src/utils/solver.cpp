#include "solver.h"


#include <QFile>


#include <QDebug>



Solver::Solver(QObject *parent) : QObject(parent)
{
    m_wordlistPath = "";
}

void Solver::setWordlistPath(const QString &path)
{
    m_wordlistPath = path;
}
QString Solver::wordlistPath() const
{
    return m_wordlistPath;
}

bool Solver::isWordValid(const QString &word)
{
    QFile inFile(m_wordlistPath);
    if(!inFile.open(QIODevice::ReadOnly)) {
        qWarning() << "error opening file for read" << m_wordlistPath;
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
QStringList Solver::filterInvalidWords(QStringList words, const bool &sort)
{
    QStringList validWords;

    QFile inFile(m_wordlistPath);
    if(!inFile.open(QIODevice::ReadOnly)) {
        qWarning() << "error opening file for read" << m_wordlistPath;
        return validWords;
    }

    QTextStream inStream(&inFile);
    while (!inStream.atEnd()) {
        QString line = inStream.readLine();
        for (QString &word : words) {
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


void Solver::generateOptimizedWordlistFile(const QString &inPath, const QString &outPath, const int &minWordLength, const int &maxWordLength)
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














