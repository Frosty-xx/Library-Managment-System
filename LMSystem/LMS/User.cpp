#include "User.h"
#include "Loan.h"
#include "Date.h"
#include <ctime>
#include <QString>
#include <QJsonArray>
#include <regex> // regular experssion for emails
using namespace std;
User::User()
{
}
User::User(QString u, QString p,QString f,QString l, QString e,QString d ){
    Username=u;
    Password=p;
    FirstName=f;
    LastName=l;
    Email=e;
    DateRegistered=d;
}
User::~User()
{


    for (unsigned int i = 0; i < LHistory.size(); i++)
    {
        delete LHistory[i];
        LHistory[i] = nullptr;
    }
    for (Reserve *r : RHistory) {
        delete r;
        r = nullptr;
    }
    for (Notification *n : Notifications) {
        delete n;
        n = nullptr;
    }
}
// setters
void User::setUsername(QString username)
{
    Username = username;
}
void User::setPassword(QString password)
{

    Password = password;
}
void User::setFirstName(QString fristName)
{
    FirstName = fristName;
}
void User::setLastName(QString lastName)
{
    LastName = lastName;
}
void User::setEmail(QString email)
{
    Email = email;
}
void User::setPhoneNumber(QString phoneNumber)
{
    PhoneNumber = phoneNumber;
}
void User::setDateRegistgered(QString date)
{
    DateRegistered = date;
}

// checkers
 bool User::phonecheck(const QString &phonenum)
{
    const regex pattern("^0[567][0-9]{8}$");
    return regex_match(phonenum.toStdString(),pattern);
}
bool User::emailcheck(const QString &email)
{
    const regex pattern(
        "(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    return regex_match(email.toStdString(), pattern);
}
bool User::pass_ge_5(const QString &pass)
{
    const regex pattern("^.{5,}$");

    return regex_match(pass.toStdString(), pattern);
}
bool User::pass_special(const QString &pass)
{
    const regex pattern("[@$!?_#&]");
    return regex_search(pass.toStdString(), pattern);
}
bool User::pass_num(const QString &pass)
{

    const regex pattern("[0-9]");
    return regex_search(pass.toStdString(), pattern);
}
bool User::pass_Lc(const QString &pass)
{
    const regex pattern("[a-z]");
    return regex_search(pass.toStdString(), pattern);
}
bool User::pass_Uc(const QString &pass)
{
    const regex pattern("[A-Z]");
    return regex_search(pass.toStdString(), pattern);
}

// LibraryMethods:
void User::Borrow(Loan* loan)
{
    Loan *copy = new Loan(*loan);
    LHistory.push_back(copy);
    BorrowedItems.push_back(loan);

    // updating the Resrved items
    for (unsigned int i = 0; i < ReservedItems.size(); i++)
    {
        if (ReservedItems[i]->getId() == loan->getID())
        {
            ReservedItems.erase(ReservedItems.begin() + i);
            break;
        }
    }
}
void User::Return(Resources *item){

    for (unsigned int i = 0; i < BorrowedItems.size(); i++)
    {
        if (BorrowedItems[i]->getID() == item->getId())
        {
            BorrowedItems.erase(BorrowedItems.begin() + i);
            break;
        }
    }
        // updating the history
        Date Dreturned;
        Dreturned.apply_currentDate();

        for ( unsigned int k = 0; k < LHistory.size(); k++)
        {
            if (LHistory[k]->getID() == item->getId() && !LHistory[k]->get_returned())
            {
                LHistory[k]->set_date_returned(Dreturned.toString());
                LHistory[k]->set_returned(true);
                break;
            }
        }
}
void User::reserve(Reserve* r)
{

    ReservedItems.push_back(r);
    Reserve *copy = new Reserve(*r);
    RHistory.push_back(copy);
}

// Files:
QJsonObject User::toJson()
{
    QJsonObject obj;

    obj["Username"] = Username;
    obj["Password"] = Password;
    obj["FirstName"] = FirstName;
    obj["LastName"] = LastName;
    obj["Email"] = Email;
    obj["PhoneNumber"] = PhoneNumber;
    obj["DateRegistered"] = DateRegistered;

    // Borrowed Items
    QJsonArray borrowedArray;
    for (Loan *l : BorrowedItems)
    {

        borrowedArray.append(l->toJson());

    }
    obj["BorrowedItems"] = borrowedArray;

    //Reserves:
    QJsonArray reservedItems;
    for (Reserve *res : ReservedItems) {
        reservedItems.append(res->toJson());
    }
    obj["ReservedItems"] = reservedItems;


    // LHistory
    QJsonArray HistoryArray;
    for (Loan *loan : LHistory) {
        HistoryArray.append(loan->toJson());
    }
    obj["History"] = HistoryArray;

    // RHistoy:
    QJsonArray RHistoryArray;
    for (Reserve *res : RHistory) {
        RHistoryArray.append(res->toJson());
    }
    obj["Reservations History"]=RHistoryArray;

    //Notifcations:
    QJsonArray notifcationsarray;
    for (Notification *n : Notifications) {
        notifcationsarray.append(n->toJson());
    }
    obj["Notifications"] = notifcationsarray;
    return obj;
}
void User::FromJson(QJsonObject obj)
{
    Username = obj["Username"].toString();
    Password = obj["Password"].toString();
    FirstName = obj["FirstName"].toString();
    LastName = obj["LastName"].toString();
    Email = obj["Email"].toString();
    PhoneNumber = obj["PhoneNumber"].toString();
    DateRegistered = obj["DateRegistered"].toString();

    // Loans
    QJsonArray borrowedItems = obj["BorrowedItems"].toArray();
    QJsonArray history = obj["History"].toArray();
    for (int i = 0; i < borrowedItems.size(); i++) {
        Loan *l = new Loan();
        l->FromJson(borrowedItems[i].toObject());
        BorrowedItems.push_back(l);
    }
    for (int i = 0; i < history.size(); i++) {
        Loan *loan = new Loan();
        loan->FromJson(history[i].toObject());
        LHistory.push_back(loan);
    }

    //Reserves
    QJsonArray Reservesarray = obj["ReservedItems"].toArray();
    for (int i = 0; i < Reservesarray.size(); i++) {
        Reserve *r = new Reserve();
        r->FromJson(Reservesarray[i].toObject());
        ReservedItems.push_back(r);
    }
    //Rhistory
    QJsonArray RHistoryArray = obj["Reservations Histroy"].toArray();
    for (int j = 0;j < RHistoryArray.size(); j++) {
        Reserve *r = new Reserve;
        r->FromJson(Reservesarray[j].toObject());
        RHistory.push_back(r);
    }

    //notifications:
    QJsonArray NotifArray = obj["Notifications"].toArray();
    for (int j = 0; j < NotifArray.size(); j++) {
        Notification *n = new Notification;
        n->FromJson(NotifArray[j].toObject());
        Notifications.push_back(n);
    }
}
void User::cancelReserve(int ID)
{
    for (unsigned int i = 0; i < ReservedItems.size(); i++) {
        if (ReservedItems[i]->getId() == ID) {
            ReservedItems.erase(ReservedItems.begin() + i);
            return;
        }
    }
}










