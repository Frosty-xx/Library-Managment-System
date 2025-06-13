#include "notification.h"

Notification::Notification() {}

Notification::Notification(QString t, QString d)
{
    Text = t;
    Date = d;
}
QJsonObject Notification::toJson()
{
    QJsonObject object;
    object["Text"] = Text;
    object["Date"] = Date;

    return object;
}
void Notification::FromJson(QJsonObject object)
{
    Text = object["Text"].toString();
    Date = object["Date"].toString();
}
