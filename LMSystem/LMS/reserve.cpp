#include "reserve.h"

Reserve::Reserve() {}
Reserve::Reserve(QString u, Resources *r, QString date)
{

    Username =u;
    Title = r->getTitle();
    ID = r->getId();
    date_reserved=date;
};

QJsonObject Reserve::toJson()
{
    QJsonObject obj;
    obj["Username"] = Username;
    obj["Title"] = Title;
    obj["Id"]=ID;
    obj["Date_Reserved"] = date_reserved;
    return obj;
}
void Reserve::FromJson(QJsonObject obj){
    Username=obj["Username"].toString();
    ID = obj["Id"].toInt() ;
    Title = obj["Title"].toString();
    date_reserved = obj["Date_Reserved"].toString();
}
