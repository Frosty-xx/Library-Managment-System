#include "mainmenu.h"
#include <QMessageBox>
#include <QStandardItemModel>
#include <QDesktopServices>
#include <QStringListModel>
#include <Qstring>
#include "Admin.h"
#include "LibraryDataManager.h"
#include "adding.h"
#include "changepassword.h"
#include "changeusername.h"
#include "mainwindow.h"
#include "qdir.h"
#include "ui_mainmenu.h"
#include <cxxabi.h> //to demangle typeinfo().name() (removes the number before the word)
#include <typeinfo>

bool inItemDetails=false;
void MainMenu::hideAllRecentItems()
{
    ui->Title1->hide();
    ui->Title2->hide();
    ui->Title3->hide();
    ui->Title4->hide();
    ui->Title5->hide();
    ui->Title6->hide();
    ui->Image1->hide();
    ui->Image2->hide();
    ui->Image3->hide();
    ui->Image4->hide();
    ui->Image5->hide();
    ui->Image6->hide();
}
void MainMenu::setARecentItem(QLabel *title, QLabel *Image, QString Title, QPixmap cover)
{
    title->setText(Title);
    title->show();
    Image->setPixmap(cover);
    Image->show();
}
void MainMenu::LoadAllRecentItems()
{
    int count = 1;
    vector<Resources *> copy = library->getAll_Resources();
    while (count < 7 && !copy.empty()) {
        switch (count) {
        case 1:
            if (copy.back()->getCoverPath() != "\0") {
                QPixmap cover(copy.back()->getCoverPath());
                setARecentItem(ui->Title1, ui->Image1, copy.back()->getTitle(), cover);
            }else {
                QPixmap cover(":/Pictures/Book Cover-01.svg");
                setARecentItem(ui->Title1, ui->Image1, copy.back()->getTitle(), cover);
            };

            copy.pop_back();
            count++;

            break;
        case 2:

            if (copy.back()->getCoverPath() != "\0") {
                QPixmap cover(copy.back()->getCoverPath());
                setARecentItem(ui->Title2, ui->Image2, copy.back()->getTitle(), cover);
            }else {
                QPixmap cover(":/Pictures/Book Cover-01.svg");
                setARecentItem(ui->Title2, ui->Image2, copy.back()->getTitle(), cover);
            };

            copy.pop_back();
            count++;
            break;
        case 3:
            if (copy.back()->getCoverPath() != "\0") {
                QPixmap cover(copy.back()->getCoverPath());
                setARecentItem(ui->Title3, ui->Image3, copy.back()->getTitle(), cover);
            }else {
                QPixmap cover(":/Pictures/Book Cover-01.svg");
                setARecentItem(ui->Title3, ui->Image3, copy.back()->getTitle(), cover);
            };

            copy.pop_back();
            count++;
            break;
        case 4:
            if (copy.back()->getCoverPath() != "\0") {
                QPixmap cover(copy.back()->getCoverPath());
                setARecentItem(ui->Title4, ui->Image4, copy.back()->getTitle(), cover);
            }else {
                QPixmap cover(":/Pictures/Book Cover-01.svg");
                setARecentItem(ui->Title4, ui->Image4, copy.back()->getTitle(), cover);
            };

            copy.pop_back();
            count++;
            break;
        case 5:
            if (copy.back()->getCoverPath() != "\0") {
                QPixmap cover(copy.back()->getCoverPath());
                setARecentItem(ui->Title5, ui->Image5, copy.back()->getTitle(), cover);
            }else {
                QPixmap cover(":/Pictures/Book Cover-01.svg");
                setARecentItem(ui->Title5, ui->Image5, copy.back()->getTitle(), cover);
            };

            copy.pop_back();
            count++;
            break;
        case 6:
            if (copy.back()->getCoverPath() != "\0") {
                QPixmap cover(copy.back()->getCoverPath());
                setARecentItem(ui->Title6, ui->Image6, copy.back()->getTitle(), cover);
            }else {
                QPixmap cover(":/Pictures/Book Cover-01.svg");
                setARecentItem(ui->Title6, ui->Image6, copy.back()->getTitle(), cover);
            };

            copy.pop_back();
            count++;
            break;
        default:
            break;
        }
    }

}
void MainMenu::LoadAllTables()
{
    TableLoad();
    MYReservesLoad();
    HistroyLoad();
    UsersLoad();
    CBLoad();
    CRLoad();
    WLoad();
    LoadStatistics();
    LoadNotifications();
    LoadAllRecentItems();
}
void MainMenu::ActivateButton(QPushButton *Button)
{
    Button->setEnabled(1);
    QString style = R"(QPushButton{
background-color:#059862;
color:white;
border:1px solid black;
border-radius:2px;
padding:7px 5px;
}
QPushButton::hover{

background-color:#04AA6D;
})";
    Button->setStyleSheet(style);
}

