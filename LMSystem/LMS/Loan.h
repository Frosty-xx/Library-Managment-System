#ifndef LOAN_H
#define LOAN_H
#include "Resources.h"
#include <QJsonObject>
using namespace std;
#pragma once
class Loan
{
public:
    Loan();
    Loan(QString username,Resources *Item, QString date_borrowed, QString date_returned = "\0", bool returned = false);
    Loan(Loan const &other)
    {
        username = other.username;
        Title = other.Title;
        ID = other.ID;
        date_borrowed = other.date_borrowed;
        date_returned = other.date_returned;
        returned = other.returned;

    }
    ~Loan();
    // seters
    void set_username(QString username);
    void set_title(QString Title);
    void set_ID(int ID);
    void set_date_borrowed(QString date);
    void set_date_returned(QString date);
    void set_returned(bool);

    // geters

    QString get_date_borrowed() const { return date_borrowed; };
    QString get_date_returned() const { return date_returned; };
    bool get_returned() const { return returned; };
    QString getTitle() const { return Title; };
    int getID() const { return ID; };
    QString getUsername() const { return username; };

    QJsonObject toJson();
    void FromJson(QJsonObject object);

private:
    QString username;
    QString Title;
    int ID;
    QString date_borrowed;
    QString date_returned;
    bool returned;
};

#endif
