#ifndef LIBRARYDATAMANAGER_H
#define LIBRARYDATAMANAGER_H
#include <Qstring>
#include "Library.h"
#pragma once

class LibraryDataManager
{
public:
    LibraryDataManager();
    ~LibraryDataManager();

    static bool save(const Library &library, const QString &filename);
    static bool load(Library &library, const QString &filename);

private:
};

#endif