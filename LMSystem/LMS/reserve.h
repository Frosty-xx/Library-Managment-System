#ifndef RESERVE_H
#define RESERVE_H
#include <QString>
#include "Resources.h"

class Reserve
{
public:
    Reserve();
    Reserve(QString u, Resources *r,QString date);
    Reserve(Reserve const &other)
    {
        Username = other.Username;
        Title = other.Title;
        ID = other.ID;
        date_reserved = other.date_reserved;
    }

    //getters:
    QString getUsername(){return Username;};
    QString getTitle() { return Title; };
    int getId() { return ID; };
    QString get_date_reserved() { return date_reserved; };

    // Setters:
    void setItem(Resources *r)
    {
        Title = r->getTitle();
        ID = r->getId();
    };
    //Json:
    QJsonObject toJson();
    void FromJson(QJsonObject object);


private:
    QString Username;
    QString Title;
    int ID;
    QString date_reserved;


};

#endif // RESERVE_H
