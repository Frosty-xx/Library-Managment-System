#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Library.h"
#include"form.h"

#include <QMainWindow>
#include <QStandardItemModel>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Library* lr,QWidget *parent = nullptr);
    ~MainWindow();
private:
    Library* library;


private slots:

    void on_CreateAccountButton_clicked();

    void on_SignInButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
