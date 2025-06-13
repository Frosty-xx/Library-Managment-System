#include "changeusername.h"
#include "ui_changeusername.h"
#include<QMessageBox>

ChangeUsername::ChangeUsername(Library* l,User*u,MainMenu* mm,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChangeUsername)
{
    m = mm;
    library = l;
    user = u;
    ui->setupUi(this);
}

ChangeUsername::~ChangeUsername()
{
    delete ui;
}

void ChangeUsername::on_pushButton_clicked()
{
    if (ui->lineEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "Please Fill the filed");
    } else {
        if (library->UsernameTaken(ui->lineEdit->text())) {
            QMessageBox::information(this,
                                     "Error",
                                     "Username Taken \n Please Enter a different Username");
        } else {
            user->setUsername(ui->lineEdit->text());
            QMessageBox::information(this, "Success", "Username Changed");
            m->applychangeusername();
        }
    }
}
