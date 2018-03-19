#include "view_modifclient.h"
#include "ui_modifclient.h"
#include <QMessageBox>

ModifClient::ModifClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifClient)
{
    ui->setupUi(this);
}

ModifClient::~ModifClient()
{
    delete ui;
}

void ModifClient::on_bouttonAppliquer_clicked()
{
    //tests si les champs sont renseignés
    if(!ui->linePrenom->text().compare("") || !ui->lineNom->text().compare("")|| !ui->lineAdresse->text().compare("")||
            !ui->lineVille->text().compare("")|| ui->comboAffectation->size().isEmpty())
        QMessageBox::warning(this,"Erreur","Veuillez remplir tout les champs obligatoires !");
    else if(!controlerClient.testDate(ui->dateRDV->date()))
        QMessageBox::warning(this,"Erreur","Veuillez donner une date valide");
    else{
        /*controlerClient.ajouterClient(ui->linePrenom->text(), ui->lineNom->text(), ui->lineAdresse->text(),
                                      ui->lineVille->text(), ui->comboAffectation, ui->dateRDV->date(),
                                      ui->lineTelephone->text(), ui->spinCP->value(), ui->spinDuree->value(),
                                      ui->spinPriorite->value(), ui->textCommentaire->document());*/
    }
}

void ModifClient::on_bouttonOK_clicked()
{
    //tests si les champs sont renseignés
    if(!ui->linePrenom->text().compare("") || !ui->lineNom->text().compare("")|| !ui->lineAdresse->text().compare("")||
            !ui->lineVille->text().compare("")|| ui->comboAffectation->size().isEmpty())
        QMessageBox::warning(this,"Erreur","Veuillez remplir tout les champs obligatoires !");
    else if(!controlerClient.testDate(ui->dateRDV->date()))
        QMessageBox::warning(this,"Erreur","Veuillez donner une date valide");
    else{
        /*controlerClient.ajouterClient(ui->linePrenom->text(), ui->lineNom->text(), ui->lineAdresse->text(),
                                      ui->lineVille->text(), ui->comboAffectation, ui->dateRDV->date(),
                                      ui->lineTelephone->text(), ui->spinCP->value(), ui->spinDuree->value(),
                                      ui->spinPriorite->value(), ui->textCommentaire->document());

        this->accept();*/
    }
}

void ModifClient::on_bouttonAnnuler_clicked()
{
    this->close();
}
