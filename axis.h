#ifndef AXIS_H
#define AXIS_H

#include <QObject>
#include <QPainter>
#include <QPen>
#include <QString>
#include <QDebug>
#include <QDateTime>

class Axis : public QObject
{
    Q_OBJECT
public:
    explicit Axis(int x, int y, int w, int h, QObject *parent = 0);

    void drawXaxis(QPainter *painter); //rysuje os X
    void drawYaxis(QPainter *painter); //rysuje os Y

    void setDefaultLineProperties(); //ustawia poczatkowe opcje osi.
    void showAxis(QPainter *painter); //pokazuje obie osie

    void setGeometry(int x, int y, int w, int h);
    void setYaxisProperties();
    void setYaxisAutoScale();

private:

    int graph_x;
    int graph_y;
    int graph_w;
    int graph_h;

    QPen axisLineProperties;

    int startPointX; //punkt w ktorym zaczyna sie canvas
    int startPointY; //punkt w ktorym zaczyna sie canvas

    double xMin; //wartosc minimalna osi x
    double xMax; //wartosc maksymalna osi x

    double yMin; //wartosci minimalne i maksymalne na wykresie
    double yMax;

    int xUnits; //odstęp między jednostkami na osi x
    int yUnits; //odstęp między jednostkami na osi y

    double YaxisMax; //wartosci minimalne i makxymalne na osi Y
    double YaxisMin;

    bool visibleX; //flaga mowiaca o tym czy obiekt osi X jest narysowany
    bool visibleY; //flaga mowiaca o tym czy obiekt osi Y jest narysowany

    QVector<long long int> x_data_list;
    QVector<QVector<float> > y_data_list;

protected slots:

    void getMinMax(double x_min, double x_max, double y_min, double y_max);
    void setLineData(QVector<long long int> x_data, QVector<QVector<float> > y_data);

signals:

    void unitsSetted(double xUnits, double yUnits);
};

#endif // AXIS_H
