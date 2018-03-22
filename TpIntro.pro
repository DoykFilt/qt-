#-------------------------------------------------
#
# Project created by QtCreator 2018-02-10T15:30:55
#
#-------------------------------------------------

QT       += core gui\
            sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TpIntro
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    view_apropos.cpp \
    view_ajouterclient.cpp \
    view_login.cpp \
    view_mainwindow.cpp \
    view_modifclient.cpp \
    controler_client.cpp \
    view_ajouterpersonnel.cpp \
    controler_personnel.cpp \
    view_modifpersonnel.cpp \
    view_affichagerechercheclient.cpp \
    model_personne.cpp \
    model_personnelinfos.cpp \
    model_clientinfos.cpp \
    controler_personne.cpp \
    db_init.cpp \
    model_rdv.cpp \
    model_type.cpp \
    model_compte.cpp \
    db_management.cpp \
    controller_login.cpp

HEADERS += \
    view_ajouterclient.h \
    view_apropos.h \
    view_login.h \
    view_mainwindow.h \
    view_modifclient.h \
    controler_client.h \
    view_ajouterpersonnel.h \
    controler_personnel.h \
    view_modifpersonnel.h \
    view_affichagerechercheclient.h \
    model_personne.h \
    model_personnelinfos.h \
    model_clientinfos.h \
    controler_personne.h \
    db_init.h \
    model_rdv.h \
    model_type.h \
    model_compte.h \
    db_management.h \
    controller_login.h

FORMS += \
        mainwindow.ui \
    login.ui \
    apropos.ui \
    modifclient.ui \
    ajouterclient.ui \
    ajouterpersonnel.ui \
    modifpersonnel.ui \
    affichagerechercheclient.ui

RESOURCES += \
    Ressources/ressources.qrc
