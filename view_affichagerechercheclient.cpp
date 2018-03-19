#include "view_affichagerechercheclient.h"
#include "ui_affichagerechercheclient.h"

affichageRechercheClient::affichageRechercheClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::affichageRechercheClient)
{
    //ui->tableView->setmodel()
    
    ui->setupUi(this);
}

affichageRechercheClient::~affichageRechercheClient()
{
    delete ui;
}

void affichageRechercheClient::on_buttonOK_clicked()
{
    this->accept();
}


