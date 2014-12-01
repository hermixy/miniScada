#include "datadownloader.h"

DataDownloader::DataDownloader(QObject *parent) :
    QObject(parent)
{
    connect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(downloadFinished(QNetworkReply*)));
}

void DataDownloader::startDownload()
{
    QUrl url("http://www.swpc.noaa.gov/ftpdir/lists/ace/ace_swepam_1m.txt");
    downloadFile(url);

    //qDebug() << __FILE__ << __LINE__ << __func__ ;
}

void DataDownloader::downloadFile(const QUrl &url)
{
    QNetworkRequest request(url);
    QNetworkReply *reply = manager.get(request);

#ifndef QT_NO_SSL
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)), SLOT(sslError(QList<QSslError>)));
#endif

    currentDownloads.append(reply);
}

void DataDownloader::sslError(const QList<QSslError> &sslErrors)
{
#ifndef QT_NO_SSL
    foreach(const QSslError &error, sslErrors)
    {
        fprintf(stderr, "SSL error: %s\n", qPrintable(error.errorString()));
    }
#else
    Q_UNUSED(sslError)
#endif
}

void DataDownloader::saveFile(const QString &filename, QIODevice *data)
{
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly))
    {
        fprintf(stderr, "Cannot save the file %s \n", qPrintable(filename), qPrintable(file.errorString()));
    }

    file.write(data->readAll());
    file.close();
}

QString DataDownloader::getFileName(const QUrl &url)
{
    QString path = url.path();
    QString name = QFileInfo(path).fileName();

    return name;
}

void DataDownloader::downloadFinished(QNetworkReply *reply)
{
    QUrl url = reply->url();
    if(reply->error())
    {
        fprintf(stderr, "Download %s failed", url.toEncoded().constData(), qPrintable(reply->errorString()));
    }
    else
    {
        QString filename = getFileName(url);
        saveFile(filename, reply);
    }

    currentDownloads.removeAll(reply);
    reply->deleteLater();

    emit fileDownloaded();
}
