#include "canvas.h"
#include "graph.h"

Canvas::Canvas(int x, int y, int w, int h, QObject *parent) :
    QObject(parent)
{
    graph_x = x;
    graph_y = y;

    graph_h = w;
    graph_w = h;
}

void Canvas::drawCanvas(QPainter *painter, void *parent)
{
    setCanvasBrushDefaultProperties();
    setCanvasFrameLineDefaultProperties();

    painter->setPen(canvasFrameLine);
    painter->setBrush(canvasBrush);

    if(parent)
    {
        Graph *p_parent = (Graph*) parent;
        p_parent->setCanvasVisible();
    }

    painter->drawRect(graph_x, graph_y , graph_w, graph_h);
}

void Canvas::setCanvasFrameLineDefaultProperties()
{
    canvasFrameLine.setColor(Qt::white);
    canvasFrameLine.setWidth(1);
}

void Canvas::setCanvasBrushDefaultProperties()
{
    canvasBrush.setColor(Qt::white);
    canvasBrush.setStyle(Qt::SolidPattern);
}

void Canvas::setGeometry(int x, int y, int w, int h)
{
    graph_x = x;
    graph_y = y;
    graph_w = w;
    graph_h = h;
}

