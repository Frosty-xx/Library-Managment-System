#include "renew.h"
#include "ui_renew.h"

Renew::Renew(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Renew)
{
    ui->setupUi(this);
}

Renew::~Renew()
{
    delete ui;
}
