#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>

//for qsrand - will be removed later
#include <QTime>
#include <QDebug>
#include <QTimer>
#include <QKeyEvent>

#include "graph.h"
#include "datadownloader.h"
#include "filereader.h"
#include "line.h"

#
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void setGeometry(int x, int y, int w, int h);
    void keyPressEvent(QKeyEvent *ev);
    void keyReleaseEvent(QKeyEvent *ev);

private slots:
    void on_LineColor_activated(const QString &arg1);

    void on_pushButton_Stop_clicked();

    void on_pushButton_Start_clicked();

    void on_radioButton_XmaxConst_toggled(bool checked);

    void on_radioButton_XmaxAuto_toggled(bool checked);

    void on_radioButton_XminAuto_toggled(bool checked);

    void on_radioButton_XminConst_toggled(bool checked);

    void on_radioButton_XUnitAuto_toggled(bool checked);

    void on_radioButton_XUnitConst_toggled(bool checked);

    void on_radioButton_YmaxAuto_toggled(bool checked);

    void on_radioButton_YmaxConst_toggled(bool checked);

    void on_radioButton_YminAuto_toggled(bool checked);

    void on_radioButton_YminConst_toggled(bool checked);

    void on_radioButton_YunitAuto_toggled(bool checked);

    void on_radioButton_YUnitConst_toggled(bool checked);

    void on_XGridOn_stateChanged(int arg1);

    void on_yGridOn_stateChanged(int arg1);

    void on_radioButton_XgridAuto_toggled(bool checked);

    void on_radioButton_XGrdiConst_toggled(bool checked);

    void on_radioButton_YGridAuto_toggled(bool checked);

    void on_radioButton_YGridConst_toggled(bool checked);

    void on_LineWidth_valueChanged(int arg1);

    void on_pushButton_ZoomIn_clicked();

    void on_pushButton_ZoomOut_clicked();

    void on_LineType_activated(int index);

private:
    int graph_x;
    int graph_y;
    int graph_w;
    int graph_h;

    Ui::Widget *ui;

    Graph *graph; //widget rysujacy wykres na swoim rodzicu

    QTimer *downloaderTimer;

    DataDownloader downloader;
    FileReader reader;
};

#endif // WIDGET_H
