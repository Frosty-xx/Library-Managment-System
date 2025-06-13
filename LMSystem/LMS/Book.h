#ifndef BOOK_H
#define BOOK_H
#pragma once
#include "Resources.h"

class Book : public Resources
{
public:
    Book();
    Book(QString title, QString author, int id, bool isAvailable, int availableQuantity,QString Genre,bool elec, int pages );
    ~Book();
    // setters
    void setPages(int pages) { pages < 10 ? Pages = 0 : Pages = pages; };


    // getters
    int getPages() const { return Pages; };

    // Files:
    QJsonObject toJson() override;
    void FromJson(QJsonObject object) override;

private:
    int Pages;
};

#endif
