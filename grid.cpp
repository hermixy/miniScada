#include "grid.h"

Grid::Grid(int x, int y, int w, int h, QObject *parent) : QObject(parent)
{
    graph_x = x;
    graph_y = y;
    graph_w = w;
    graph_h = h;

    xGridDensity = 50;
    yGridDensity = 50;
    setGridLineProperties();
}

int Grid::getXGridDensity() const
{
    return xGridDensity;
}

void Grid::setXGridDensity(double value)
{
    xGridDensity = value;
}
int Grid::getYGridDensity() const
{
    return yGridDensity;
}

void Grid::setYGridDensity(double value)
{
    yGridDensity = value;
}

void Grid::drawGrid(QPainter *painter)
{
    painter->setPen(gridLineProperties);
    drawXgridLine(painter);
    drawYgridLine(painter);

    visible = true;
}
QPen Grid::getGridLineProperties() const
{
    return gridLineProperties;
}

void Grid::setGridLineProperties()
{

}

void Grid::drawXgridLine(QPainter *painter)
{
    for(int x = xGridDensity + graph_x; x <= graph_w + graph_x; x+= xGridDensity)
    {
        painter->drawLine(x, graph_y , x, graph_w + graph_y);
    }
}

void Grid::drawYgridLine(QPainter *painter)
{
    for(int y = yGridDensity; y <= graph_h + graph_y; y += yGridDensity)
    {
        painter->drawLine(graph_x, y + graph_y, graph_h + graph_x, y + graph_y);
    }
}

void Grid::setGeometry(int x, int y, int w, int h)
{
    graph_x = x;
    graph_y = y;
    graph_w = w;
    graph_h = h;
}

void Grid::setDensitiy(double xDensity, double yDensity)
{
    xGridDensity = xDensity;
    yGridDensity = yDensity;
}



