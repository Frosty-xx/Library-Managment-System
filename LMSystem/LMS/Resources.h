#ifndef RESOURCES_H
#define RESOURCES_H
#pragma once
#include <QJsonObject>
#include <Qstring>
using namespace std;

class Resources
{
public:
    Resources();
    Resources(QString author,QString title,int id,bool isavailable,int quantity,QString Genre,bool electornic);
    virtual ~Resources();
    // setters
    void setAuthor(QString author) { Author = author; };
    void setTitle(QString title) { Title = title; };
    void setIsAvailable(bool isAvailable) { IsAvailable = isAvailable; };
    void setavailableQuantity(int quantity) { quantity < 0 ? availableQuantity = 0 : availableQuantity = quantity; };
    void setId(int id) { Id = id; };
    void setCoverPath(QString path) { Cover = path; };
    void setPdfPath(QString Path) { PDf = Path; };

    // getters
    QString getAuthor() const { return Author;};
    QString getTitle() const { return Title; };
    QString getGenre() const { return Genre; };
    bool getIsAvailable() const { return IsAvailable; };
    int getavailableQuantity() const { return availableQuantity; };
    bool getisElectronic() const { return electronic; };
    QString getCoverPath() const { return Cover; };
    QString getPdfPath() const { return PDf; };

    int getId() const { return Id; };

    // FileManagment
    virtual QJsonObject toJson();
    virtual void FromJson(QJsonObject object);

    //operators:
    bool operator==(const Resources& other);
    //utility functions:
    bool matching( const QString &title); // works the search function in the library class

private:
    QString Author;
    QString Title;
    QString Genre;
    int Id;
    bool IsAvailable;
    int availableQuantity;
    bool electronic;
    QString Cover;
    QString PDf;

};

#endif
