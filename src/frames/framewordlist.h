#ifndef FRAMEWORDLIST_H
#define FRAMEWORDLIST_H


#include <QFrame>


QT_BEGIN_NAMESPACE
class QListWidget;
class QLabel;
QT_END_NAMESPACE


class FrameWordList : public QFrame
{
    Q_OBJECT

public:
    explicit FrameWordList(QWidget *parent = nullptr);

public:
    void setWordList(QStringList wordList);

private:
    QListWidget *m_listWidget = nullptr;
    QLabel *m_lblWordCount = nullptr;

signals:

};

#endif // FRAMEWORDLIST_H
