#ifndef FILEREADER_H
#define FILEREADER_H

#include <QObject>
#include <QFile>
#include <QDebug>

class FileReader : public QObject
{
    Q_OBJECT
public:
    explicit FileReader(QObject *parent = 0);
    QVector<long long int> getXdata(void);
    QVector<QVector<float> > getYdata(void);

    bool checkState();

private:
    QVector<long long int> x_data_list;
    QVector<QVector<float> > y_data_list;
    bool ready;

protected slots:
    void startReadData(void);

signals:
    void dataReady(QVector<long long int> x_data, QVector<QVector<float> > y_data);
};

#endif // FILEREADER_H
