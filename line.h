#ifndef LINE_H
#define LINE_H

#include <QObject>
#include <QVector>
#include <QPointF>
#include <QPainter>
#include <QPalette>
#include <QDebug>
#include <QTime>
#include <QPen>

class Line : public QObject
{
    Q_OBJECT
public:
    explicit Line(int x, int y, int w, int h, QObject *parent = 0);

    void DrawLine(QPainter *painter);

    void getXminMax();
    void getYminMax();

    void SetColor(QColor col);
    void SetLineWidth(int width);
    void SetLineStyle(Qt::PenStyle style);
    void MoveLine(int x, int y);
    void SetDefaultScale();
    void RedrawLine();
    void SetScale(float scaleX, float scaleY);
    float GetXscale(void);
    float GetYscale(void);

private:

    QVector<long long int> x_data_list;
    QVector<QVector<float> > y_data_list;

    QPainterPath path;
    QPainterPathStroker stroker;
    QPainterPath stroke;

    //Line properties
    QPen linePen;
    QColor lineColor;
    Qt::PenStyle lineStyle;
    Qt::PenCapStyle lineCapStyle;
    Qt::PenJoinStyle lineJoinStyle;
    int lineWidth;

    QBrush lineBrush;

    QTransform m;

    bool ready;

    int graph_x;
    int graph_y;
    int graph_w;
    int graph_h;

    double min_x;
    double max_x;

    double min_y;
    double max_y;

    double ax;
    double ay;

    int x_interval;
    int dx;

    float y_interval;
    float dy;

    float scaleX;
    float scaleY;


protected slots:

    void setLineData(QVector<long long int> x_data, QVector<QVector<float> > y_data);

signals:

    void minMaxValues(double x_min, double x_max, double y_min, double y_max);
};

#endif // LINE_H
