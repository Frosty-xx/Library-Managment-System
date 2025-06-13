#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QJsonObject>
class Notification
{
public:
    //getters:
    QString getDate() const { return Date; };
    QString getText() const { return Text; };

    Notification();
    Notification(QString text, QString Date);

    QJsonObject toJson();
    void FromJson(QJsonObject object);
private:
    QString Date;
    QString Text;


};

#endif // NOTIFICATION_H
