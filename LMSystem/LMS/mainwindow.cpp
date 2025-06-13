#include "mainwindow.h"
#include "mainmenu.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
MainWindow::MainWindow(Library* l, QWidget *parent)
    : QMainWindow(parent),
    library(l)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_CreateAccountButton_clicked()
{
    Form*f= new Form(library);
    f->show();
    this->close();
}


void MainWindow::on_SignInButton_clicked()
{
    bool allFilled = true;
    bool found = false;
    for (QLineEdit* field : this->findChildren<QLineEdit*>()) {
        if (field->text().trimmed().isEmpty()) {
            allFilled = false;
            break;
        }
    }
    if(!allFilled){
        QMessageBox::warning(this,"Validation","Please fill All Fields");
    }
    else{

        for (User* user:library->getUsers()) {
            if(ui->Usernaemfield->text() == user->getUsername() && ui->passwordfield->text()==user->getPassword()){
            MainMenu* m=new MainMenu(library,user);
            m->show();
            this->close();
            found=true;
            break;
            }
         }
        if(!found){
            QMessageBox::warning(this,"Validation","Wrong Username or Password");
        }
    }

}

