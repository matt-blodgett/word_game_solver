#ifndef SOLVER_H
#define SOLVER_H


#include <QObject>


class Solver : public QObject
{
    Q_GADGET

public:
    explicit Solver(QObject *parent = nullptr);

public:
    void setWordlistPath(const QString &path);
    QString wordlistPath() const;

private:
    QString m_wordlistPath;

public:
    bool isWordValid(const QString &word);
    QStringList filterInvalidWords(QStringList words, const bool &sort = false);

public:
    void generateOptimizedWordlistFile(const QString &inPath, const QString &outPath, const int &minWordLength, const int &maxWordLength);
};

#endif // SOLVER_H