void MainMenu::DisableButton(QPushButton *Button)
{
    Button->setEnabled(0);
    QString style = R"(QPushButton{
background-color:#D9EEE1;
color:white;
border:1px solid black;
border-radius:2px;
padding:7px 5px;
}
)";
    Button->setStyleSheet(style);

}
void MainMenu::onSelectionChanged()
{
    bool hasSelection = !ui->ResourcesView->selectionModel()->selectedRows().isEmpty();
    if (hasSelection) {
        ActivateButton(ui->ReturnButton);

    } else {
        DisableButton(ui->ReturnButton);
    }

}
void MainMenu::onSelectionChanged2()
{
    bool hasSelection = !ui->UsersView->selectionModel()->selectedRows().isEmpty();
    if (hasSelection) {
        ActivateButton(ui->RemoveUser);

    } else {
        DisableButton(ui->RemoveUser);
    }

}

MainMenu::MainMenu(Library* l,User* u,QWidget *parent)
    : QWidget(parent),
    currentUser(u),
    library(l)
    , ui(new Ui::MainMenu)
{

    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->DUsername->setText(currentUser->getUsername());
    ui->CancelReserveButton->setEnabled(0);
    ui->RenewButton->setEnabled(0);
    ui->RemoveButton->setEnabled(0);
    hideAllRecentItems();
    LoadAllRecentItems();
    ui->AdminSearchID->setValidator(new QIntValidator(1, 999999, this));
    ui->IdSearchField->setValidator(new QIntValidator(1, 99999999, this));

    //Showing menu according to User Type
    if (!dynamic_cast<Admin *>(currentUser)) {
        ui->menu->item(5)->setHidden(true);
        ui->menu->item(6)->setHidden(true);
    }
    LoadAllTables();
    ui->ResourcesView->setColumnWidth(0, 300);
    ui->ResourcesView->setColumnWidth(1, 150);
    //=====================Page2=========================================

    DisableButton(ui->ReturnButton);
    connect(ui->ResourcesView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &MainMenu::onSelectionChanged);
    connect(ui->UsersView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &MainMenu::onSelectionChanged2);
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::on_LogOut_clicked()
{
    LibraryDataManager::save(*library,
                             QCoreApplication::applicationDirPath() + "/Data/Library.json");
    this->close();
    MainWindow* w=new MainWindow(library,nullptr);
    w->show();
}


void MainMenu::on_ClearButton_clicked()
{
    ui->SearchField->setText("\0");
    ui->IdSearchField->setText("\0");
    TableLoad();
    ui->ResourcesView->setColumnWidth(0, 200);
    ui->ResourcesView->setColumnWidth(1, 150);
    ui->FilterBox->setCurrentIndex(0);
}


//puplic methods:
void MainMenu::TableLoad()
{
    //Modeling the table view
    LibraryModel = new QStandardItemModel(0, 5, this);
    AdminsLibraryModel = new QStandardItemModel(0, 5, this);

    QList<QString> Labels;
    Labels << "Title" << "Author" << "Type" << "Genre" << "Quantity"<<"ID";
    LibraryModel->setHorizontalHeaderLabels(Labels);
    AdminsLibraryModel->setHorizontalHeaderLabels(Labels);

    // make the model from library Data.
    for (Resources *item : library->getAll_Resources()) {
        QList<QStandardItem *> row1;
        QList<QStandardItem *> row2;
        row1 << new QStandardItem(item->getTitle())
             << new QStandardItem(item->getAuthor())
             << new QStandardItem(abi::__cxa_demangle(typeid(*item).name(), 0, 0, 0))
             << new QStandardItem(item->getGenre())
             << new QStandardItem(QString::fromStdString(to_string(item->getavailableQuantity())))
        << new QStandardItem(QString::number(item->getId()));

        LibraryModel->appendRow(row1);
        for (QStandardItem *r : row1) {
            row2.append(r->clone());
        }
        AdminsLibraryModel->appendRow(row2);

    }

    ui->ResourcesView->setModel(LibraryModel);
    ui->AResourcesView->setModel(AdminsLibraryModel);


}



void MainMenu::on_SearchField_textChanged(const QString &arg1)
{
    QString Title = arg1;
    QString Filter = ui->FilterBox->currentText();
    int ID = ui->IdSearchField->text().trimmed().isEmpty() ? -1 : ui->IdSearchField->text().toInt();


    ResourcesViewUpdate(LibraryModel,library->LSearchTitle(Title, Filter, ID));
    DisableButton(ui->ReturnButton);

}
void MainMenu::on_IdSearchField_textChanged(const QString &arg1)
{
    int ID = arg1=="\0"?-1:arg1.toInt();
    QString Title = ui->SearchField->text().isEmpty()?"\0":ui->SearchField->text();

    QString Filter = ui->FilterBox->currentText();

    ResourcesViewUpdate(LibraryModel,library->LSearchTitle(Title, Filter, ID));
     DisableButton(ui->ReturnButton);
}

void MainMenu::on_FilterBox_currentTextChanged(const QString &arg1)
{
    int Id = ui->IdSearchField->text().isEmpty() ? -1 : ui->IdSearchField->text().toInt();
    QString title;
    ResourcesViewUpdate(LibraryModel,library->LSearchTitle(title,arg1,Id));
    DisableButton(ui->ReturnButton);
}



void MainMenu::HistroyLoad()
{
    MyLoaHistoryModel = new QStandardItemModel(0, 4, this);
    MyResHistoryModel = new QStandardItemModel(0, 2, this);

    QList<QString> lables;
    lables << "Title" << "Date Borrowed" << "Is returned" << "Date Returned";
    MyLoaHistoryModel->setHorizontalHeaderLabels(lables);

    QList<QString> lables2;
    lables2 << "Title" << "Date Reserved";
    MyResHistoryModel->setHorizontalHeaderLabels(lables2);

    for (unsigned int var = 0; var < currentUser->getLHistory().size(); ++var) {
        QList<QStandardItem *> row;
        row << new QStandardItem(currentUser->getLHistory()[var]->getTitle())
            << new QStandardItem(currentUser->getLHistory()[var]->get_date_borrowed())
            << new QStandardItem(currentUser->getLHistory()[var]->get_returned() ? "Yes" : "No")
            << new QStandardItem(currentUser->getLHistory()[var]->get_date_returned());
       MyLoaHistoryModel->appendRow(row);
    }
    for (Reserve *r : currentUser->getRHistory()) {
        QList<QStandardItem *> row;
        row << new QStandardItem(r->getTitle())
            << new QStandardItem(r->get_date_reserved());
        MyResHistoryModel->appendRow(row);
    }
    ui->LoansHistory->setModel(MyLoaHistoryModel);
    ui->ReserevsHistory->setModel(MyResHistoryModel);
}
void MainMenu::MYReservesLoad()
{
    MyReservesModel = new QStandardItemModel(0, 3, this);
    QList<QString> Lables;
    Lables << "Title" << "Date Reserved"  <<"ID";
    MyReservesModel->setHorizontalHeaderLabels(Lables);

    for (Reserve *r : currentUser->getReserves()) {
        QList<QStandardItem *> row;
        row << new QStandardItem(r->getTitle()) << new QStandardItem(r->get_date_reserved())
            << new QStandardItem(QString::number(r->getId()));
        MyReservesModel->appendRow(row);
    }
    ui->MyReservesView->setModel(MyReservesModel);


}
void MainMenu::UsersLoad()
{
    OriginalUsersModel = new QStandardItemModel(0, 6, this);
    QList<QString> lables;
    lables << "Username" << "First-Name" << "Last-Name" << "Email" << "Phone" << "Type"<< "Date Registered" ;
    OriginalUsersModel->setHorizontalHeaderLabels(lables);
    for (unsigned int i = 0; i < library->getUsers().size(); ++i) {
            QList<QStandardItem *> row;
            row << new QStandardItem(library->getUsers()[i]->getUsername())
                << new QStandardItem(library->getUsers()[i]->getFirstName())
                << new QStandardItem(library->getUsers()[i]->getLastName())
                << new QStandardItem(library->getUsers()[i]->getEmail())
                << new QStandardItem(library->getUsers()[i]->getPhoneNumber())
                << new QStandardItem(dynamic_cast<Admin*>(library->getUsers()[i])?"Admin":"Regular")
                << new QStandardItem(library->getUsers()[i]->getDateRegistered());
            OriginalUsersModel->appendRow(row);
    }
    ui->UsersView->setModel(OriginalUsersModel);
}

void MainMenu::CRLoad()
{
    AllReservationModel = new QStandardItemModel(0, 3, this);

    QList<QString> lables;
    lables << " Username" << "Title" << "Date Reserved";
    AllReservationModel->setHorizontalHeaderLabels(lables);
    for (queue<Reserve *> *q : library->getReserves()) {
        queue<Reserve *> copy = *q;
        while (!copy.empty()) {
            QList<QStandardItem *> row;
            row << new QStandardItem(copy.front()->getUsername())
                << new QStandardItem(copy.front()->getTitle())
                << new QStandardItem(copy.front()->get_date_reserved());
            AllReservationModel->appendRow(row);
            copy.pop();
        }
    }
    ui->CReservedItems->setModel(AllReservationModel);
}
void MainMenu::CBLoad()
{
    AllBorrowedModel = new QStandardItemModel(0, 3, this);

    QList<QString> lables;
    lables << " Username" << "Title" << "Date Borrowed";
    AllBorrowedModel->setHorizontalHeaderLabels(lables);
    for (Loan *l : library->getLoans()) {
        QList<QStandardItem *> row;


        row << new QStandardItem(l->getUsername()) << new QStandardItem(l->getTitle())
            << new QStandardItem(l->get_date_borrowed());
        AllBorrowedModel->appendRow(row);
    }

    ui->CBorrowedItems->setModel(AllBorrowedModel);
}
void MainMenu::WLoad()
{
    WaitingModel = new QStandardItemModel(0, 3, this);
    QList<QString> Lables;
    Lables << " Username" << "Title" << "Date Reserved";
    WaitingModel->setHorizontalHeaderLabels(Lables);

    for (Reserve *r : library->getWaiting()) {
        QList<QStandardItem *> row;
        row << new QStandardItem(r->getUsername()) << new QStandardItem(r->getTitle())
            << new QStandardItem(r->get_date_reserved());

        WaitingModel->appendRow(row);
    }

    ui->CWaiting->setModel(WaitingModel);

}









void MainMenu::on_ResourcesView_doubleClicked(const QModelIndex &index) {
    ui->stackedWidget->setCurrentIndex(7);
    inItemDetails = true;
    int ID = LibraryModel->index(index.row(), 5).data().toInt();
    QString Type = LibraryModel->index(index.row(), 2).data().toString();
    Resources *item = nullptr;
    if (Type == "Book") {
        for (Resources *r : library->getBooks()) {
            if (r->getId() == ID) {
                item = r;
            }
        }
    } else {
        for (Resources *r : library->getArticles()) {
            if (r->getId() == ID) {
                item = r;
            }
        }
    }

    ui->DTitle->setText(item->getTitle());
    ui->DAuthor->setText(item->getAuthor());
    ui->DGenre->setText(item->getGenre());
    ui->DID->setText(QString::fromStdString(to_string(item->getId())));
    ui->DEBookArticle->setText(item->getisElectronic()?"yes":"no");
    if (item->getCoverPath() != "\0") {
        QPixmap cover(item->getCoverPath());
        ui->CoverPhoto->setPixmap(cover);
    } else {
        QPixmap cover(":/Pictures/Book Cover-01.svg");
        ui->CoverPhoto->setPixmap(cover);
    };

    if (item->getisElectronic()) {
        ui->OpenfileButton->show();
    } else {
        ui->OpenfileButton->hide();
    }
}

void MainMenu::closeEvent(QCloseEvent *event)
{
    LibraryDataManager::save(*library, QCoreApplication::applicationDirPath() + "/Data/Library.json");
    event->accept();
}













void MainMenu::on_ReserveButton_clicked()
{
    bool alreadyR = false;
    bool alreadyB = false;
    library->LReserveItem(currentUser, ui->DID->text().toInt(), alreadyR,alreadyB);
    if (alreadyR ) {
        QMessageBox::warning(this, "Validation", "Item Already Reserved!");
        return;
    } else if (alreadyB) {
        QMessageBox::warning(this, "Validation", "Item Already Borrowed!");
        return;
    }
    QMessageBox::information(this, "Sucess", "Item Reserved with success");
    LoadAllTables();
}

void MainMenu::on_BorrowButton_clicked()
{
    bool AlreadyB = false;
    if (library->LBorrowItem(currentUser, ui->DID->text().toInt(),AlreadyB)) {
        QMessageBox::information(this, "Success", "Item Borrowed with success");
    } else if (AlreadyB) {
        QMessageBox::warning(this, "Failure", "Item Already Borrowed");
    } else {
        QMessageBox::information(this,
                                 "Out of Stock!",
                                 "Item not available, Feel free to make a reservation");
    }
    LoadAllTables();

}

void MainMenu::on_ReturnButton_3_clicked()
{
    if (library->LReturnItem(currentUser, ui->DID->text().toInt())) {
        QMessageBox::information(this, "success", "Item Returned with success");

    } else {
        QMessageBox::warning(this, "Error", "You haven't Borrowed this item");
    }
    LoadAllTables();
}












void MainMenu::on_AddResButton_clicked()
{
    Adding *a = new Adding(library, currentUser,this);
    a->show();
}








//Helping methods:
void MainMenu::ResourcesViewUpdate(QStandardItemModel*model,vector<Resources *> Results)
{
    model->clear();
    //remaking the model after search:
    QList<QString> Labels;
    Labels << "Title" << "Author" << "Type" << "Genre" << "Quantity" << "ID";
    model->setHorizontalHeaderLabels(Labels);


    for (Resources *item : Results) {
        QList<QStandardItem *> row;
        row << new QStandardItem(item->getTitle()) << new QStandardItem(item->getAuthor())
            << new QStandardItem(abi::__cxa_demangle(typeid(*item).name(), 0, 0, 0))
            << new QStandardItem(item->getGenre())
            << new QStandardItem(QString::number(item->getavailableQuantity()))
            << new QStandardItem(QString::number(item->getId()));
        model->appendRow(row);
    }
}

void MainMenu::on_lineEdit_5_textChanged(const QString &arg1)
{
    DisableButton(ui->CancelReserveButton);
    MyReservesModel->clear();
    QList<QString> Lables;
    Lables << "Title" << "Date Reserved" << "People Ahead";
    MyReservesModel->setHorizontalHeaderLabels(Lables);
    bool match = true;
    for (Reserve *r : currentUser->getReserves()) {
        if (arg1.length() > r->getTitle().length()) {
            match = false;
        } else {
            for (int i = 0; i < arg1.length(); i++) {
                if (arg1[i].toLower() != r->getTitle()[i].toLower() && arg1 != "\0") {
                    match = false;
                    break;
                }
            }
            if (match) {
                QList<QStandardItem *> row;
                row << new QStandardItem(r->getTitle())
                    << new QStandardItem(r->get_date_reserved());
                MyReservesModel->appendRow(row);
            }
        }
    }
}

void MainMenu::on_MyReservesView_clicked(const QModelIndex &index)
{
    ActivateButton(ui->CancelReserveButton);
}

void MainMenu::on_CancelReserveButton_clicked()
{
    int rowselected = ui->MyReservesView->selectionModel()->selectedRows().first().row();
    int ID = MyReservesModel->index(rowselected, 2).data().toInt();
    if (library->LibraryCencelReserve(currentUser, ID)) {
        QMessageBox::information(this, "Info", "Reservation Canceled");
        LoadAllTables();
    } else {
        QMessageBox::warning(this, "Error", "Couldn't Cancel The Reserve");
    }
}

void MainMenu::on_ChangePassword_clicked()
{
    ChangePassword *c = new ChangePassword(currentUser);
    c->show();
}

void MainMenu::on_Change_Username_clicked()
{
    ChangeUsername *c = new ChangeUsername(library, currentUser,this);
    c->show();
}

void MainMenu::on_AdminSearchTitle_textChanged(const QString &arg1)
{
    int ID = ui->AdminSearchID->text().trimmed().isEmpty() ? -1 : ui->AdminSearchID->text().toInt();

    ResourcesViewUpdate(AdminsLibraryModel, library->LSearchTitle(arg1, "None", ID));


    DisableButton(ui->RenewButton);
    DisableButton(ui->RemoveButton);
}

void MainMenu::on_AdminSearchID_textChanged(const QString &arg1)
{
    int ID = arg1.trimmed().isEmpty() ? -1 : arg1.toInt();
    QString Title = ui->AdminSearchTitle->text();
    ResourcesViewUpdate(AdminsLibraryModel, library->LSearchTitle(Title, "None", ID));

    DisableButton(ui->RenewButton);
    DisableButton(ui->RemoveButton);
}

void MainMenu::on_AResourcesView_clicked(const QModelIndex &index)
{
    ActivateButton(ui->RenewButton);
    ActivateButton(ui->RemoveButton);
}

void MainMenu::on_RemoveButton_clicked()
{
    int SelectedRow = ui->AResourcesView->selectionModel()->selectedRows().front().row();
    int ID = AdminsLibraryModel->index(SelectedRow, 5).data().toInt();
    QString Type = AdminsLibraryModel->index(SelectedRow, 2).data().toString();
    library->LRemoveItem(currentUser, ID, Type);
    LoadAllTables();
}

void MainMenu::on_OpenfileButton_clicked()
{
    QString filePath;
    for (Resources *r : library->getAll_Resources()) {
        if (r->getId() == ui->DID->text().toInt()) {
            filePath = r->getPdfPath();
        }
    }
    QFile file(filePath);
    if (QFile::exists(filePath)) {
        QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
    } else {
        qDebug() << "File doesn't exist!";
    }
}

void MainMenu::on_BackToLibrary_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    inItemDetails = false;
}

