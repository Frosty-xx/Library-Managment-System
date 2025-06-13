#ifndef FORM_H
#define FORM_H
#include "Library.h"
#include <QCloseEvent>
#include <QWidget>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT
protected:

public:
    explicit Form(Library* l,QWidget *parent = nullptr);

    ~Form();

private:
    Library* library;
private slots:
    void on_CreateButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::Form *ui;
    void inputcheck();
};

#endif // FORM_H
