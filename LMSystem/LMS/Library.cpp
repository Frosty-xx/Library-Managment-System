#include "Library.h"
#include "Date.h"
#include <QMessageBox>
int Library::nextId = 1;
Library::Library()
{
}

Library::~Library()
{
    for (Resources* r : All_Resources) {
        delete r;
    }
    All_Resources.clear();

    for (Loan* l : Loans) {
        delete l;
    }
    Loans.clear();

    for (Reserve* r : Waiting) {
        delete r;
    }
    Waiting.clear();

    for (User* u : Users) {
        delete u;
    }
    Users.clear();

    for (unsigned int i = 0; i < Users.size(); i++)
    {
        delete Users[i];
        Users[i] = nullptr;
    }
    for ( unsigned int i = 0; i < Reserves.size(); i++)
    {
        while (!Reserves[i]->empty()) {
            delete Reserves[i]->front();
        }
        delete Reserves[i];
    }
}

bool Library::LBorrowItem(User *user,int ID, bool &AlreadyB)
{
    for (Loan *l : user->getBorrowed()) {
        if (l->getID() == ID) {
            AlreadyB = true;
            return false;
        }
    }
    bool waiting = false;
    //finding the item:
    bool found = false;
    Resources *r;
    for (Book *b : Books) {
        if (b->getId() == ID) {
            r = b;
            break;
            found = true;
        }
    }
    if (!found) {
        for (Article *a : Articles) {
            if (a->getId() == ID) {
                r = a;
            }
        }
    }
    //cheking if the user is in the waiting List
    for (unsigned int i = 0; i < Waiting.size(); i++) {
        if (Waiting[i]->getUsername() == user->getUsername() && Waiting[i]->getId() == r->getId()) {
            Waiting.erase(Waiting.begin() + i);
            waiting = true;
        }
    }
    if (!r->getIsAvailable()&& !waiting) {
        return false;
    }

    Date d;
    d.apply_currentDate();
    Loan *l = new Loan(user->getUsername(), r, d.toString());

    Loans.push_back(l);
    user->Borrow(l);
    r->setavailableQuantity(r->getavailableQuantity() - 1);


    r=nullptr;
    return true;
}


void Library::LRemoveItem(User *user, int Id,QString Type)
{
    if (dynamic_cast<Admin *>(user))
    {
        //canceling All Reserves::

        for (User *u : Users) {
            LibraryCencelReserve(u, Id);
        }

        //Returning all items(The employer would know the book removed when its actully returned)
        for (User *u : Users) {
            LReturnItem(u, Id);
        }

        for (unsigned int i = 0; i < All_Resources.size(); i++) {
            if (All_Resources[i]->getId() == Id) {
                All_Resources.erase(All_Resources.begin() + i);
            }
        }
        if (Type == "Book") {
            for (unsigned int i = 0; i < Books.size(); i++) {
                if (Books[i]->getId() == Id) {
                    Books.erase(Books.begin() + i);
                }
            }
        }

        else {
            for (unsigned int i = 0; i < Articles.size(); i++) {
                if (Articles[i]->getId() == Id) {
                    Articles.erase(Articles.begin() + i);
                }
            }
        }
    }
}

