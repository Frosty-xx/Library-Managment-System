#include "LibraryDataManager.h"
#include "Admin.h"
#include <QFile>
#include <QJsonArray>

LibraryDataManager::LibraryDataManager()
{
}

LibraryDataManager::~LibraryDataManager()
{
}
bool LibraryDataManager::save(const Library &library, const QString &filename)
{
    QFile file(filename);

    qDebug() << "Saving file To" << filename;
    QJsonObject root;
    QJsonObject libraryObj;
    QJsonObject resourcesObj;
    QJsonObject usersObj;

    // Resources::
    QJsonArray booksArray;
    for (unsigned int i = 0; i < library.getBooks().size(); i++)
    {
        booksArray.append(library.getBooks()[i]->toJson());
    }
    QJsonArray articleArray;
    for (unsigned int i = 0; i < library.getArticles().size(); i++)
    {
        articleArray.append(library.getArticles()[i]->toJson());
    }

    resourcesObj["Books"] = booksArray;
    resourcesObj["Articles"] = articleArray;
    libraryObj["Resources"] = resourcesObj;

    // Users:
    QJsonArray UsersArray;
    QJsonArray AdminsArray;
    for (unsigned int i = 0; i < library.getUsers().size(); i++)
    {
        if (dynamic_cast<Admin *>(library.getUsers()[i]))
        {
            AdminsArray.append(library.getUsers()[i]->toJson());
        }
        else
        {

            UsersArray.append(library.getUsers()[i]->toJson());
        }
    }

    usersObj["Admins"] = AdminsArray;
    usersObj["Regular Users"] = UsersArray;
    libraryObj["Users"] = usersObj;

    //Reserves and Borrowed:

    QJsonArray Reservesarray;

    QJsonArray waitingarray;
    QJsonArray Loansarray;



    for (Reserve *w : library.getWaiting()) {
        waitingarray.append(w->toJson());
    }
    libraryObj["Waiting"] = waitingarray;
    for (Loan *l : library.getLoans()) {
        Loansarray.append(l->toJson());
    }
    libraryObj["Loans"] = Loansarray;

    try {
        for (unsigned int j = 0; j < library.getReserves().size(); ++j) {
            QJsonArray Queuearray;
            std::queue<Reserve *> tempQueue = *library.getReserves()[j];
            while (!tempQueue.empty()) {
                Reserve *res = tempQueue.front();
                if (res)
                    Queuearray.append(res->toJson());
                tempQueue.pop();
            }
            Reservesarray.append(Queuearray);
        }
    } catch (const std::exception &e) {
        qWarning() << "Error serializing reserves:" << e.what();
        return false;
    };
    libraryObj["Reserves"] = Reservesarray;
    libraryObj["IDcount"] = library.getcurrentId();

    root["Library"] = libraryObj;

    // writing to the file
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
    {
        qWarning() << "Failed to open file for writing";
        return false;
    }

    QJsonDocument doc(root);
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();

    qDebug() << "Save Succecful";
    return true;
}
bool LibraryDataManager::load(Library &library, const QString &filename)
{
    QFile file(filename);

    qDebug() << "Loading file from:" << filename;

    if (!file.exists()) {
        qWarning() << "File does not exist!";
        return false;
    }
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        qWarning() << "Could not open file for reading";
        return false;
    }

    QByteArray rawData = file.readAll(); //reading al data into a QByte Array

    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(rawData); //turning the data into JsonDocument
    if (doc.isNull() || !doc.isObject())
    {
        qWarning() << "Invalid JSON format";
        return false;
    }

    QJsonObject root = doc.object();
    //====Resources======
    QJsonObject libraryobj = root["Library"].toObject();
    QJsonObject resourcesObj = libraryobj.value("Resources").toObject();
    QJsonArray booksArray = resourcesObj.value("Books").toArray();
    QJsonArray articleArray = resourcesObj.value("Articles").toArray();


    for (int i = 0; i < booksArray.size(); i++)
    {
        Book *n = new Book();
        n->FromJson(booksArray[i].toObject());
        library.AddBook(n);
    }
    for (int i = 0; i < articleArray.size(); i++)
    {
        Article *n = new Article();
        n->FromJson(articleArray[i].toObject());
        library.AddArticle(n);

    }

    //====Users=========
    QJsonObject usersObj = libraryobj.value("Users").toObject();
    QJsonArray UsersArray = usersObj.value("Regular Users").toArray();
    QJsonArray AdminsArray = usersObj.value("Admins").toArray();

    for (int i = 0; i < UsersArray.size(); i++)
    {
        User * nu =new User();
        nu->FromJson(UsersArray[i].toObject());
        library.LRegisterUser(nu);

    }
    for (int i = 0; i < AdminsArray.size(); i++)
    {
        Admin *nu = new Admin();
        nu->FromJson(AdminsArray[i].toObject());
        library.LRegisterUser(nu);
    }

    //====Reserves and Loans===========
    QJsonArray waitingArray = libraryobj.value("Waiting").toArray();
    QJsonArray LoansArray = libraryobj.value("Loans").toArray();
    QJsonArray ReservesArray = libraryobj.value("Reserves").toArray();

    for (int i = 0; i < waitingArray.size(); i++) {
        Reserve *w = new Reserve();
        w->FromJson(waitingArray[i].toObject());
        library.PushWaiting(w);
    }
    for (int i = 0; i < LoansArray.size(); i++) {
        Loan *l = new Loan();
        l->FromJson(LoansArray[i].toObject());
        library.PushLoan(l);
    }
    //Queues:
    for (int i = 0; i < ReservesArray.size(); i++) {
        queue<Reserve *> *q = new queue<Reserve *>();
        QJsonArray QueueReserves = ReservesArray[i].toArray();
        for (int j = 0; j < QueueReserves.size(); j++) {
            Reserve *r = new Reserve();
            r->FromJson(QueueReserves[j].toObject());
            q->push(r);
        }

        library.PushReserve(q);
    }

    //currentId
    library.setcurrentId(libraryobj.value("IDcount").toInt());



    return true;
}
