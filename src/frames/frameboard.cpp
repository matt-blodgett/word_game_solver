#include "frameboard.h"


#include "utils/board.h"


#include <QGridLayout>

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>


#include <QKeyEvent>
#include <QApplication>


#include <QListWidget>
#include <QListWidgetItem>
#include <QComboBox>




// --------------------------------------------------

BoardTile::BoardTile(QWidget *parent) : QWidget(parent)
{
    m_label = new QLabel(this);
    m_input = new QLineEdit(this);

//    m_label->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
//    m_input->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

    m_label->setFixedSize(50, 50);
    m_input->setFixedSize(50, 50);

    QGridLayout *gridMain = new QGridLayout(this);
    gridMain->addWidget(m_label, 0, 0, 1, 1);
    gridMain->addWidget(m_input, 0, 0, 1, 1);
    gridMain->setContentsMargins(0, 0, 0, 0);
    gridMain->setHorizontalSpacing(0);
    gridMain->setVerticalSpacing(0);
    setLayout(gridMain);

    m_input->setVisible(false);

    m_input->setMaxLength(1);

    connect(m_input, &QLineEdit::textEdited, this, &BoardTile::onTextEdited);


    m_label->setObjectName("BoardTileLabel");
    m_input->setObjectName("BoardTileInput");
}


void BoardTile::setValue(const QString &letter)
{
    m_value = letter;
    m_label->setText(m_value);
    m_input->setText(m_value);
}
QString BoardTile::value() const
{
    return m_value;
}
QString BoardTile::editedValue() const
{
    return m_input->text();
}

void BoardTile::setEditing(const bool &editing)
{
    m_editing = editing;

    m_label->setVisible(!m_editing);
    m_input->setVisible(m_editing);
}

void BoardTile::setHighlighted(const bool &highlighted)
{
    if (highlighted) {
        m_label->setStyleSheet("BoardTile QLabel#BoardTileLabel {border: 1px solid #000000; font-size: 26px;background: #d1a4eb;}");
    } else {
        m_label->setStyleSheet("BoardTile QLabel#BoardTileLabel {border: 1px solid #000000; font-size: 26px;}");
    }

}

void BoardTile::onTextEdited(const QString &text)
{
    m_input->setText(text.toUpper());
    QKeyEvent event(QEvent::KeyPress, Qt::Key_Tab, Qt::NoModifier);
    QApplication::sendEvent(m_input, &event);
}




// --------------------------------------------------

FrameBoard::FrameBoard(QWidget *parent) : QFrame(parent)
{
    m_frmTiles = new QFrame(this);

    m_frmConfig = new QFrame(this);
    m_btnEdit = new QPushButton(m_frmConfig);
    m_btnSave = new QPushButton(m_frmConfig);
    m_btnCancel = new QPushButton(m_frmConfig);

    m_frmWordList = new QFrame(this);
    m_listWidget = new QListWidget(m_frmWordList);
    m_lblWordCount = new QLabel(m_frmWordList);

    m_listWidget->setFixedWidth(100);

    m_btnEdit->setText("Edit");
    m_btnSave->setText("Done");
    m_btnCancel->setText("Cancel");

    m_lblWordCount->setText("Total words: 0");

    connect(m_btnEdit, &QPushButton::released, this, [this]{setEditing(true);});
    connect(m_btnSave, &QPushButton::released, this, &FrameBoard::onSaveClicked);
    connect(m_btnCancel, &QPushButton::released, this, [this]{setEditing(false);});

    connect(m_listWidget, &QListWidget::currentRowChanged, this, &FrameBoard::onWordListRowChanged);
}


