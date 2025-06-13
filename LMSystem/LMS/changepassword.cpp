#include "changepassword.h"
#include "ui_changepassword.h"
#include <QMessageBox>

ChangePassword::ChangePassword(User* u,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChangePassword)
{
    user = u;
    ui->setupUi(this);
}

ChangePassword::~ChangePassword()
{
    delete ui;
}

void ChangePassword::on_pushButton_clicked()
{
    if (ui->lineEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "Please Fill the filed");
    } else {
        if (!(User::pass_Lc(ui->lineEdit->text()) && User::pass_Uc(ui->lineEdit->text())
              && User::pass_ge_5(ui->lineEdit->text()) && User::pass_num(ui->lineEdit->text())
              && User::pass_special(ui->lineEdit->text()))) {
            QMessageBox::warning(
                this,
                "Validation",
                "Password too weak:\n -At least 5 characters\n -Include special char \n -Include a "
                "number \n -Include Upper and lower case letter");
        } else {
            QMessageBox::information(this, "succes", "Password Changed");
            user->setUsername(ui->lineEdit->text());
        }
    }
}
