#include "Loan.h"

Loan::Loan()
{
}
Loan::~Loan()
{

}
void Loan::set_date_borrowed(QString date)
{
    date_borrowed = date;
}
void Loan::set_date_returned(QString date)
{
    date_returned = date;
}
void Loan::set_returned(bool returned)
{
    this->returned = returned;
}
Loan::Loan(QString u,Resources *Item, QString date_borrowed, QString date_returned, bool returned)
{
    username=u;
    Title = Item->getTitle();
    ID = Item->getId();
    set_date_borrowed(date_borrowed);
    set_date_returned(date_returned);
    set_returned(returned);
}
QJsonObject Loan::toJson()
{
    QJsonObject obj;
    obj["Username"] = username;
    obj["Title"] = Title;
    obj["Returned"] = returned;
    obj["Id"] = ID;
    obj["date_borrowed"] = date_borrowed;
    obj["date_returned"] = date_returned;
    return obj;
}
void Loan::FromJson(QJsonObject object)
{
    username = object["Username"].toString();
    ID = object["Id"].toInt();
    returned=object["Returned"].toBool();
    Title=object["Title"].toString();
    date_borrowed = object["date_borrowed"].toString();
    date_returned = object["date_returned"].toString();
}
