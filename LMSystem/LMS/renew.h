#ifndef RENEW_H
#define RENEW_H

#include <QWidget>

namespace Ui {
class Renew;
}

class Renew : public QWidget
{
    Q_OBJECT

public:
    explicit Renew(QWidget *parent = nullptr);
    ~Renew();

private:
    Ui::Renew *ui;
};

#endif // RENEW_H
