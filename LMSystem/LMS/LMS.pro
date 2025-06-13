QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Admin.cpp \
    Article.cpp \
    Book.cpp \
    Date.cpp \
    Library.cpp \
    LibraryDataManager.cpp \
    Loan.cpp \
    Resources.cpp \
    User.cpp \
    adding.cpp \
    changepassword.cpp \
    changeusername.cpp \
    form.cpp \
    main.cpp \
    mainmenu.cpp \
    mainwindow.cpp \
    notification.cpp \
    reserve.cpp

HEADERS += \
    Admin.h \
    Article.h \
    Book.h \
    Date.h \
    Library.h \
    LibraryDataManager.h \
    Loan.h \
    Resources.h \
    User.h \
    addBook.h \
    adding.h \
    changepassword.h \
    changeusername.h \
    form.h \
    mainmenu.h \
    mainwindow.h \
    notification.h \
    reserve.h

FORMS += \
    adding.ui \
    changepassword.ui \
    changeusername.ui \
    form.ui \
    mainmenu.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resc.qrc

DISTFILES += \

RC_FILE = Icons/LibraryIcon.rc
