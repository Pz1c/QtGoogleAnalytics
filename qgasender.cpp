#include "qgasender.h"

QGASender::QGASender(QObject *parent) : QObject(parent) {
    _requestIdx = 0;
}

void QGASender::saveRequest(QString &data) {
#ifdef QT_DEBUG
    QString file_name = QString("qa_request_%1.html").arg(QString::number(++_requestIdx));
    QFile file(file_name);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << _postData;
    out << endl << endl;
    out << data;
    file.close();
    qDebug() << "data stored into " << file_name;
#endif
}

void QGASender::slotReadyRead() {
    QNetworkReply *reply = (QNetworkReply *)sender();
    if (reply->error() != QNetworkReply::NoError) {
        return;
    }
	
    //QString url = reply->url().toString();
    QString data = reply->readAll();
    //qDebug() << "from url: " << url << " QGASender::slotReadyRead";
    if (!data.isEmpty()) {
        saveRequest(data);
    }

    emit finishSuccessfully();
}

void QGASender::slotError(QNetworkReply::NetworkError error) {
    qDebug() << "QGASender::slotError" << error << _reply->errorString();
    emit finishError();
}

void QGASender::slotSslErrors(QList<QSslError> error_list) {
    qDebug() << "QGASender::slotSslErrors " << error_list;
    emit finishError();
}

void QGASender::setPostData(const QByteArray &postData)
{
    _postData = postData;
}

void QGASender::setProxySettings(QString IP, int Port, QString Username, QString Password) {
    _proxyHost = IP;
    _proxyPort = Port;
    _proxyUser = Username;
    _proxyPass = Password;
    applyProxySettings();
}

void QGASender::applyProxySettings() {
    qDebug() << "QGASender::applyProxySettings" << _proxyHost << _proxyPort;
    if (_proxyHost.isEmpty()) {
        _nam.setProxy(QNetworkProxy::NoProxy);
    } else {
        _proxy.setType(QNetworkProxy::HttpProxy);
        _proxy.setHostName(_proxyHost);
        _proxy.setPort(_proxyPort);
        if (!_proxyUser.isEmpty()) {
            _proxy.setUser(_proxyUser);
        }
        if (!_proxyPass.isEmpty()) {
            _proxy.setPassword(_proxyPass);
        }
        _nam.setProxy(_proxy);
    }
}

void QGASender::send() {
    //qDebug() << "QGASender::send()";
    QNetworkRequest request;
    request.setUrl(QUrl(QString("https://www.google-analytics.com/batch")));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    _reply = _nam.post(request, _postData);
    connect(_reply, SIGNAL(finished()), this, SLOT(slotReadyRead()));
    connect(_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(slotError(QNetworkReply::NetworkError)));
    connect(_reply, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(slotSslErrors(QList<QSslError>)));
}
