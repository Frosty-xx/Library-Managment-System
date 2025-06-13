#ifndef LIBRARY_H
#define LIBRARY_H
#pragma once
#include "Resources.h"
#include "Book.h"
#include "Article.h"
#include "User.h"
#include "Admin.h"
#include <vector>
#include <queue>
using namespace std;

class Library
{
public:
    Library();
    ~Library();
    // methods
    void LRemoveItem(User *user, int Id, QString Type);
    bool LBorrowItem(User *user, int ID, bool &AlreadyB);
    void LReserveItem(User *user, int ID, bool &AlreadyR,bool &AlreadyB);
    bool LibraryCencelReserve(User *, int ID);
    bool LReturnItem(User *user, int ID);

    bool LRenewItem(User *user, int ID,int QuantitytoADD);

    // method to check if username is taken before
    bool UsernameTaken(QString username);
    // Add Resource
    void AddBook(Book *item)
    {
        Books.push_back(item);
        All_Resources.push_back(item);
    }
    void AddArticle(Article *item)
    {
        Articles.push_back(item);
        All_Resources.push_back(item);
    }
    void PushLoan(Loan *l) { Loans.push_back(l); };
    void PushWaiting(Reserve *R) { Waiting.push_back(R); };
    void PushReserve(queue<Reserve *> *q) { Reserves.push_back(q); };



    // getters
    vector<queue<Reserve *> *> getReserves() const { return Reserves; }
    vector<Book *> getBooks() const { return Books; }
    vector<Article *> getArticles() const { return Articles; }
    vector<User *> getUsers() const { return Users; }
    vector<Loan *> getLoans() const { return Loans; };
    vector<Reserve *> getWaiting() const { return Waiting; };
    vector<Resources *> getAll_Resources() const { return All_Resources; };
    static int getnextId()
    {
        nextId += 1;
        return nextId;
    }
    static int getcurrentId() { return nextId; };

    // setters:
    static void setcurrentId(int Id)
    {
        nextId = Id;
    }

    // User methods
    void LRegisterUser(User *user);
    bool RemoveUser(QString Username);
    vector<Resources *> LSearchTitle(const QString &title, const QString &Filter1 = "None", int ID = -1) const;
    vector<User *> LSearchUsers(const QString &username, const QString &Firstname) const;

    //notifications:
    void notifyUser(User *u, Notification * n);

private:
    // Cataloge
    vector<queue<Reserve *> *> Reserves;
    vector<Reserve *> Waiting;
    vector<Loan *> Loans;
    vector<Book *> Books;
    vector<Article *> Articles;
    vector<Resources *> All_Resources;
    vector<User *> Users;
    static int nextId;
};

#endif
