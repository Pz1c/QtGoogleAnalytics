#include "qgascreenview.h"

QGAScreenview::QGAScreenview(const QString &ScreenName, QObject *parent) : QGAItem("screenview", parent) {
    _screenName = QUrl::toPercentEncoding(ScreenName);
}

QString QGAScreenview::toString() {
    return QString("%1&an=%2&av=%3&aid=%4&aiid=%5&cd=%6").arg(QGAItem::toString(), QUrl::toPercentEncoding(APPLICATION_TITLE), APPLICATION_VERSION,
                                                        APPLICATION_PACKAGE, APPLICATION_INSTALLER_PACKAGE, _screenName);
}
