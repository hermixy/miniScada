#ifndef GRID_H
#define GRID_H

#include <QObject>
#include <QPainter>
#include <QPen>
#include <QDebug>

class Grid : public QObject
{
    Q_OBJECT
public:
    explicit Grid(int x, int y, int w, int h, QObject *parent = 0);

    int getXGridDensity() const;
    void setXGridDensity(double value);

    int getYGridDensity() const;
    void setYGridDensity(double value);

    void drawGrid(QPainter *painter);

    QPen getGridLineProperties() const;
    void setGridLineProperties();

    void drawXgridLine(QPainter *painter);
    void drawYgridLine(QPainter *painter);

    void setGeometry(int x, int y, int w, int h);

private:
    int graph_x;
    int graph_y;
    int graph_w;
    int graph_h;

    int xGridDensity;
    int yGridDensity;

    bool visible; //flaga informujaca o tym czy siatka jest widoczna.

protected slots:

    void setDensitiy(double xDensity, double yDensity);
};

#endif // GRID_H
