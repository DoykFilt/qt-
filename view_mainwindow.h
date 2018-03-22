#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "view_ajouterclient.h"
#include "view_ajouterpersonnel.h"
#include "view_apropos.h"
#include <controler_client.h>
#include <controler_personnel.h>
#include <controller_login.h>
#include <db_management.h>
#include <QStatusBar>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    AjouterClient clientWindows;
    AjouterPersonnel personnelWindows;
    aPropos apropos;


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionclient_triggered();
    void on_actionQuitter_triggered();
    void on_actionPersonnel_triggered();
    void on_actionA_propos_triggered();
    void on_BouttonRechercherClient_clicked();
    void on_buttonSupprimerClient_clicked();
    void on_buttonSupprimerPersonnel_clicked();
    void on_buttonModifierClient_clicked();
    void on_buttonModifierPersonnel_clicked();

private:
    Ui::MainWindow *ui;
    QSqlTableModel * modelClient=NULL;
    QSqlTableModel * modelRecherche=NULL;
    QSqlTableModel * modelRessource=NULL;
    ControlerClient cClient;
    ControlerPersonnel cPersonnel;
    void createTableView();
    void createTreeView();

public :
    QString getId();				

};

#endif // MAINWINDOW_H
