#ifndef QGAEVENT_H
#define QGAEVENT_H

#include "qgaitem.h"

class QGAEvent : public QGAItem
{
    Q_OBJECT

public:
    explicit QGAEvent(const QString &Category, const QString &Action, const QString &Label = "", const QString &Value = "", QObject *parent = 0);

    QString toString() override;
signals:

public slots:
    
protected slots:

protected:


};

#endif
