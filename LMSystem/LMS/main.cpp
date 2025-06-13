#include "mainwindow.h"
#include"mainmenu.h"
#include"Library.h"
#include "Admin.h"
#include"LibraryDataManager.h"
#include <QDir>
#include <QApplication>
#include <QPushButton>
#include <QFont>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Library Ensia;
    LibraryDataManager::load(Ensia, QCoreApplication::applicationDirPath() + "/Data/Library.json");
    MainWindow m(&Ensia);
    m.show();

    return a.exec();
}