void Library::LReserveItem(User *user,int ID,bool &alreadyR,bool &alreadyB)
{
    //finding the item:
    //could replace to search in all item when more resources are added
    bool found = false;
    Resources *r;
    for (Book *b : Books) {
        if (b->getId() == ID) {
            r = b;
            break;
            found = true;
        }
    }
    if (!found) {
        for (Article *a : Articles) {
            if (a->getId() == ID) {
                r = a;
            }
        }
    }


    //cheking and Reserving:
    found = false;
    for (Reserve *r : user->getReserves()) {
        if (r->getId() == ID) {
            alreadyR = true;
            return;
            break;
        }
    }

    for (Loan *l : user->getBorrowed()) {
        if (l->getID() == ID) {
            alreadyB = true;
            return;
            break;
        }
    }
    if (found && !alreadyR && !alreadyB ) {
        Date d;
        d.apply_currentDate();
        Reserve *nr = new Reserve(user->getUsername(), r, d.toString());

        user->reserve(nr);
        if (r->getIsAvailable()) {
            Waiting.push_back(nr);

            r->setavailableQuantity(r->getavailableQuantity() - 1);
            if (r->getavailableQuantity() == 0) {
                r->setIsAvailable(0);
            }
        } else {
            for (queue<Reserve *>* q : Reserves) {
                if (q->front()->getId() == ID) {
                    q->push(nr);
                }
            };
        }
    }
    if (!found) {


        Date d;
        d.apply_currentDate();
        Reserve *nr = new Reserve(user->getUsername(), r, d.toString());
        user->reserve(nr);

        if (r->getIsAvailable()) {
            Waiting.push_back(nr);
            if (r->getavailableQuantity() == 1) {
                r->setavailableQuantity(r->getavailableQuantity() - 1);
                r->setIsAvailable(0);
            } else {
                r->setavailableQuantity(r->getavailableQuantity() - 1);
            }
        } else {
            queue<Reserve *> *n = new queue<Reserve *>();
            n->push(nr);
            Reserves.push_back(n);
        }
    }
}
bool Library::LibraryCencelReserve(User *user, int ID)
{
    Resources *res;
    for (Resources *r : All_Resources) {
        if (r->getId() == ID) {
            res = r;
            break;
        }
    }
    for (int i = 0; i < Waiting.size(); i++) {
        if (Waiting[i]->getUsername() == user->getUsername() and Waiting[i]->getId() == ID) {
            user->cancelReserve(ID);
            delete Waiting[i];
            Waiting.erase(Waiting.begin() + i);
            res->setavailableQuantity(res->getavailableQuantity() + 1);

        // moving reserves
        for (unsigned int i = 0; i < Reserves.size(); i++) {
                if (!Reserves[i]->empty() && Reserves[i]->front()->getId() == ID) {
                    Waiting.push_back(Reserves[i]->front());
                    Reserves[i]->pop();
                    res->setavailableQuantity(res->getavailableQuantity() + -1);
                    // TODO: Notify the user in Waiting.back()
                    User *u;
                    for (User *us : Users) {
                        if (us->getUsername() == Waiting.back()->getUsername()) {
                            u = us;
                        }
                    }
                    Date d;
                    d.apply_currentDate();
                    Notification *n = new Notification("Your Item " + Waiting.back()->getTitle()
                                                           + " is now available for you to borrow",
                                                       d.toString());
                    notifyUser(u, n);
                    break;
                }
            }
            res->setIsAvailable(res->getavailableQuantity() > 0 ? 1 : 0);
            return true;
        }
    }

    for (int i = 0; i < Reserves.size(); i++) {
        if(!Reserves[i].empty()){
        if (Reserves[i]->front()->getId() == ID) {
            queue<Reserve *> copy = *Reserves[i];
            vector<Reserve *> Replacement;
            while (!copy.empty()) {
                if (copy.front()->getUsername() == user->getUsername()
                    and copy.front()->getId() == ID) {
                    user->cancelReserve(ID);
                    copy.pop();
                    continue;
                }
                Replacement.push_back(copy.front());
                copy.pop();
            }
            delete Reserves[i];
            Reserves[i] = new queue<Reserve *>();
            for (Reserve *r : Replacement) {
                Reserves[i]->push(r);
            }
            return true;
        }
    }
}
    return false;
}
bool Library::LReturnItem(User *user,int ID)
{
    bool found = false;
    Resources *r = nullptr;

    // Search in books
    for (Book *b : Books) {
        if (b->getId() == ID) {
            r = b;
            found = true;
            break;
        }
    }

    if (!found) {
        for (Article *a : Articles) {
            if (a->getId() == ID) {
                r = a;
                found = true;
                break;
            }
        }
    }

    // If resource wasn't found at all
    if (!found) return false;


    bool BBefore = false;
    for (Loan* l : user->getBorrowed()) {
        if (l->getID() == ID) {
            BBefore = true;
            break;
        }
    }
    if (!BBefore) return false;

    // Remove the loan
    for (unsigned int i = 0; i < Loans.size(); i++) {
        if (user->getUsername() == Loans[i]->getUsername() && Loans[i]->getID() == r->getId()) {

            user->Return(r);
            delete Loans[i];
            Loans.erase(Loans.begin() + i);

            r->setavailableQuantity(r->getavailableQuantity() + 1);
            if (!r->getIsAvailable()) {
                r->setIsAvailable(1);
            }
            break;
        }
    }


    for (unsigned int i = 0; i < Reserves.size(); i++) {
        if (!Reserves[i]->empty() && Reserves[i]->front()->getId() == r->getId()) {
            Waiting.push_back(Reserves[i]->front());
            Reserves[i]->pop();
            // TODO: Notify the user in Waiting.back()
            User *u;
            for (User *us : Users) {
                if (us->getUsername() == Waiting.back()->getUsername()) {
                    u = us;
                }
            }
            Date d;
            d.apply_currentDate();
            Notification *n = new Notification("Your Item " + Waiting.back()->getTitle()
                                                   + " is now available for you to borrow",
                                               d.toString());
            notifyUser(u, n);

            u = nullptr;
            break;
        }
    }

    return true;


}

