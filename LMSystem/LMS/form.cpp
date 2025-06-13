#include "form.h"
#include "ui_form.h"
#include "Library.h"
#include "Date.h"
#include "LibraryDataManager.h"
#include "Admin.h"
#include "User.h"
#include "mainwindow.h"
#include <QMessageBox>

Form::Form(Library* l,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Form)
{
    library=l;
    ui->setupUi(this);

}




Form::~Form()
{
    delete ui;
}

void Form::on_CreateButton_clicked()
{
    bool allFilled = true;

    for (QLineEdit* field : this->findChildren<QLineEdit*>()) {
        if (field->text().trimmed().isEmpty()) {
            allFilled = false;
            break;
        }
    }

    if (!allFilled) {
        QMessageBox::warning(this, "Validation", "Please fill in all fields.");
    }
    else{

        if(!User::emailcheck(ui->EmailField->text())){
            QMessageBox::warning(this,"Validation","Please Enter A valid Email.");
            return;
        }
        if(!(User::pass_Lc(ui->PasswordField->text()) && User::pass_Uc(ui->PasswordField->text()) && User::pass_ge_5(ui->PasswordField->text()) && User::pass_num(ui->PasswordField->text()) && User::pass_special(ui->PasswordField->text()))){
            QMessageBox::warning(this,"Validation","Password too weak:\n -At least 5 characters\n -Include special char \n -Include a number \n -Include Upper and lower case letter");
            return;
        }
        if(!User::phonecheck(ui->PhoneField->text())){
            QMessageBox::warning(this,"Validation","Incorrect Phone Format");
            return;
        }
        //checking if the username is taken before
        if (library->UsernameTaken(ui->Userfield->text())) {
            QMessageBox::information(this, "Validation", "Username Taken Before\n Please Change Your username");
            return;
        }
        //Fields are valid
        if(ui->YesAdmin->isChecked()){
            Admin* a = new Admin();
            a->setEmail(ui->EmailField->text());
            a->setFirstName(ui->FirstNameField->text());
            a->setPhoneNumber(ui->PasswordField->text());
            a->setLastName(ui->LastNameField->text());
            a->setPassword(ui->PasswordField->text());
            a->setUsername(ui->Userfield->text());
            Date d;
            d.apply_currentDate();
            a->setDateRegistgered(d.toString());
            //Registering
            library->LRegisterUser(a);
            QMessageBox::information(this,"Success","Admin created with Sucess");
            LibraryDataManager::save(*library,"C:/Users/Millenium/Desktop/LibraryManagementSystem/LMS/Data/Library.json");
            MainWindow *w = new MainWindow(library);
            this->close();
            w->show();
        }
        else{
            User* u = new User();
            u->setEmail(ui->EmailField->text());
            u->setFirstName(ui->FirstNameField->text());
            u->setPhoneNumber(ui->PasswordField->text());
            u->setLastName(ui->LastNameField->text());
            u->setPassword(ui->PasswordField->text());
            u->setUsername(ui->Userfield->text());
            //aplying date
            Date d;
            d.apply_currentDate();
            u->setDateRegistgered(d.toString());
            //Registering
            library->LRegisterUser(u);
            QMessageBox::information(this,"Success","User created with Sucess");
            LibraryDataManager::save(*library,
                                     QCoreApplication::applicationDirPath() + "/Data/Library.json");            MainWindow* w=new MainWindow(library);
            this->close();
            w->show();
        }
    }

}

void Form::on_pushButton_clicked()
{
    this->close();
    MainWindow *w = new MainWindow(library);
    w->show();

}
