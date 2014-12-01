#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QTimer>
#include <QDebug>
#include <QMouseEvent>
#include <QWheelEvent>


#include "canvas.h"
#include "axis.h"
#include "line.h"
#include "grid.h"

class Graph : public QWidget
{
    Q_OBJECT

public:
    explicit Graph(int x, int y, int w, int h, QWidget *parent = 0);
    ~Graph();

    void paintEvent(QPaintEvent *);
    void setGeometry(int x, int y, int w, int h);
    void setCanvasVisible();

    void setLineData(QVector<int> &x,QVector<QVector<float> > &y);
    Line* getLine();
    Axis* getAxis();

    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void wheelEvent(QWheelEvent *ev);

    bool getShiftPressed() const;
    void setShiftPressed(bool value);

protected slots:

    void UpdateGraph();

    void axisOff();
    void axisOn();

    void axisSetXunits();
    void axisSetYunits();

    void gridOff();
    void gridOn();

    void gridSetXdensity();
    void gridSetYdensity();

private:
    QPainter *painter;
    QPen frameLine; //odpowiada za obramowanie wykresu

    QTimer *refreshTimer; //odswierzanie - czestosc dorysowywania danych
    QPoint mouseMovePoint; //koordynaty dla eventu move myszy
    QPoint mousePressPoint; //koordynaty dla eventu press myszy
    QPoint mouseReleasePoint; //koordynaty dla eventu release myszy

    Canvas *canvas; //tlo wykresu
    Grid *grid; //siatka wykresu
    Axis *axis; //osie wykresu
    Line *line; //obiekt linie;

    int refreshFrequency; //czestosc odswierzania wykresu

    bool need_update_canvas;
    bool need_update_axis;
    bool need_update_grid;
    bool need_update_line;

    bool visible_canvas;
    bool visible_axis;
    bool visible_grid;
    bool visible_line;

    int graph_x;
    int graph_y;
    int graph_w;
    int graph_h;

    int _x;
    int _y;

    bool shiftPressed;
};

#endif // GRAPH_H
