#ifndef ADDING_H
#define ADDING_H
#include "mainmenu.h"
#include "Library.h"

#include <QWidget>

namespace Ui {
class Adding;
}

class Adding : public QWidget
{
    Q_OBJECT

public:
    explicit Adding(Library* l, User* currentUser,MainMenu* m,QWidget *parent = nullptr);
    ~Adding();

private slots:
    void on_radioButton_2_clicked();

    void on_checkBox_checkStateChanged(const Qt::CheckState &arg1);

    void on_radioButton_clicked();

    void on_pushButton_3_clicked();


    void on_UploadCoverButton_clicked();

    void on_UploadFileButton_clicked();

private:
    Ui::Adding *ui;
    MainMenu *m;
    Library *library;
    User *currentUser;
};

#endif // ADDING_H
