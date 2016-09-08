#ifndef QGASENDER_H
#define QGASENDER_H

#include <QObject>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QTextStream>
#include <QNetworkProxy>

class QGASender : public QObject
{
    Q_OBJECT
public:
    explicit QGASender(QObject *parent = 0);
    void setProxySettings(QString IP, int Port, QString Username, QString Password);
    void setPostData(const QByteArray &postData);

public slots:
    void send();

signals:
    void finishSuccessfully();
    void finishError();

protected slots:

    // NAT
    void slotReadyRead();
    void slotError(QNetworkReply::NetworkError error);
    void slotSslErrors(QList<QSslError> error_list);

private:
    // data
    QByteArray _postData;

    // proxy
    QString _proxyHost;
    int _proxyPort;
    QString _proxyUser;
    QString _proxyPass;

    // network
    bool _isLoading;
    int _requestIdx;
    QNetworkAccessManager _nam;
    QNetworkReply *_reply;
    QNetworkProxy _proxy;

    void applyProxySettings();
    void saveRequest(QString &data);
};

#endif // QGASENDER_H
