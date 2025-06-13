#include "Resources.h"
#include <QJsonObject>
#include <Qstring>
using namespace std;

Resources::Resources()
{
}
Resources::Resources(QString author,QString title,int id,bool isavailable,int quantity,QString genre,bool elect){
    Author=author;
    Title=title;
    Id=id;
    IsAvailable=isavailable;
    availableQuantity=quantity;
    Genre = genre;
    electronic = elect;

}
Resources::~Resources()
{
}
QJsonObject Resources::toJson()
{
    QJsonObject obj;


    obj["title"] = Title;
    obj["author"] = Author;
    obj["Available"] = IsAvailable;
    obj["availableQuantity"] = availableQuantity;
    obj["Id"] = Id;
    obj["Genre"] = Genre;
    obj["Cover"] = Cover;
    obj["PDf"] = PDf;
    obj["Electronic"] = electronic;
    return obj;
}
void Resources::FromJson(QJsonObject object)
{
    Author = object["author"].toString();
    Title = object["title"].toString();
    Genre = object["Genre"].toString();
    IsAvailable = object["Available"].toBool();
    availableQuantity = object["availableQuantity"].toInt();
    Id = object["Id"].toInt();
    Cover = object["Cover"].toString();
    electronic = object["Electronic"].toBool();
    PDf = object["PDf"].toString();
}

//Opeartor
bool Resources::operator==(const Resources &other)
{
    return Title == other.Title && Author == other.Author && Id == other.Id;
}

//utility
//this loops through the title to return the matching titles( search=li returns linear,linear Algerba ....)
bool Resources::matching(const QString &title){

    for (int i = 0; i < title.length(); i++) {
        if (i == this->getTitle().length()) {
            return false;
        } else if (title[i].toLower() != this->getTitle()[i].toLower()) {
            return false;
        }
    }
    return true;
}