void Library::LRegisterUser(User *user)
{
    Users.push_back(user);
}
bool Library::UsernameTaken(QString username)    {
    for (User *u : Users) {
        if (username == u->getUsername()) {
            return true;
        }
    }
    return false;
}
vector<Resources *> Library::LSearchTitle(const QString &title,const QString &Filter1,int Id) const
{
    vector<Resources *> results;


    if (Filter1 == "Books") {
        for (const auto &book : Books)
        {
            if (((book->matching(title)|| title=="\0") && (book->getId()== Id || Id==-1))){
                results.push_back(book);
            }
        }
    }
    else if (Filter1 == "Articles")
        {
        for (const auto &article : Articles) {
            if (((article->matching(title)|| title=="\0") && (article->getId()== Id || Id==-1))) {
                results.push_back(article);
            }
        }
        }
    else{
        for (const auto &Resource : All_Resources) {
                if (((Resource->matching(title)|| title=="\0") && (Resource->getId()== Id || Id==-1))) {
                    results.push_back(Resource);
                }

        }

        }
    return results;
}

bool Library::LRenewItem(User *user, int ID, int QuantitytoADD)
{
    if (dynamic_cast<Admin *>(user)) {
        Resources *r;
        for (Resources *res : All_Resources) {
            if (res->getId() == ID) {
                r = res;
                break;
            }
        }
        r->setavailableQuantity(r->getavailableQuantity() + QuantitytoADD);
        // Move Reserves;
        int count = QuantitytoADD;
        for (unsigned int i = 0; i < Reserves.size(); i++) {
            if(!Reserves[i].empty()){
            if (Reserves[i]->front()->getId() == ID) {
                while (!Reserves[i]->empty() and count > 0) {
                    Waiting.push_back(Reserves[i]->front());
                    Reserves[i]->pop();
                    r->setavailableQuantity(r->getavailableQuantity() - 1);
                    count--;

                    //Notifying:
                    User *u;
                    for (User *us : Users) {
                        if (us->getUsername() == Waiting.back()->getUsername()) {
                            u = us;
                        }
                    }
                    Date d;
                    d.apply_currentDate();
                    Notification *n = new Notification("Your Item " + Waiting.back()->getTitle()
                                                           + " is now available for you to borrow",
                                                       d.toString());
                    notifyUser(u, n);
                }
                break;
            }
        }
        r->setIsAvailable(r->getavailableQuantity() > 0 ? 1 : 0);
        return true;
    }
    }
    return false;
}

bool Library::RemoveUser(QString Username)
{
    User *user;
    for (int i = 0; i < Users.size(); i++) {
        if (Users[i]->getUsername() == Username) {
            user = Users[i];
            Users.erase(Users.begin() + i);
        }
    }
    //return all items:
    for (int j = user->getBorrowed().size(); j > 0; j--) {
        LReturnItem(user, user->getBorrowed()[j]->getID());
    }
    //Cancel All Reserves:
    for (int i = user->getReserves().size(); i > 0; i--) {
        LibraryCencelReserve(user, user->getReserves()[i]->getId());
    }

    delete user;

    return true;
}
vector<User *> Library::LSearchUsers(const QString &username, const QString &Firstname) const
{
    vector<User *> Results;

    bool matchU;
    bool matchF;
    for (User *u : Users) {
        matchU = true;
        matchF = true;
        matchU = username.length() > u->getUsername().length() ? false : true;
        matchF = Firstname.length() > u->getFirstName().length() ? false : true;

        if (matchU) {
            for (int i = 0; i < username.length(); i++) {
                if (username[i].toLower() != u->getUsername()[i].toLower()) {
                    matchU = false;
                    break;
                }
            }
        }
        if (matchF) {
            for (int i = 0; i < Firstname.length(); i++) {
                if (Firstname[i].toLower() != u->getFirstName()[i].toLower()) {
                    matchF = false;
                    break;
                }
            }
        }

        if ((matchU || username == "\0") && (matchF || Firstname == "\0")) {
            Results.push_back(u);
        }
    }
    return Results;
}

void Library::notifyUser(User *u, Notification *n)
{
    u->AddNotification(n);
}



