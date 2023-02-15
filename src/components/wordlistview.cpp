#include "wordlistview.h"


#include <QGridLayout>

#include <QListWidget>
#include <QListWidgetItem>

#include <QLabel>



WordListView::WordListView(QWidget *parent) : QWidget(parent)
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


//    new QListWidgetItem("test1", m_listWidget);
//    new QListWidgetItem("test2", m_listWidget);
//    new QListWidgetItem("test3", m_listWidget);
//    new QListWidgetItem("test4", m_listWidget);

//    QListWidgetItem *newItem = new QListWidgetItem;
//    newItem->setText("newItem");
//    m_listWidget->insertItem(0, newItem);

    for (int i = 0; i < 100; i++) {
        new QListWidgetItem("test" + QString::number(i), m_listWidget);
    }

    m_lblWordCount->setText("Total word count = " + QString::number(m_listWidget->count()));
}
