#ifndef BOARD_H
#define BOARD_H


#include <QObject>


struct Point
{
    int x;
    int y;
    bool operator==(const Point &p) {
        return (p.x == x && p.y == y);
    }
};


typedef QVector<Point> PointList;


class Board : public QObject
{
    Q_GADGET

public:
    explicit Board(QObject *parent = nullptr);

public:
    void setup(const QString &letters, const int &gridSize);
    void setLetters(const QString &letters);

    QChar letterAt(const Point &point);
    QChar letterAt(const int &x, const int &y);

    int gridSize() const;

private:
    QString m_letters;
    int m_gridSize;
    QVector<QVector<QChar>> m_grid;

private:
    PointList getPointNeighbours(const Point &point);
    QVector<PointList> getPointCombinationsAt(const Point &startPoint, const int &depth);
    QVector<PointList> getAllPointCombinations(const int &depth);

public:
    QString pointsToString(const PointList &points);
    QStringList findAllValidStrings(const int &minLength = 0, const int &maxLength = -1);
};

#endif // BOARD_H



























