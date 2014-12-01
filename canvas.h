#ifndef CANVAS_H
#define CANVAS_H

#include <QObject>
#include <QPainter>
#include <QDebug>

class Canvas : public QObject
{
    Q_OBJECT
public:
    explicit Canvas(int x, int y, int w, int h, QObject *parent = 0);

    void drawCanvas(QPainter *painter, void *parent);
    void setCanvasFrameLineDefaultProperties();
    void setCanvasBrushDefaultProperties();

    void setGeometry(int x, int y, int w, int h);

private:

    int graph_x;
    int graph_y;
    int graph_w;
    int graph_h;

    QPen canvasFrameLine;
    QBrush canvasBrush;

};

#endif // CANVAS_H
