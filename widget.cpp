#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->resize(800, 600);

    //graph initiazliation
    graph = new Graph(20, 20, 500, 500, ui->widget);
    graph->move(20, 20);
    graph->resize(520, 600);

    //Todo : Remove this when data from server reading will be completed
    QTime time;
    qsrand((uint)time.msec());

    //downloader initialization
    downloaderTimer = new QTimer(this);
    downloaderTimer->start(30 * 60);
    downloader.startDownload();

    //TODO set groups of qRadioButtons using QButtonGroup
    QButtonGroup *gr1 = new QButtonGroup(this);
    gr1->addButton(ui->radioButton_XmaxAuto);
    gr1->addButton(ui->radioButton_XmaxConst);

    QButtonGroup *gr2 = new QButtonGroup(this);
    gr2->addButton(ui->radioButton_XGrdiConst);
    gr2->addButton(ui->radioButton_XgridAuto);

    QButtonGroup *gr3 = new QButtonGroup(this);
    gr3->addButton(ui->radioButton_XminAuto);
    gr3->addButton(ui->radioButton_XminConst);

    QButtonGroup *gr4 = new QButtonGroup(this);
    gr4->addButton(ui->radioButton_XUnitAuto);
    gr4->addButton(ui->radioButton_XUnitConst);

    QButtonGroup *gr5 = new QButtonGroup(this);
    gr5->addButton(ui->radioButton_YGridAuto);
    gr5->addButton(ui->radioButton_YGridConst);

    QButtonGroup *gr6 = new QButtonGroup(this);
    gr6->addButton(ui->radioButton_YmaxAuto);
    gr6->addButton(ui->radioButton_YmaxConst);

    QButtonGroup *gr7 = new QButtonGroup(this);
    gr7->addButton(ui->radioButton_YminAuto);
    gr7->addButton(ui->radioButton_YminConst);

    QButtonGroup *gr8 = new QButtonGroup(this);
    gr8->addButton(ui->radioButton_YunitAuto);
    gr8->addButton(ui->radioButton_YUnitConst);

    //Signals and slots connections
    connect(downloaderTimer, SIGNAL(timeout()), &downloader, SLOT(startDownload()));
    connect(&downloader, SIGNAL(fileDownloaded()) , &reader, SLOT(startReadData()));
    connect(&reader, SIGNAL(dataReady(QVector<long long int>,QVector<QVector<float> >)), graph->getLine(), SLOT(setLineData(QVector<long long int>,QVector<QVector<float> >)));
    connect(&reader, SIGNAL(dataReady(QVector<long long int>,QVector<QVector<float> >)), graph->getAxis(), SLOT(setLineData(QVector<long long int>,QVector<QVector<float> >)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key() == Qt::Key_Shift)
    {
        qDebug() << __FILE__ << __LINE__ << __func__  ;
        graph->setShiftPressed(true);
    }
    else
    {
        qDebug() << __FILE__ << __LINE__ << __func__  ;
        graph->setShiftPressed(false);
    }
}

void Widget::keyReleaseEvent(QKeyEvent *ev)
{
    if(ev->key() == Qt::Key_Shift)
    {
        qDebug() << __FILE__ << __LINE__ << __func__  ;
        graph->setShiftPressed(false);
    }
}

void Widget::on_LineColor_activated(const QString &arg1)
{
    if(!arg1.compare("Niebieski"))
    {
        graph->getLine()->SetColor(Qt::blue);
    }
    else if(!arg1.compare("Czerwony"))
    {
        graph->getLine()->SetColor(Qt::red);
    }

    update();
}

void Widget::on_pushButton_Stop_clicked()
{

}

void Widget::on_pushButton_Start_clicked()
{

}

void Widget::on_radioButton_XmaxConst_toggled(bool checked)
{

}

void Widget::on_radioButton_XmaxAuto_toggled(bool checked)
{

}

void Widget::on_radioButton_XminAuto_toggled(bool checked)
{

}

void Widget::on_radioButton_XminConst_toggled(bool checked)
{

}

void Widget::on_radioButton_XUnitAuto_toggled(bool checked)
{

}

void Widget::on_radioButton_XUnitConst_toggled(bool checked)
{

}


void Widget::on_radioButton_YmaxAuto_toggled(bool checked)
{

}

void Widget::on_radioButton_YmaxConst_toggled(bool checked)
{

}

void Widget::on_radioButton_YminAuto_toggled(bool checked)
{

}


void Widget::on_radioButton_YminConst_toggled(bool checked)
{

}



void Widget::on_radioButton_YunitAuto_toggled(bool checked)
{

}

void Widget::on_radioButton_YUnitConst_toggled(bool checked)
{

}

void Widget::on_XGridOn_stateChanged(int arg1)
{

}

void Widget::on_yGridOn_stateChanged(int arg1)
{

}

void Widget::on_radioButton_XgridAuto_toggled(bool checked)
{

}

void Widget::on_radioButton_XGrdiConst_toggled(bool checked)
{

}

void Widget::on_radioButton_YGridAuto_toggled(bool checked)
{

}

void Widget::on_radioButton_YGridConst_toggled(bool checked)
{

}

void Widget::on_LineWidth_valueChanged(int arg1)
{
    graph->getLine()->SetLineWidth(arg1);
    update();
}

void Widget::on_pushButton_ZoomIn_clicked()
{

}

void Widget::on_pushButton_ZoomOut_clicked()
{

}

void Widget::on_LineType_activated(int index)
{
    switch (index) {
    case 0:
        graph->getLine()->SetLineStyle(Qt::SolidLine);
        break;
    case 1:
        graph->getLine()->SetLineStyle(Qt::DashLine);
        break;
    case 2:
        graph->getLine()->SetLineStyle(Qt::DashDotLine);
        break;
    case 3:
        graph->getLine()->SetLineStyle(Qt::DashDotDotLine);
        break;
    case 4:
        graph->getLine()->SetLineStyle(Qt::DotLine);
        break;
    default:
        break;
    }
    update();
}
