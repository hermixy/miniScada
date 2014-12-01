#ifndef DATADOWNLOADER_H
#define DATADOWNLOADER_H

#include <QObject>
#include <QtNetwork>
#include <QFile>

class QString;

class DataDownloader : public QObject
{
    Q_OBJECT
public:
    explicit DataDownloader(QObject *parent = 0);
    void downloadFile(const QUrl &url);
    QString getFileName(const QUrl &url);
    void saveFile(const QString &filename, QIODevice *data);

private:
    QNetworkAccessManager manager;
    QList<QNetworkReply *> currentDownloads;

public slots:
    void startDownload();
    void downloadFinished(QNetworkReply *reply);
    void sslError(const QList<QSslError> &sslErrors);

signals:
    void fileDownloaded(void);
};

#endif // DATADOWNLOADER_H
