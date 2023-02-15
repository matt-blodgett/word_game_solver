#ifndef WORDLISTVIEW_H
#define WORDLISTVIEW_H


#include <QWidget>


QT_BEGIN_NAMESPACE
class QListWidget;
class QLabel;
QT_END_NAMESPACE


class WordListView : public QWidget
{
    Q_OBJECT

public:
    explicit WordListView(QWidget *parent = nullptr);

private:
    QListWidget *m_listWidget = nullptr;
    QLabel *m_lblWordCount = nullptr;

signals:

};

#endif // WORDLISTVIEW_H
