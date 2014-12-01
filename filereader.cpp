#include "filereader.h"

FileReader::FileReader(QObject *parent) :
    QObject(parent)
{
    //
}

void FileReader::startReadData()
{
    QFile file("ace_swepam_1m.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream fileStream(&file);
    QString str;
    ready = false;
    QVector<QStringList> fileData;

    do {
        str = fileStream.readLine();
        QStringList splitedStr = str.split(" ", QString::SkipEmptyParts);
        fileData.append(splitedStr);
    } while (!fileStream.atEnd());

    if(x_data_list.empty() && y_data_list.empty())
    {
        //kopiuje wszystko od 14 linii w gore
        for(int i = 18; i < fileData.size(); i++)
        {
            if(fileData.at(i).at(6).toInt() == 0)
            {
                QVector<float> lines;
                x_data_list.append(fileData.at(i).at(5).toInt());
                lines.append(fileData.at(i).at(7).toFloat());
                lines.append(fileData.at(i).at(8).toFloat());
                lines.append(fileData.at(i).at(9).toFloat());
                y_data_list.append(lines);
            }
        }
    }
    else if(!x_data_list.empty() && !y_data_list.empty())
    {
        if(fileData.at(fileData.size() - 2).at(6).toInt() == 0)
        {
            QVector<float> line;
            x_data_list.append(fileData.at(fileData.size() - 2).at(5).toInt());
            line.append(fileData.at(fileData.size() - 2).at(7).toFloat());
            line.append(fileData.at(fileData.size() - 2).at(8).toFloat());
            line.append(fileData.at(fileData.size() - 2).at(9).toFloat());
            y_data_list.append(line);
        }
    }
    fileData.clear();

    emit(dataReady(x_data_list, y_data_list));
    file.close();
}

QVector<long long int> FileReader::getXdata(void)
{
    return x_data_list;
}

QVector<QVector<float> > FileReader::getYdata(void)
{
    return y_data_list;
}

bool FileReader::checkState()
{
    return ready;
}
