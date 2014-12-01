#include "line.h"

Line::Line(int x, int y, int w, int h, QObject *parent) :
    QObject(parent)
{
    graph_x = x;
    graph_y = y;

    graph_h = w;
    graph_w = h;

    //Set line properties, move to method
    lineStyle = Qt::DashDotDotLine;
    lineCapStyle = Qt::RoundCap;
    lineJoinStyle = Qt::RoundJoin;
    lineWidth = 2;
    lineColor = Qt::red;

    linePen.setColor(lineColor);
    linePen.setStyle(lineStyle);
    linePen.setCapStyle(lineCapStyle);
    linePen.setJoinStyle(lineJoinStyle);
    linePen.setWidth(lineWidth);

    m.translate(20, graph_h + 20); //przesuwa wykres w miejsce osi Y.
    m.scale(1, -1); //zamienia wspolrzedne na typowy układ kartezjański.

    //po tych operacjach początek układu współrzędnych stanowi przecięcie osi X i Y.

    scaleX = 1;
    scaleY = 1;
}

void Line::DrawLine(QPainter *painter)
{
    if(x_data_list.size() > 0 && y_data_list.size() > 0)
    {
        painter->setWorldTransform(m);
        stroke = stroker.createStroke(path);
        painter->strokePath(path, linePen);
    }
}

//TODO change this to STL ?? it can be used also for flaot type
void Line::getXminMax()
{
    min_x = x_data_list.at(0);
    max_x = x_data_list.at(0);

    foreach (int var, x_data_list)
    {
        if(var > max_x) max_x = var;
        if(var < min_x) min_x = var;
    }
}

void Line::getYminMax()
{
    min_y = y_data_list.at(0).at(1);
    max_y = y_data_list.at(0).at(1);

    float var;
    for(int i = 0; i < y_data_list.size(); i++)
    {
            var = y_data_list.at(i).at(1);
            if(var > max_y) max_y = var;
            if(var < min_y) min_y = var;
    }
}

void Line::SetColor(QColor col)
{
    lineColor = col;
    linePen.setColor(col);
}

void Line::SetLineWidth(int width)
{
    stroker.setWidth(width);
    linePen.setWidth(width);
}

void Line::SetLineStyle(Qt::PenStyle style)
{
    linePen.setStyle(style);
}

void Line::MoveLine(int x, int y)
{
    if(m.dx() - x >= 20) m.translate(-x, y);
}

void Line::SetDefaultScale()
{
    dx = max_x - min_x;
    x_interval = dx / 500;

    dy = max_y - min_y;
    y_interval = dy / 500;
}

void Line::RedrawLine()
{
    QPainterPath p;
    path = p;

    path.moveTo(x_data_list.at(0), y_data_list.at(0).at(1));
    for (int i = 0; i < x_data_list.size() - 1; i++)
    {
        path.lineTo(x_data_list.at(i), y_data_list.at(i).at(1));
    }
}

void Line::SetScale(float scaleX, float scaleY)
{
    this->scaleX = scaleX;
    this->scaleY = scaleY;

    for(int i = 0; i < x_data_list.size() - 1; i++)
    {
        x_data_list[i] = x_data_list[i] * scaleX;
        y_data_list[i][1] = y_data_list[i].at(1) * scaleY;
    }

    RedrawLine();
}

float Line::GetXscale()
{
    return scaleX;
}

float Line::GetYscale()
{
    return scaleY;
}

void Line::setLineData(QVector<long long> x_data, QVector<QVector<float> > y_data)
{
    static int inv = 0;

    x_data_list = x_data;
    y_data_list = y_data;

    getXminMax();
    getYminMax();

    emit minMaxValues(min_x, max_x, min_y, max_y);
    SetDefaultScale();

    for(int i = 0; i < x_data_list.size() - 1; i++)
    {
        x_data_list[i] = (x_data_list[i] - min_x) / x_interval;
        y_data_list[i][1] = (y_data_list[i][1] - min_y) / y_interval;
    }

    if(inv == 0)
    {
        path.moveTo(x_data_list.at(0), y_data_list.at(0).at(1));
        for (int i = 0; i < x_data_list.size() - 1; i++)
        {
            path.lineTo(x_data_list.at(i), y_data_list.at(i).at(1));
        }
    }

    inv++;
}
