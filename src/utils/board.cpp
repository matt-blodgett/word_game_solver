#include "board.h"



#include <QDebug>




Board::Board(QObject *parent) : QObject(parent)
{

}


void Board::setup(const QString &letters, const int &gridSize)
{
    m_gridSize = gridSize;
    setLetters(letters);
}

void Board::setLetters(const QString &letters)
{
    if (m_letters == letters) {
        return;
    }

    m_letters = letters;

    m_grid.clear();
    for (int i = 0; i < m_gridSize; i++) {
        QVector<QChar> row;
        for (int j = 0; j < m_gridSize; j++) {
            QChar letter = letters[j + (i * m_gridSize)];
            row.push_back(letter);
        }
        m_grid.push_back(row);
    }
}

int Board::gridSize() const
{
    return m_gridSize;
}

QChar Board::letterAt(const Point &point)
{
    return m_grid[point.x][point.y];
}
QChar Board::letterAt(const int &x, const int &y)
{
    Point point = {x, y};
    return letterAt(point);
}


PointList Board::getPointNeighbours(const Point &point)
{
    int x = point.x;
    int y = point.y;

    PointList pointNeighbours = {
        {x + 0, y + 1},
        {x + 0, y - 1},
        {x + 1, y + 0},
        {x + 1, y + 1},
        {x + 1, y - 1},
        {x - 1, y + 0},
        {x - 1, y + 1},
        {x - 1, y - 1}
    };

    PointList validPointNeighbours;
    for (Point &p : pointNeighbours) {
        if (p.x >= 0 && p.y >= 0 && p.x < m_gridSize && p.y < m_gridSize) {
            validPointNeighbours.push_back(p);
        }
    }

    return validPointNeighbours;
}
QVector<PointList> Board::getPointCombinationsAt(const Point &startPoint, const int &depth)
{
    QVector<PointList> pointCombinations;

    if (depth < 0) {
        return pointCombinations;
    }

    for (Point &startPointNeighbour : getPointNeighbours(startPoint)) {

        for (Point &childNeighbour : getPointNeighbours(startPointNeighbour)) {

            if (childNeighbour == startPoint) {
                continue;
            }

            PointList pointCombination;
            pointCombination.push_back(startPoint);

            if (depth > 1) {
                pointCombination.push_back(startPointNeighbour);
                if (depth > 2) {
                    pointCombination.push_back(childNeighbour);
                }
            }

            pointCombinations.push_back(pointCombination);
        }
    }

    QVector<PointList> currentDepthPoints(pointCombinations);

    for (int i = 0; i < depth - 3; i++) {
        QVector<PointList> depthPoints;

        for (PointList &points : currentDepthPoints) {
            Point lastPoint = points.back();

            for (const Point &childNeighbour : getPointNeighbours(lastPoint)) {
                if (std::count(points.begin(), points.end(), childNeighbour) > 0) {
                    continue;
                }
                PointList pointCombination(points);
                pointCombination.push_back(childNeighbour);
                depthPoints.push_back(pointCombination);
            }
        }

        for (PointList &pointCombination : depthPoints) {
            pointCombinations.push_back(pointCombination);
        }

        currentDepthPoints = depthPoints;
    }

    return pointCombinations;
}
QVector<PointList> Board::getAllPointCombinations(const int &depth)
{
    QVector<PointList> allPointCombinations;

    for (int x = 0; x < m_gridSize; x++) {
        for (int y = 0; y < m_gridSize; y++) {
            Point startPoint = {x, y};
            for (PointList &pointCombination : getPointCombinationsAt(startPoint, depth)) {
                allPointCombinations.push_back(pointCombination);
            }
        }
    }

    return allPointCombinations;
}

QString Board::pointsToString(const PointList &points)
{
    QString str;
    for (Point point : points) {
        str += QString(letterAt(point));
    }
    return str;
}
QStringList Board::findAllValidStrings(const int &minLength, const int &maxLength)
{
    int depth = maxLength;
    if (maxLength < 0) {
        depth = m_gridSize * m_gridSize;
    }

    QStringList validStrings;
    for (PointList &pointCombination : getAllPointCombinations(depth)) {
        if (pointCombination.length() >= minLength) {
            validStrings << pointsToString(pointCombination);
        }
    }

    return validStrings;
}



















