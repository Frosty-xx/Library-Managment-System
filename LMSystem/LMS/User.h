#ifndef USER_H
#define USER_H
#include <vector>
#include <QJsonObject>
#include <QString>
#include "Resources.h"
#include "notification.h"
#include "Loan.h"
#include "reserve.h"
using namespace std;

#pragma once



class User
{
public:
    User();
    User(QString u, QString p,QString f,QString l, QString e,QString d );
    virtual ~User();
    // setters
    void setUsername(QString username);
    void setPassword(QString password);
    void setFirstName(QString firstName);
    void setLastName(QString lastName);
    void setEmail(QString email);
    void setPhoneNumber(QString phoneNumber);
    void setDateRegistgered(QString date);

    // getters
    QString getUsername() const { return Username; }
    QString getPassword() const { return Password; }
    QString getFirstName() const { return FirstName; }
    QString getLastName() const { return LastName; }
    QString getEmail() const { return Email; }
    QString getPhoneNumber() const { return PhoneNumber; }
    vector<Notification *> getNotifications() const { return Notifications; };

    vector<Loan *> getBorrowed() const { return BorrowedItems; };
    vector<Reserve *> getReserves() const { return ReservedItems; };
    vector<Loan *> getLHistory() const { return LHistory; };
    vector<Reserve *> getRHistory() const { return RHistory; };

    QString getDateRegistered() const { return DateRegistered ;};
    // LibraryMethods:
    void Borrow(Loan* loan);
    void Return(Resources *item);
    void reserve(Reserve *r);
    void cancelReserve(int ID);
    // Json:
    QJsonObject toJson();
    void FromJson(QJsonObject);


    // methodes to check validity:
    static bool emailcheck(const QString &email) ;
    static bool phonecheck(const QString &phonenum);
    //Passwords:
    static bool pass_ge_5(const QString &pass);
    static bool pass_special(const QString& pass);
    static bool pass_num(const QString& pass);
    static bool pass_Lc(const QString& pass);
    static bool pass_Uc(const QString& pass);

    //notifications:
    void AddNotification(Notification *n) { Notifications.push_back(n); }
    void ClearAllNotifications()
    {
        for (Notification *n : Notifications) {
            delete n;
        }
        Notifications.clear();
    }

private:
    vector<Reserve *> ReservedItems;
    vector<Loan*> BorrowedItems;
    vector<Loan *> LHistory;
    vector < Reserve*>RHistory;
    QString Username;
    QString Password;
    QString FirstName;
    QString LastName;
    QString Email;
    QString PhoneNumber;
    // Dates:
    QString DateRegistered;

    vector<Notification *> Notifications;


};

#endif
