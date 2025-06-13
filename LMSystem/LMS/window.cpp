#include "window.h"
#include <QPushButton>
Window::Window(QWidget *parent)
    : QWidget{parent}

{
    //Set fixed size
    setFixedSize(1920,1080);

    m_button = new QPushButton("Hello Wordl",this);
    m_button->setGeometry(800,800,80,30);

}
