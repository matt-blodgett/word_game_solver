#include "framewordlist.h"


#include <QGridLayout>

#include <QLabel>

#include <QListWidget>
#include <QListWidgetItem>




FrameWordList::FrameWordList(QWidget *parent) : QFrame(parent)
{
    m_listWidget = new QListWidget(this);
    m_lblWordCount = new QLabel(this);

    QGridLayout *gridMain = new QGridLayout(this);
    gridMain->addWidget(m_listWidget, 0, 0, 1, 1);
    gridMain->addWidget(m_lblWordCount, 1, 0, 1, 1);
//    gridMain->setContentsMargins(0, 0, 0, 0);
//    gridMain->setHorizontalSpacing(0);
//    gridMain->setVerticalSpacing(0);
    setLayout(gridMain);
}


void FrameWordList::setWordList(QStringList wordList)
{
//    for (QString &word : wordList) {
//        QListWidgetItem *item = new QListWidgetItem;
//        item->setText(word);
//        m_listWidget->addItem(item);
//    }

    m_listWidget->addItems(wordList);
    m_lblWordCount->setText("Total words: " + QString::number(wordList.length()));

}
