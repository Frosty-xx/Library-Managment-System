#include "Book.h"
using namespace std;
Book::Book()
{
}
Book::Book(QString title, QString author, int id, bool isAvailable, int availableQuantity,QString Genre,bool elec, int pages):Resources( author, title, id, isAvailable, availableQuantity, Genre, elec)
{

    Pages = pages < 10 ? 0 : pages;
}
Book::~Book()
{
}

QJsonObject Book::toJson()
{
    QJsonObject obj = Resources::toJson();
    obj["Pages"] = Pages;
    return obj;
}
void Book::FromJson(QJsonObject obj)
{
    Resources::FromJson(obj);
    Pages = obj["Pages"].toInt();
}
