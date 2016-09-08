#include "qgaevent.h"

QGAEvent::QGAEvent(const QString &Category, const QString &Action, const QString &Label, const QString &Value, QObject *parent) : QGAItem("event", parent) {
    _category = QUrl::toPercentEncoding(Category);
    _action = QUrl::toPercentEncoding(Action);
    _label = QUrl::toPercentEncoding(Label);
    _value = QUrl::toPercentEncoding(Value);
}

QString QGAEvent::toString() {
    return QString("%1&ec=%2&ea=%3&el=%4&ev=%5").arg(QGAItem::toString(), _category, _action, _label, _value);
}
