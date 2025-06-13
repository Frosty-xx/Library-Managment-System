#include "adding.h"
#include "ui_adding.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QFileDialog>
Adding::Adding(Library* l , User* u,MainMenu* ma ,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Adding)
{
    library = l;
    m = ma;
    currentUser = u;
    ui->setupUi(this);
    ui->UploadFileButton->setEnabled(false);
    ui->Filename->hide();
    QString style = R"(QPushButton{
            background-color:dark grey;
            border:1px solid black;

        })";
    ui->UploadFileButton->setStyleSheet(style);

    //Validations:
    ui->QuantityField->setValidator(new QIntValidator(0, 999999, this));
    ui->PagesField->setValidator(new QIntValidator(0, 999999, this));

}
Adding::~Adding()
{
    delete ui;




}

void Adding::on_radioButton_2_clicked()
{
    ui->PagesField->hide();
    ui->Pages->hide();
}

void Adding::on_checkBox_checkStateChanged(const Qt::CheckState &arg1)
{
    if (!arg1) {
        ui->UploadFileButton->setEnabled(false);
        QString style = R"(QPushButton{
            background-color:dark grey;
            border:1px solid black;

        })";
        ui->UploadFileButton->setStyleSheet(style);
    } else {
        ui->UploadFileButton->setEnabled(true);
        QString style2 = R"(
QPushButton{
background-color:white;
border:1px solid black;

}
QPushButton::hover{
    background-color: rgb(217, 217, 217);
})";
        ui->UploadFileButton->setStyleSheet(style2);
    }
}

void Adding::on_radioButton_clicked()
{
    ui->PagesField->show();
    ui->Pages->show();
}

void Adding::on_pushButton_3_clicked()
{
    bool AllFilled = true;
    for (QLineEdit *l : this->findChildren<QLineEdit *>()) {
        if (l->isHidden()) {
            continue;
        }
        if (l->text().trimmed().isEmpty()) {
            AllFilled = false;
        }
    }
    if (!AllFilled) {
        QMessageBox::warning(this, "Validation", "Please Fill All Fields");
    } else if (ui->checkBox->isChecked() && ui->UploadFileButton->text() == "Upload File") {
        QMessageBox::warning(this, "Validation", "Please Upload a file");

    }
    else {
        if (ui->radioButton->isChecked()) {
            Book *b = new Book(ui->TitleField->text(),
                               ui->AuthorField->text(),
                               library->getnextId(),
                               ui->QuantityField->text().toInt() == 0 ? 0 : 1,
                               ui->QuantityField->text().toInt(),
                               ui->GenreField->text(),
                               ui->checkBox->isChecked() ? 1 : 0,
                               ui->PagesField->text().toInt());
            if (!ui->Filename->isHidden()) {
                b->setCoverPath(QCoreApplication::applicationDirPath() + "/Data/BookCovers/" + ui->Filename->text());
            }
            if (ui->checkBox->isChecked()) {
                b->setPdfPath(QCoreApplication::applicationDirPath() + "/Data/ElectronicResources/" + ui->UploadFileButton->text());
            }


            library->AddBook(b);
            QMessageBox::information(this, "Success", " Book Added succesfully");

        }

        else {
            Article *a = new Article(ui->TitleField->text(),
                                     ui->AuthorField->text(),
                                     library->getnextId(),
                                     ui->QuantityField->text().toInt() == 0 ? 0 : 1,
                                     ui->QuantityField->text().toInt(),
                                     ui->GenreField->text(),
                                     ui->checkBox->isChecked() ? 1 : 0);
            if (!ui->Filename->isHidden()) {
                a->setCoverPath(QCoreApplication::applicationDirPath() + "/Data/BookCovers/" + ui->Filename->text());
            }
            if (ui->checkBox->isChecked()) {
                a->setPdfPath(QCoreApplication::applicationDirPath() + "/Data/ElectronicResources/" + ui->UploadFileButton->text());
            }

            library->AddArticle(a);


            QMessageBox::information(this, "Success", "Article Added succesfully");

            // clears:
            for (QLineEdit *l : this->findChildren<QLineEdit *>()) {

                l->setText("\0");
            }
            ui->Filename->hide();
            ui->checkBox->setChecked(0);
            ui->UploadFileButton->setText("Upload File");
        }
        //updates the tables
        m->LoadAllTables();
    }
    // Reload the Table;




}

void Adding::on_UploadCoverButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Open a file",
                                                    "",
                                                    "Images (*.png *.jpg *.jpeg *.bmp)");

    if (fileName.isEmpty()) {
        qDebug() << "No file selected.";
        return;
    }

    QFileInfo fileInfo(fileName);
    QString suffix = fileInfo.suffix().toLower();

    if (!(suffix == "jpg" || suffix == "jpeg" || suffix == "png" || suffix == "bmp")) {
        QMessageBox::warning(this, "invalid format", " Invalid FormatFile!");

        return;
    }

    QString targetDir = QCoreApplication::applicationDirPath() + "/Data/BookCovers/";
    QDir().mkpath(targetDir); // Makes sure the folder exists

    QString targetPath = targetDir + fileInfo.fileName();

    if (QFile::copy(fileName, targetPath)) {
        qDebug() << "File saved to:" << targetPath;
    } else {
        qDebug() << "Failed to save file.";
    }
    ui->Filename->setText(fileInfo.fileName());
    ui->Filename->show();
}

void Adding::on_UploadFileButton_clicked()
{
    QString Filename = QFileDialog::getOpenFileName(this, "Open a file");
    if (Filename.isEmpty()) {
        qDebug() << "No file selected.";
        return;
    }
    QFileInfo fileinfo(Filename);
    QString suffix = fileinfo.suffix().toLower();
    if (suffix != "pdf") {
        QMessageBox::warning(this, "invalid format", " Invalid FormatFile!");

        return;
    }
    // copying the file;
    QString targetDir = QCoreApplication::applicationDirPath() + "/Data/ElectronicResources/";
    QDir().mkpath(targetDir); // Makes sure the folder exists
    QString targetPath = targetDir + fileinfo.fileName();
    if (QFile::copy(Filename, targetPath)) {
        qDebug() << "File saved to:" << targetPath;
    } else {
        qDebug() << "Failed to save file.";
    }
    ui->UploadFileButton->setText(fileinfo.fileName());
}
