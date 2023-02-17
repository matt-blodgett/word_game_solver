#ifndef WORDVALIDATOR_H
#define WORDVALIDATOR_H


#include <QObject>


class WordValidator : public QObject
{
    Q_OBJECT

public:
    explicit WordValidator(QObject *parent = nullptr);

public:
    void setWordListPath(const QString &path);
    QString wordListPath() const;

private:
    QString m_wordListPath;

public:
    bool isValidWord(const QString &word);
    QStringList findAllValidWords(QStringList wordList, const bool &sort = true);

public:
    static void generateOptimizedWordListFile(const QString &inPath, const QString &outPath, const int &minWordLength, const int &maxWordLength);
};

#endif // WORDVALIDATOR_H
