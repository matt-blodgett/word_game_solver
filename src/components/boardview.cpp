#include "boardview.h"


#include "utils/board.h"


#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>


#include <QKeyEvent>
#include <QApplication>




BoardViewTile::BoardViewTile(QWidget *parent) : QWidget(parent)
{
    m_label = new QLabel(this);
    m_input = new QLineEdit(this);

    m_label->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    m_input->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

    m_label->setFixedSize(50, 50);
    m_input->setFixedSize(50, 50);

    QGridLayout *gridMain = new QGridLayout(this);
    gridMain->addWidget(m_label, 1, 1, 1, 1);
    gridMain->addWidget(m_input, 1, 1, 1, 1);
    gridMain->setContentsMargins(0, 0, 0, 0);
    gridMain->setHorizontalSpacing(0);
    gridMain->setVerticalSpacing(0);
    setLayout(gridMain);

    m_input->hide();

    m_input->setMaxLength(1);

    connect(m_input, &QLineEdit::textEdited, this, &BoardViewTile::onTextEdited);


    m_label->setObjectName("BoardTileLabel");
    m_input->setObjectName("BoardTileInput");
}


void BoardViewTile::setValue(const QString &letter)
{
    m_value = letter;
    m_label->setText(m_value);
    m_input->setText(m_value);
}
QString BoardViewTile::value() const
{
    return m_value;
}
QString BoardViewTile::editedValue() const
{
    return m_input->text();
}

void BoardViewTile::setEditing(const bool &editing)
{
    m_editing = editing;

    if (m_editing) {
        m_label->hide();
        m_input->show();
    } else {
        m_input->hide();
        m_label->show();
    }
}

void BoardViewTile::onTextEdited(const QString &text)
{
    m_input->setText(text.toUpper());
    QKeyEvent event(QEvent::KeyPress, Qt::Key_Tab, Qt::NoModifier);
    QApplication::sendEvent(m_input, &event);
}






BoardView::BoardView(QWidget *parent) : QWidget(parent)
{
    m_frmTiles = new QWidget(this);

    m_btnEdit = new QPushButton(this);
    m_btnSave = new QPushButton(this);
    m_btnCancel = new QPushButton(this);

    m_btnEdit->setText("Edit");
    m_btnSave->setText("Done");
    m_btnCancel->setText("Cancel");

    connect(m_btnEdit, &QPushButton::released, this, [this]{setEditing(true);});
    connect(m_btnSave, &QPushButton::released, this, &BoardView::onSaveClicked);
    connect(m_btnCancel, &QPushButton::released, this, [this]{setEditing(false);});
}


void BoardView::setBoard(Board *board)
{
    m_board = board;

    QGridLayout *gridTiles = new QGridLayout(m_frmTiles);
    for (int x = 0; x < m_board->gridSize(); x++) {
        QVector<BoardViewTile*> row;

        for (int y = 0; y < m_board->gridSize(); y++) {
            BoardViewTile *tile = new BoardViewTile(this);

            tile->setValue(m_board->letterAt(x, y));
            gridTiles->addWidget(tile, x, y, 1, 1);

            row << tile;
        }
        m_tiles << row;
    }

    // left, top, right, bottom
    gridTiles->setContentsMargins(0, 0, 0, 0);
    gridTiles->setHorizontalSpacing(0);
    gridTiles->setVerticalSpacing(0);
    m_frmTiles->setLayout(gridTiles);


    QGridLayout *gridMain = new QGridLayout(this);
    gridMain->addWidget(m_frmTiles, 1, 1, 1, 1);
    gridMain->addWidget(m_btnEdit, 2, 1, 1, 1);
    gridMain->addWidget(m_btnSave, 2, 1, 1, 1);
    gridMain->addWidget(m_btnCancel, 3, 1, 1, 1);
//    gridMain->setColumnStretch(0, 1);
    gridMain->setColumnStretch(1, 0);
//    gridMain->setColumnStretch(2, 1);
//    gridMain->setRowStretch(0, 1);
    gridMain->setRowStretch(1, 0);
//    gridMain->setRowStretch(2, 1);
//    gridMain->setContentsMargins(0, 0, 0, 0);
//    gridMain->setHorizontalSpacing(0);
//    gridMain->setVerticalSpacing(0);
    setLayout(gridMain);

    m_btnSave->hide();
    m_btnCancel->hide();
}

void BoardView::setEditing(const bool &editing)
{
    if (m_editing == editing) {
        return;
    }

    m_editing = editing;

    if (m_editing) {
        m_btnEdit->hide();
        m_btnSave->show();
        m_btnCancel->show();
    } else {
        m_btnEdit->show();
        m_btnSave->hide();
        m_btnCancel->hide();
    }

    for (QVector<BoardViewTile*> &tiles : m_tiles) {
        for (BoardViewTile *tile : tiles) {
            tile->setEditing(m_editing);
        }
    }

    emit editingStatusChanged(m_editing);
}

void BoardView::onSaveClicked()
{
    QString letters;
    for (QVector<BoardViewTile*> &tiles : m_tiles) {
        for (BoardViewTile *tile : tiles) {
            letters += tile->editedValue();
        }
    }

    m_board->setLetters(letters);

    for (int x = 0; x < m_board->gridSize(); x++) {
        for (int y = 0; y < m_board->gridSize(); y++) {
            BoardViewTile *tile = m_tiles[x][y];
            tile->setValue(m_board->letterAt(x, y));
        }
    }

    setEditing(false);
}








