#ifndef QGOOGLEANALYTICS_H
#define QGOOGLEANALYTICS_H

#include <QObject>
#include <QDebug>
#include <QSettings>
#include <QList>
#include <QPair>
#include <QUuid>
#include <QTimer>
#include <QQmlEngine>
#include <QJSEngine>
#include <QThread>
#include <QLocale>

#include "qgaconstant.h"
#include "qgaevent.h"
#include "qgascreenview.h"
#include "qgaitemmanager.h"
#include "qgasender.h"

// https://developers.google.com/analytics/devguides/collection/protocol/v1/

class QGoogleAnalytics : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE void sendEvent(QString Category, QString Action, QString Label, QString Value);
    Q_INVOKABLE void sendScreenview(QString ScreenName);
    Q_INVOKABLE void setTID(const QString &TID);
    Q_INVOKABLE void setScreenSize(int Width, int Height);
    Q_INVOKABLE void setLanguage(const QString &Language);
    Q_INVOKABLE void setOS(const QString &OS);
    Q_INVOKABLE void pause();
    Q_INVOKABLE void resume();
public:
    static QGoogleAnalytics *getInstance();
    ~QGoogleAnalytics();



signals:

protected slots:
    // send
    void send();
    void prepareNextSend();

    void sendSuccessfully();
    void sendError();

protected:
    explicit QGoogleAnalytics(QObject *parent = 0);

    void init();
    void setProxySettings(QString IP, int Port, QString Username, QString Password);
    void loadParameters();
    void saveParameters(bool GA = false, bool Proxy = false);
    void setNewStatusForSending(int Status);

    QSettings *_settings;
    QGAItemManager _manager;
    QGASender _sender;
    QThread _thread;
private:
    static QGoogleAnalytics *_self;

    //GA
    QString _userID;
    QString _TID;

    // system info
    bool _pause;
    int _pauseTime;
    int _screenWidth;
    int _screenHeight;
    QString _language;
    QString _os;
    bool _addInfoSent;
    QLocale _locale;


    // proxy
    QString _proxyHost;
    int _proxyPort;
    QString _proxyUser;
    QString _proxyPass;
};

static QObject *googleanalytics_qobject_singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    qDebug() << "googleanalytics_qobject_singletontype_provider";
    return QGoogleAnalytics::getInstance();
}

#endif // QGOOGLEANALYTICS_H
