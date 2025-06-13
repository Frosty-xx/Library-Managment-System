#ifndef CHANGEUSERNAME_H
#define CHANGEUSERNAME_H
#include "User.h"
#include "Library.h"
#include"mainmenu.h"

#include <QWidget>

namespace Ui {
class ChangeUsername;
}

class ChangeUsername : public QWidget
{
    Q_OBJECT

public:
    explicit ChangeUsername(Library* l,User* u,MainMenu* mm,QWidget *parent = nullptr);
    ~ChangeUsername();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ChangeUsername *ui;
    Library *library;
    User *user;
    MainMenu *m;
};

#endif // CHANGEUSERNAME_H
