#ifndef QGAITEMMANAGER_H
#define QGAITEMMANAGER_H

#include <QObject>
#include <QDebug>
#include "qgaevent.h"
#include "qgascreenview.h"

class QGAItemManager : public QObject
{
    Q_OBJECT

public:
    explicit QGAItemManager(QObject *parent = 0);
    ~QGAItemManager();

    QList<QGAItem *> getItemlist() const;
    QList<QGAItem *> getItemlistByParams(int Count = 20, int Status = 0);
    void clear();

    void addEvent(const QString &Category, const QString &Action, const QString &Label = "", const QString &Value = "");
    void addScreenview(const QString &ScreenName);
signals:

public slots:
    void cleanSendItem();

protected slots:
    
protected:

    QList<QGAItem *> _itemlist;
private:
    
};

#endif
