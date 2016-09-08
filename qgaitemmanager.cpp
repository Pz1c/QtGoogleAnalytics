#include "qgaitemmanager.h"

QGAItemManager::QGAItemManager(QObject *parent) : QObject(parent) {
    
}

QGAItemManager::~QGAItemManager() {
    clear();
}

void QGAItemManager::clear() {
    foreach(QGAItem *d, _itemlist) {
        d->deleteLater();
    }
    _itemlist.clear();
}

QList<QGAItem *> QGAItemManager::getItemlist() const
{
    return _itemlist;
}

QList<QGAItem *> QGAItemManager::getItemlistByParams(int Count, int Status) {
    //qDebug() << "QGAItemManager::getItemlistByParams" << Count << Status;
    QList<QGAItem *> res;
    foreach(QGAItem *item, _itemlist) {
        //qDebug() << "item" << item->status() << res.size();
        if (item->status() == Status) {
            res.append(item);
        }
        if (res.size() >= Count) {
            break;
        }
    }

    return res;
}

void QGAItemManager::cleanSendItem() {
    //qDebug() << "QGAItemManager::cleanSendItem";
    if (_itemlist.size() == 0) {
        return;
    }
    QMutableListIterator<QGAItem *> i(_itemlist);
    while (i.hasNext()) {
        QGAItem *item = i.next();
        if (item->status() == GA_ITEM_STATUS_SEND) {
            item->deleteLater();
            i.remove();
        }
    }
}

void QGAItemManager::addEvent(const QString &Category, const QString &Action, const QString &Label, const QString &Value) {
    cleanSendItem();
    _itemlist.append(new QGAEvent(Category, Action, Label, Value, this));
}

void QGAItemManager::addScreenview(const QString &ScreenName) {
    cleanSendItem();
    _itemlist.append(new QGAScreenview(ScreenName, this));
}