void FrameBoard::setBoard(Board *board)
{
    m_board = board;

    QGridLayout *gridTiles = new QGridLayout(m_frmTiles);
    for (int x = 0; x < m_board->gridSize(); x++) {
        QVector<BoardTile*> row;

        for (int y = 0; y < m_board->gridSize(); y++) {
            BoardTile *tile = new BoardTile(this);

            tile->setValue(m_board->letterAt(x, y));
            gridTiles->addWidget(tile, x, y, 1, 1);

            row << tile;
        }
        m_tiles << row;
    }

    // left, top, right, bottom
//    gridTiles->setContentsMargins(0, 0, 0, 0);
    gridTiles->setHorizontalSpacing(0);
    gridTiles->setVerticalSpacing(0);
    m_frmTiles->setLayout(gridTiles);

    QGridLayout *gridConfig = new QGridLayout(m_frmConfig);
    gridConfig->addWidget(m_btnEdit, 0, 0, 1, 1);
    gridConfig->addWidget(m_btnSave, 0, 0, 1, 1);
    gridConfig->addWidget(m_btnCancel, 0, 1, 1, 1);
//    gridConfig->setContentsMargins(0, 0, 0, 0);
//    gridConfig->setHorizontalSpacing(0);
//    gridConfig->setVerticalSpacing(0);
    m_frmConfig->setLayout(gridConfig);

    QGridLayout *gridWordList = new QGridLayout(m_frmWordList);
    gridWordList->addWidget(m_listWidget, 0, 0, 1, 1);
    gridWordList->addWidget(m_lblWordCount, 1, 0, 1, 1);
//    gridWordList->setContentsMargins(0, 0, 0, 0);
//    gridWordList->setHorizontalSpacing(0);
//    gridWordList->setVerticalSpacing(0);
    m_frmWordList->setLayout(gridWordList);

    QGridLayout *gridMain = new QGridLayout(this);
    gridMain->addWidget(m_frmTiles, 0, 0, 1, 1);
    gridMain->addWidget(m_frmConfig, 1, 0, 1, 1);
    gridMain->addWidget(m_frmWordList, 0, 1, 3, 1);
    gridMain->setRowStretch(2, 1);
    gridMain->setContentsMargins(0, 0, 0, 0);
//    gridMain->setHorizontalSpacing(0);
//    gridMain->setVerticalSpacing(0);
    setLayout(gridMain);


    setEditing(false);
}

void FrameBoard::setEditing(const bool &editing)
{
//    if (m_editing == editing) {
//        return;
//    }

    m_editing = editing;

    m_btnEdit->setVisible(!m_editing);
    m_btnSave->setVisible(m_editing);
    m_btnCancel->setVisible(m_editing);

    for (QVector<BoardTile*> &tiles : m_tiles) {
        for (BoardTile *tile : tiles) {
            tile->setEditing(m_editing);
        }
    }

    emit editingStatusChanged(m_editing);
}

void FrameBoard::onSaveClicked()
{
    QString letters;
    for (QVector<BoardTile*> &tiles : m_tiles) {
        for (BoardTile *tile : tiles) {
            letters += tile->editedValue();
        }
    }

    m_board->setLetters(letters);

    for (int x = 0; x < m_board->gridSize(); x++) {
        for (int y = 0; y < m_board->gridSize(); y++) {
            BoardTile *tile = m_tiles[x][y];
            tile->setValue(m_board->letterAt(x, y));
        }
    }

    setEditing(false);
}
void FrameBoard::onWordListRowChanged(int row)
{
    if (row < 0) {
        return;
    }

    for (int x = 0; x < m_board->gridSize(); x++) {
        for (int y = 0; y < m_board->gridSize(); y++) {
            m_tiles[x][y]->setHighlighted(false);
        }
    }

    QString word = m_listWidget->item(row)->text();
    if (m_wordList.contains(word)) {
        PointList points = m_wordList[word];
        for (Point p : points) {
            m_tiles[p.x][p.y]->setHighlighted(true);
        }
    }
}




void FrameBoard::setWordList(QMap<QString, PointList> wordList)
{
//    for (QString &word : wordList) {
//        QListWidgetItem *item = new QListWidgetItem;
//        item->setText(word);
//        m_listWidget->addItem(item);
//    }

    m_wordList = wordList;

    QStringList items = wordList.keys();

    m_listWidget->addItems(items);
    m_lblWordCount->setText("Total words: " + QString::number(items.length()));

}

void FrameBoard::clearWordList()
{
    m_wordList.clear();
    m_listWidget->clear();
    m_lblWordCount->setText("Total words: 0");
}



void FrameBoard::setState(const QString &state)
{
    m_frmConfig->setVisible(false);

    if (state == "initial") {
        m_frmConfig->setVisible(true);
    } else if (state == "loading") {
        // nothing
    } else if (state == "done") {
        // nothing
    }
}


