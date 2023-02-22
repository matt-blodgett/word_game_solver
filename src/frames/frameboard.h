#ifndef FRAMEBOARD_H
#define FRAMEBOARD_H


#include <QFrame>


QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QComboBox;
class QPushButton;
class QListWidget;
QT_END_NAMESPACE


#include "utils/board.h"
//class Board;


class BoardTile : public QWidget
{
    Q_OBJECT

public:
    explicit BoardTile(QWidget *parent = nullptr);

public:
    void setValue(const QString &letter);
    QString value() const;
    QString editedValue() const;

    void setEditing(const bool &editing);

    void setHighlighted(const bool &highlighted);

private:
    QString m_value;
    bool m_editing;

private:
    QLabel *m_label = nullptr;
    QLineEdit *m_input = nullptr;

private slots:
    void onTextEdited(const QString &text);
};


class FrameBoard : public QFrame
{
    Q_OBJECT

public:
    explicit FrameBoard(QWidget *parent = nullptr);

public:
    void setBoard(Board *board);
    void setEditing(const bool &editing);

private:
    Board *m_board = nullptr;
    bool m_editing;

private:
    QFrame *m_frmTiles = nullptr;
    QVector<QVector<BoardTile*>> m_tiles;

    QFrame *m_frmConfig = nullptr;
    QPushButton *m_btnEdit = nullptr;
    QPushButton *m_btnSave = nullptr;
    QPushButton *m_btnCancel = nullptr;

    QFrame *m_frmWordList = nullptr;
    QListWidget *m_listWidget = nullptr;
    QLabel *m_lblWordCount = nullptr;


private slots:
    void onSaveClicked();
    void onWordListRowChanged(int row);

signals:
    void editingStatusChanged(const bool &editing);


public:
    void setWordList(QMap<QString, PointList> wordList);
    void clearWordList();

private:
    QMap<QString, PointList> m_wordList;

public slots:
    void setState(const QString &state);

};




#endif // FRAMEBOARD_H