void MainMenu::on_RenewButton_clicked()
{
    int rowS = ui->AResourcesView->selectionModel()->selectedRows().front().row();
    int ID = AdminsLibraryModel->index(rowS, 5).data().toInt();
    if (library->LRenewItem(currentUser, ID, ui->spinBox->value())) {
        QMessageBox::information(this, "Renewed", "Item renewed");
    } else {
        QMessageBox::warning(this, "Error", "Couldn't Renew Item");
    }
    LoadAllTables();

}

void MainMenu::on_ReturnButton_clicked()
{
    int selectedRow = ui->ResourcesView->selectionModel()->selectedRows().front().row();
    int ID = LibraryModel->index(selectedRow, 5).data().toInt();
    if (library->LReturnItem(currentUser, ID)) {
        QMessageBox::information(this, "success", "Item Returned with success");

    } else {
        QMessageBox::warning(this, "Error", "You haven't Borrowed this item");
    }
    LoadAllTables();
    DisableButton(ui->ReturnButton);

}

void MainMenu::on_menu_currentRowChanged(int currentRow)
{
    if (currentRow == 0) {
        if (inItemDetails)
            ui->stackedWidget->setCurrentIndex(7);
        else
            ui->stackedWidget->setCurrentIndex(0);
    }
}

void MainMenu::on_AdminSearchUsername_textChanged(const QString &arg1)
{
    DisableButton(ui->RemoveUser);

    QString username = arg1;
    QString FirstName = ui->AdminSearchFirstName->text().trimmed();

    OriginalUsersModel->clear();
    QList<QString> lables;
    lables << "Username" << "First-Name" << "Last-Name" << "Email" << "Phone" << "Type"
           << "Date Registered";
    OriginalUsersModel->setHorizontalHeaderLabels(lables);
    for (unsigned int i = 0; i < library->LSearchUsers(username, FirstName).size(); ++i) {
        QList<QStandardItem *> row;
        row << new QStandardItem(library->getUsers()[i]->getUsername())
            << new QStandardItem(library->getUsers()[i]->getFirstName())
            << new QStandardItem(library->getUsers()[i]->getLastName())
            << new QStandardItem(library->getUsers()[i]->getEmail())
            << new QStandardItem(library->getUsers()[i]->getPhoneNumber())
            << new QStandardItem(dynamic_cast<Admin *>(library->getUsers()[i]) ? "Admin" : "Regular")
            << new QStandardItem(library->getUsers()[i]->getDateRegistered());
        OriginalUsersModel->appendRow(row);
    }
}

