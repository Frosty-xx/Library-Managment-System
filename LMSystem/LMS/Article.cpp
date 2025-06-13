#include "Article.h"


Article::Article(QString title,
        QString author,
        int id,
        bool isAvailable,
        int availableQuantity,
        QString Genre,
        bool elec)
    : Resources( author,
                 title,
                 id,
                 isAvailable,
                 availableQuantity,
                 Genre,
                 elec)
{


}

Article::Article()
{

}

Article::~Article()
{

}
