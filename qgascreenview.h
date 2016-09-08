#ifndef QGASCREENVIEW_H
#define QGASCREENVIEW_H

#include "qgaitem.h"

class QGAScreenview : public QGAItem
{
    Q_OBJECT

public:
    explicit QGAScreenview(const QString &ScreenName, QObject *parent = 0);

    QString toString() override;
signals:

public slots:
    
protected slots:

protected:


};

#endif
