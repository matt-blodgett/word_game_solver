#ifndef SOLVER_H
#define SOLVER_H


#include <QObject>


class Solver : public QObject
{
    Q_OBJECT

public:
    explicit Solver(QObject *parent = nullptr);

public:
    void setWordListPath(const QString &path);
    QString wordListPath() const;

private:
    QString m_wordListPath;

public:
    bool isValidWord(const QString &word);
    QStringList findAllValidWords(QStringList wordList, const bool &sort = true);

public:
    void generateOptimizedWordListFile(const QString &inPath, const QString &outPath, const int &minWordLength, const int &maxWordLength);
};

#endif // SOLVER_H
