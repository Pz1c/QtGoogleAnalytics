#include "qgaitem.h"

uint QGAItem::_currentId = 0;

QGAItem::QGAItem(const QString &ItemType, QObject *parent) : QObject(parent) {
    _id = ++_currentId;
    _type = ItemType;
    _status = GA_ITEM_STATUS_NONE;
    if (_type.compare("event") == 0) {
        _typeID = GA_ITEM_TYPE_EVENT;
    } else if (_type.compare("pageview") == 0) {
        _typeID = GA_ITEM_TYPE_PAGEVIEW;
    } else if (_type.compare("screenview") == 0) {
        _typeID = GA_ITEM_TYPE_SCREENVIEW;
    } else {
        _typeID = GA_ITEM_TYPE_NONE;
    }

    _timestamp = QDateTime::currentMSecsSinceEpoch();
}

int QGAItem::status() const
{
    return _status;
}

void QGAItem::setStatus(int status)
{
    _status = status;
}

QString QGAItem::toString() {
    return QString("t=%1&qt=%2").arg(_type, QString::number((int)((QDateTime::currentMSecsSinceEpoch() - _timestamp) / 1000)));
}
