#ifndef BOARDVIEW_H
#define BOARDVIEW_H


#include <QWidget>


QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QPushButton;
QT_END_NAMESPACE


class Board;


class BoardViewTile : public QWidget
{
    Q_OBJECT

public:
    explicit BoardViewTile(QWidget *parent = nullptr);

public:
    void setValue(const QString &letter);
    QString value() const;
    QString editedValue() const;

    void setEditing(const bool &editing);

private:
    QString m_value;
    bool m_editing;

private:
    QLabel *m_label = nullptr;
    QLineEdit *m_input = nullptr;

private slots:
    void onTextEdited(const QString &text);
};


class BoardView : public QWidget
{
    Q_OBJECT

public:
    explicit BoardView(QWidget *parent = nullptr);

public:
    void setBoard(Board *board);
    void setEditing(const bool &editing);

private:
    Board *m_board = nullptr;
    bool m_editing;

private:
    QWidget *m_frmTiles = nullptr;

    QPushButton *m_btnEdit = nullptr;
    QPushButton *m_btnSave = nullptr;
    QPushButton *m_btnCancel = nullptr;

    QVector<QVector<BoardViewTile*>> m_tiles;

private slots:
    void onSaveClicked();

signals:
    void editingStatusChanged(const bool &editing);
};

#endif // BOARDVIEW_H











