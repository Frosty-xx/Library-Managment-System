#ifndef CHANGEPASSWORD_H
#define CHANGEPASSWORD_H
#include "User.h"

#include <QWidget>

namespace Ui {
class ChangePassword;
}

class ChangePassword : public QWidget
{
    Q_OBJECT

public:
    explicit ChangePassword(User*u, QWidget *parent = nullptr);
    ~ChangePassword();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ChangePassword *ui;
    User *user;
};

#endif // CHANGEPASSWORD_H
