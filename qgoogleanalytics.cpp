#include "qgoogleanalytics.h"

QGoogleAnalytics * QGoogleAnalytics::getInstance() {
    qDebug() << "QGoogleAnalytics::getInstance";
    if (!_self) {
        _self = new QGoogleAnalytics();
    }
    return _self;
}

QGoogleAnalytics* QGoogleAnalytics::_self = 0;

QGoogleAnalytics::QGoogleAnalytics(QObject *parent) : QObject(parent) {
    // _TID = "UA-57963747-6";
    _addInfoSent = false;
    _screenWidth = -1;
    _screenHeight = -1;
    _language = _locale.name();
    _pause = false;

    _sender.moveToThread(&_thread);
    connect(&_sender, SIGNAL(finishSuccessfully()), this, SLOT(sendSuccessfully()));
    connect(&_sender, SIGNAL(finishError()), this, SLOT(sendError()));
    init();
    prepareNextSend();
}

QGoogleAnalytics::~QGoogleAnalytics() {
    _thread.terminate();
}

void QGoogleAnalytics::init() {
    qDebug() << "QGoogleAnalytics::init()" << ORGANIZATION_NAME << APPLICATION_NAME;
    _settings = new QSettings(QSettings::IniFormat, QSettings::UserScope, ORGANIZATION_NAME, APPLICATION_NAME);
    loadParameters();
}

void QGoogleAnalytics::loadParameters() {
    _settings->beginGroup("GA");
    _userID = _settings->value("user_id", "").toString();
    _settings->endGroup();
    _settings->beginGroup("Proxy");
    _proxyHost = _settings->value("host", "").toString();
    _proxyPort = _settings->value("port", "").toInt();
    _proxyUser = _settings->value("user", "").toString();
    _proxyPass = _settings->value("password", "").toString();
    _settings->endGroup();
    _sender.setProxySettings(_proxyHost, _proxyPort, _proxyUser, _proxyPass);

    if (_userID.isEmpty()) {
        _userID = QUuid::createUuid().toString().replace("{", "").replace("}", "").replace("-", "");
        saveParameters(true);
    }
}

void QGoogleAnalytics::saveParameters(bool GA, bool Proxy) {
    if (GA) {
        _settings->beginGroup("GA");
        _settings->setValue("user_id", _userID);
        _settings->endGroup();
    }

    if (Proxy) {
        _settings->beginGroup("Proxy");
        _settings->setValue("host", _proxyHost);
        _settings->setValue("port", _proxyPort);
        _settings->setValue("user", _proxyUser);
        _settings->setValue("password", _proxyPass);
        _settings->endGroup();
        _sender.setProxySettings(_proxyHost, _proxyPort, _proxyUser, _proxyPass);
    }
}

void QGoogleAnalytics::setProxySettings(QString IP, int Port, QString Username, QString Password) {
    _proxyHost = IP;
    _proxyPort = Port;
    _proxyUser = Username;
    _proxyPass = Password;
    _sender.setProxySettings(_proxyHost, _proxyPort, _proxyUser, _proxyPass);
}

void QGoogleAnalytics::send() {
    //qDebug() << "QGoogleAnalytics::send()" << _TID << _os << _language << _screenWidth << _screenHeight;
    if (_TID.isEmpty()) {
        //qDebug() << "QGoogleAnalytics::send() TID is empty";
        prepareNextSend();
        return;
    }
    if (_pause || (--_pauseTime > 0)) {
        //qDebug() << "QGoogleAnalytics::send() sending paused";
        prepareNextSend();
        return;
    }



    QByteArray postData;
    _manager.cleanSendItem();
    QList<QGAItem *> items = _manager.getItemlistByParams();
    bool is_empty = true;
    foreach(QGAItem *item, items) {
        item->setStatus(GA_ITEM_STATUS_SENDING);
        QString tmp_str = QString("v=1&tid=%1&cid=%2&%3").arg(_TID, _userID, item->toString());
        if (is_empty && !_addInfoSent) {
            if (_screenWidth != -1 && _screenHeight != -1) {
                tmp_str.append(QString("&sr=%1x%2").arg(QString::number(_screenWidth), QString::number(_screenHeight)));
            }

            if (!_language.isEmpty()) {
                tmp_str.append(QString("&ul=%1").arg(_language));
            }

            if (!_os.isEmpty()) {
                tmp_str.append(QString("&ua=Qt/%1(%2)").arg(QT_VERSION_STR, _os));
            }

            _addInfoSent = _screenWidth != -1 && _screenHeight != -1 && !_language.isEmpty() && !_os.isEmpty();
        }
        //tmp_str = QUrl::toPercentEncoding(tmp_str);
        //tmp_str.append("\n");
        postData.append(tmp_str);
        postData.append('\n');
        is_empty = false;
    }

    if (is_empty) {
        prepareNextSend();
        return;
    }

    //qDebug() << "final post data" << postData;
    _sender.setPostData(postData);
    if (!_thread.isRunning()) {
        _thread.start(QThread::LowestPriority);
    }
    _sender.send();
}

void QGoogleAnalytics::prepareNextSend() {
    //qDebug() << "QGoogleAnalytics::prepareNextSend()";
    QTimer::singleShot(GA_SENDING_FREQUENCY, this, SLOT(send()));
}

void QGoogleAnalytics::setNewStatusForSending(int Status) {
    QList<QGAItem *> items = _manager.getItemlist();
    foreach(QGAItem *item, items) {
        if (item->status() == GA_ITEM_STATUS_SENDING) {
            item->setStatus(Status);
        }
    }
}

void QGoogleAnalytics::setTID(const QString &TID)
{
    _TID = TID;
}

void QGoogleAnalytics::setScreenSize(int Width, int Height) {
    _screenWidth = Width;
    _screenHeight = Height;
    _addInfoSent = false;
}

void QGoogleAnalytics::setLanguage(const QString &Language) {
    _language = Language;
    _addInfoSent = false;
}

void QGoogleAnalytics::setOS(const QString &OS) {
    _os = OS;
    _addInfoSent = false;
}

void QGoogleAnalytics::sendSuccessfully() {
    //qDebug() << "QGoogleAnalytics::sendSuccessfully()";
    setNewStatusForSending(GA_ITEM_STATUS_SEND);
    //_thread.wait();
    prepareNextSend();
}

void QGoogleAnalytics::sendError() {
    qDebug() << "QGoogleAnalytics::sendError()";
    setNewStatusForSending(GA_ITEM_STATUS_NONE);
    //_thread.wait();
    prepareNextSend();
}

void QGoogleAnalytics::sendEvent(QString Category, QString Action, QString Label, QString Value) {
    //qDebug() << "QGoogleAnalytics::sendEvent" << Category << Action << Label << Value;
    _manager.addEvent(Category, Action, Label, Value);
}

void QGoogleAnalytics::sendScreenview(QString ScreenName) {
    //qDebug() << "QGoogleAnalytics::sendScreenview" << ScreenName;
    _manager.addScreenview(ScreenName);
}

void QGoogleAnalytics::pause() {
    _pause = true;
    _pauseTime = GA_PAUSE_TIME_DEF;
}

void QGoogleAnalytics::resume() {
    _pause = false;
}
