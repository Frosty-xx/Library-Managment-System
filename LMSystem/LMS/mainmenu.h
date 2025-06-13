#ifndef MAINMENU_H
#define MAINMENU_H

#include "Library.h"
#include <QStandardItemModel>
#include <QWidget>
#include <QLabel>
#include <QItemSelection>
#include <QPushButton>

namespace Ui {
class MainMenu;
}

class MainMenu : public QWidget
{
    Q_OBJECT
protected:
    void closeEvent(QCloseEvent *event) override;
public:
    explicit MainMenu(Library *l, User *current_user, QWidget *parent = nullptr);
    void LoadAllTables();
    void TableLoad();
    void MYReservesLoad();
    void HistroyLoad();
    void UsersLoad();
    void CBLoad();
    void CRLoad();
    void WLoad();

    void hideAllRecentItems();
    void setARecentItem(QLabel *title, QLabel* Image, QString Title, QPixmap cover);
    void LoadAllRecentItems();

    void ActivateButton(QPushButton *Button);
    void DisableButton(QPushButton *Button);


    void onSelectionChanged();
    void onSelectionChanged2();

    void applychangeusername();
    void LoadStatistics();

    void LoadNotifications();

    ~MainMenu();

private slots:

    void on_ResourcesView_doubleClicked(const QModelIndex &index);

    void on_ClearButton_clicked();

    void on_LogOut_clicked();

    void on_ReserveButton_clicked();

    void on_BorrowButton_clicked();

    void on_ReturnButton_3_clicked();

    void on_SearchField_textChanged(const QString &arg1);

    void on_IdSearchField_textChanged(const QString &arg1);

    void on_AddResButton_clicked();

    void ResourcesViewUpdate(QStandardItemModel* model,vector<Resources*> Results);


    void on_FilterBox_currentTextChanged(const QString &arg1);

    void on_lineEdit_5_textChanged(const QString &arg1);

    void on_MyReservesView_clicked(const QModelIndex &index);

    void on_CancelReserveButton_clicked();

    void on_ChangePassword_clicked();

    void on_Change_Username_clicked();



    void on_AdminSearchTitle_textChanged(const QString &arg1);

    void on_AdminSearchID_textChanged(const QString &arg1);

    void on_AResourcesView_clicked(const QModelIndex &index);

    void on_RemoveButton_clicked();

    void on_OpenfileButton_clicked();

    void on_BackToLibrary_clicked();

    void on_RenewButton_clicked();

    void on_ReturnButton_clicked();


    void on_menu_currentRowChanged(int currentRow);

    void on_AdminSearchUsername_textChanged(const QString &arg1);

    void on_AdminSearchFirstName_textChanged(const QString &arg1);

    void on_outofNotfications_clicked();



    void on_pushButton_2_clicked();

    void on_NotificationButton_clicked();

private:
    User* currentUser;
    Library *library;
    QStandardItemModel *LibraryModel;

    QStandardItemModel *MyReservesModel;
    QStandardItemModel *MyLoaHistoryModel;
    QStandardItemModel *MyResHistoryModel;

    QStandardItemModel *AdminsLibraryModel;
    QStandardItemModel *OriginalUsersModel;

    QStandardItemModel *AllBorrowedModel;
    QStandardItemModel *AllReservationModel;
    QStandardItemModel *WaitingModel;

    QStandardItemModel *NotificationsModel;
    ;

    Ui::MainMenu *ui;
};

#endif // MAINMENU_H
