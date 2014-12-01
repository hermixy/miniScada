#include "axis.h"

Axis::Axis(int x, int y, int w, int h, QObject *parent) :
    QObject(parent)
{
    graph_x = x;
    graph_y = y;
    graph_w = w;
    graph_h = h;

    xUnits = 50;
    yUnits = 50;

    xMin = float(graph_x);
    xMax = float (graph_x + graph_w);

    yMin = float(graph_y);
    yMax = float(graph_y + graph_h);
}

void Axis::showAxis(QPainter *painter)
{
    setDefaultLineProperties();
    painter->setPen(axisLineProperties);

    drawXaxis(painter);
    drawYaxis(painter);
}

void Axis::setGeometry(int x, int y, int w, int h)
{
    graph_x = x;
    graph_y = y;
    graph_w = w;
    graph_h = h;
}

void Axis::setYaxisProperties()
{
    double _scYmax = qRound(yMax / yUnits) * yUnits;
    if(_scYmax < yMax) _scYmax = _scYmax + yUnits;

    double _scYmin = qRound(yMin / yUnits) * yUnits;
    if(_scYmin > yMin) _scYmin = _scYmin - yUnits;

    YaxisMax = _scYmax;
    YaxisMin = _scYmin;
}

/**
 * @brief Axis::setYaxisAutoScale
 * Funkcja automatycznie dobiera warość zmiennej yUnits do danych na wykresie tak aby siatka
 * nie zawierała domyślnie więcej niż 10 linii.
 */
void Axis::setYaxisAutoScale()
{
    double temp  = (yMax - yMin) / 10;

    if (temp >= 1 && temp <= 10)
    {
        yUnits = 10;
    }
    else if(temp > 10 && temp <= 50)
    {
        yUnits = 50;
    }
    else if(temp > 50 && temp <= 100)
    {
        yUnits = 100;
    }
    else if(temp > 100 && temp <= 200)
    {
        yUnits = 200;
    }
    else if(temp > 200 && temp <= 500)
    {
        yUnits = 500;
    }
    else if(temp > 500 && temp <= 1000)
    {
        yUnits = 1000;
    }
    else if(temp > 1000 && temp <= 1500)
    {
        yUnits = 1500;
    }
    else if(temp > 1500 && temp <= 2000)
    {
        yUnits = 1500;
    }
}

void Axis::getMinMax(double x_min, double x_max, double y_min, double y_max)
{
    xMin = x_min;
    xMax = x_max;
    yMin = y_min;
    yMax = y_max;
}

void Axis::setLineData(QVector<long long> x_data, QVector<QVector<float> > y_data)
{
    x_data_list = x_data;
    y_data_list = y_data;
}

void Axis::drawXaxis(QPainter *painter)
{
    painter->drawLine(graph_x,graph_y + graph_h, graph_x + graph_w, graph_y +graph_h);
    int div = xMax - xMin;
    double dt = div/10;

    int idx = 0;

    for(int i = 0 ; i <= graph_w ; i += xUnits)
    {
        painter->drawLine(i + graph_x, graph_h + graph_y + 5, i + graph_x, graph_h + graph_y - 10);

        QTime time = QTime::fromMSecsSinceStartOfDay((xMin + idx) * 1000);
        QString t_str = time.toString("hh:mm");
        idx += 720;
        painter->drawText(i + graph_x, graph_h + graph_y + 15, t_str);
    }

    idx = 0;
    visibleX = true;
}

void Axis::drawYaxis(QPainter *painter)
{
    setYaxisAutoScale();
    setYaxisProperties();

    double idx = 0;
    int lines = (YaxisMax - YaxisMin) / yUnits;
    double space = graph_h / lines;

    painter->drawLine(graph_x,graph_y, graph_x, graph_y + graph_h);
    for(int i = 0; i <= graph_h; i += space)
    {
        QString label = QString::number(YaxisMin + idx);
        painter->drawText(graph_x - 20, graph_h - i + graph_y, label);
        idx += yUnits;
    }

    idx = 0;
    visibleY = true;

    emit unitsSetted(xUnits, space);
}

void Axis::setDefaultLineProperties()
{
    axisLineProperties.setColor(Qt::black);
    axisLineProperties.setStyle(Qt::SolidLine);
    axisLineProperties.setWidth(2);
}