void MainMenu::on_AdminSearchFirstName_textChanged(const QString &arg1)
{
    DisableButton(ui->RemoveUser);

    QString username = ui->AdminSearchUsername->text().trimmed();
    QString FirstName = arg1;

    OriginalUsersModel->clear();
    QList<QString> lables;
    lables << "Username" << "First-Name" << "Last-Name" << "Email" << "Phone" << "Type"
           << "Date Registered";
    OriginalUsersModel->setHorizontalHeaderLabels(lables);
    for (unsigned int i = 0; i < library->LSearchUsers(username, FirstName).size(); ++i) {
        QList<QStandardItem *> row;
        row << new QStandardItem(library->getUsers()[i]->getUsername())
            << new QStandardItem(library->getUsers()[i]->getFirstName())
            << new QStandardItem(library->getUsers()[i]->getLastName())
            << new QStandardItem(library->getUsers()[i]->getEmail())
            << new QStandardItem(library->getUsers()[i]->getPhoneNumber())
            << new QStandardItem(dynamic_cast<Admin *>(library->getUsers()[i]) ? "Admin" : "Regular")
            << new QStandardItem(library->getUsers()[i]->getDateRegistered());
        OriginalUsersModel->appendRow(row);
    }
}

void MainMenu::applychangeusername()
{
    ui->DUsername->setText(currentUser->getUsername());
}
void MainMenu::LoadStatistics()
{
    ui->TUsers->setText(QString::number(library->getUsers().size()));
    ui->TResources->setText(QString::number(library->getAll_Resources().size()));
    ui->TBooks->setText(QString::number((library->getBooks().size())));
    ui->TArticles->setText((QString::number(library->getArticles().size())));

    int count = 0;
    for (User *u : library->getUsers()) {
        if (dynamic_cast<Admin *>(u)) {
            count++;
        }
    }

    ui->TAdmins->setText(QString::number(count));
}

void MainMenu::on_outofNotfications_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void MainMenu::LoadNotifications()
{
    if (currentUser->getNotifications().empty()) {
        QIcon notificationIc(":/Icons/whiteNotifications.ico");
        ui->NotificationButton->setIcon(notificationIc);
    } else {
        QIcon notificationIC(":/Icons/icons8-notification-50.ico");
        ui->NotificationButton->setIcon(notificationIC);
    }


    NotificationsModel = new QStandardItemModel(0, 2, this);
    for (Notification *n : currentUser->getNotifications()) {
        QList<QStandardItem *> row;
        row << new QStandardItem(n->getText()) << new QStandardItem(n->getDate());
        NotificationsModel->appendRow(row);
    }
    ui->NotificationsView->setModel(NotificationsModel);
}

void MainMenu::on_pushButton_2_clicked()
{
    currentUser->ClearAllNotifications();
    LoadNotifications();
}

void MainMenu::on_NotificationButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}
