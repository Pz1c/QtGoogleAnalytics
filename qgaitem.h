#ifndef QGAITEM_H
#define QGAITEM_H

#include <QObject>
#include <QDebug>
#include <QDateTime>
#include <QUrl>
#include "qgaconstant.h"

class QGAItem : public QObject
{
    Q_OBJECT

public:
    explicit QGAItem(const QString &ItemType, QObject *parent = 0);

    int status() const;
    void setStatus(int status);

    virtual QString toString();
signals:

public slots:
    
protected slots:

protected:
    // https://developers.google.com/analytics/devguides/collection/protocol/v1/parameters

    // event
    QString _category;
    QString _action;
    QString _label;
    QString _value;

    // pageview
    QString _host;
    QString _page;
    QString _title;

    // screenview
    QString _screenName;

private:
    uint _id;
    QString _type; // event or pageview
    int _typeID;
    qint64 _timestamp;
    int _status; // 0 not send

    static uint _currentId;
};

#endif
