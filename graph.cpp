#include "graph.h"

Graph::Graph(int x, int y, int w , int h, QWidget *parent) :
    QWidget(parent)
{
    painter = new QPainter;

    graph_x = x;
    graph_y = y;
    graph_w = w;
    graph_h = h;

    _x = 0;
    _y = 0;

    canvas = new Canvas(x, y ,w, h, this);
    axis = new Axis(x, y, w, h, this);
    line = new Line(x, y, w, h, this);
    grid = new Grid(x, y, w ,h, this);

    refreshFrequency = 1000;

    //funkcje timera
    refreshTimer = new QTimer(this);

    connect(refreshTimer, SIGNAL(timeout()), this, SLOT(UpdateGraph()));
    connect(line, SIGNAL(minMaxValues(double,double,double,double)), axis, SLOT(getMinMax(double,double,double,double)));
    connect(axis, SIGNAL(unitsSetted(double,double)), grid, SLOT(setDensitiy(double,double)));

    refreshTimer->start(refreshFrequency);
}

Graph::~Graph()
{
    delete axis;
    delete painter;
}


void Graph::paintEvent(QPaintEvent *e)
{
    painter->begin(this);
    canvas->drawCanvas(painter, this);
    axis->showAxis(painter);
    grid->drawGrid(painter);
    line->DrawLine(painter);

    painter->end();
}

void Graph::setGeometry(int x, int y, int w, int h)
{
    graph_x = x;
    graph_y = y;
    graph_w = w;
    graph_h = h;
}

void Graph::UpdateGraph()
{
    update();
}

void Graph::axisOff()
{

}

void Graph::axisOn()
{

}

void Graph::axisSetXunits()
{

}

void Graph::axisSetYunits()
{

}

void Graph::gridOff()
{

}

void Graph::gridOn()
{

}

void Graph::gridSetXdensity()
{

}

void Graph::gridSetYdensity()
{

}
bool Graph::getShiftPressed() const
{
    return shiftPressed;
}

void Graph::setShiftPressed(bool value)
{
    shiftPressed = value;
}


void Graph::setCanvasVisible()
{
    visible_canvas = true;
}

Line* Graph::getLine()
{
    return line;
}

Axis * Graph::getAxis()
{
    return axis;
}

void Graph::mouseMoveEvent(QMouseEvent *ev)
{
    int dx, dy;

    mouseMovePoint.setX(ev->x());
    mouseMovePoint.setY(ev->y());

    //inicjalizacja zmiennych
    if(_x == 0 && _y == 0)
    {
        _x = ev->x();
        _y = ev->y();
    }

    dx = _x - ev->x();
    dy = _y - ev->y();

    _x = ev->x();
    _y = ev->y();

    qDebug() << __FILE__ << __LINE__ << __func__ << _x << _y ;

    line->MoveLine(dx, dy);
    update();
}

void Graph::mousePressEvent(QMouseEvent *ev)
{
    mousePressPoint.setX(ev->x());
    mousePressPoint.setY(ev->y());
}

void Graph::mouseReleaseEvent(QMouseEvent *ev)
{
    mouseReleasePoint.setX(ev->x());
    mouseReleasePoint.setY(ev->y());

    _x = 0;
    _y = 0;
}

void Graph::wheelEvent(QWheelEvent *ev)
{
    float scX, scY;

    scX = line->GetXscale();
    scY = line->GetYscale();

    if(shiftPressed == true)
    {
        if(ev->delta() > 0) scY = scY - 0.1;
        else scY = scY + 0.1;
        line->SetScale(scX, scY);
    }
    else
    {
        if(ev->delta() > 0 ) scX = scX - 0.1;
        else scX = scX + 0.1;

        line->SetScale(scX, scY);
    }
}

