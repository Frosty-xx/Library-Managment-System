#ifndef ARTICLE_H
#define ARTICLE_H
#include "Resources.h"
#pragma once

class Article: public Resources
{
public:
    Article();
    Article(QString title, QString author, int id, bool isAvailable, int availableQuantity,QString Genre,bool elec);
    ~Article();

private:


};

#endif
