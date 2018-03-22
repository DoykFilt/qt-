#include "view_ajouterclient.h"
#include "ui_ajouterclient.h"
#include "model_personnelinfos.h"
#include <QVector>
#include "QMessageBox"
#include "string"
#include <QDebug>

AjouterClient::AjouterClient(QWidget *parent) :
    QDialog(parent), ui(new Ui::AjouterClient)
{
    ui->setupUi(this);

    QVector<personnelInfos> personnels =  personnelInfos::db_getListPersonnel(true);
    for(QVector<personnelInfos>::iterator it = personnels.begin(); it != personnels.end(); it++)
    {
        listRessources.append(it->getNom() + " " + it->getPrenom());
        listId.append(QString::number(it->getID()));
    }
/*
    QSqlQuery * query=new QSqlQuery(DB_management::getInstance()->getDb());
    if (query->exec("SELECT Nom, Prenom, Id FROM 'TRessource' WHERE Nom != 'Admin'"))
    {
        while(query->next())
        {
            listRessources.append(query->value(0).toString()+" "+query->value(1).toString());
            listId.append(query->value(2).toString());
        }
    }
    delete query;*/
    ui->listWidgetAffectation->addItems(listRessources);
    ui->listWidgetAffectation->setSelectionMode(QAbstractItemView::MultiSelection);
}

AjouterClient::~AjouterClient()
{
    delete ui;

}

void AjouterClient::on_buttonAnnuler_clicked()
{
    this->close();
}

void AjouterClient::on_buttonOK_clicked()
{
    //tests si les champs sont renseignés
    if(!ui->linePrenom->text().compare("") || !ui->lineNom->text().compare("") || !ui->lineAdresse->text().compare("") ||
            !ui->lineVille->text().compare("") || ui->listWidgetAffectation->selectedItems().isEmpty())
        QMessageBox::warning(this,"Erreur","Veuillez remplir tout les champs obligatoires !");
    else if(!controlerClient.testDate(ui->dateRDV->date()))
        QMessageBox::warning(this,"Erreur","Veuillez donner une date valide !");
    else{
        QStringList listIdSelected;
        for(int i=0;i<listId.size();i++)
        {
           if((ui->listWidgetAffectation->item(i)->isSelected()))
           {
              listIdSelected.append(listId.value(i));
              qDebug() << listIdSelected;
           }

        }

        if (controlerClient.ajouterClient(ui->linePrenom->text(), ui->lineNom->text(), ui->lineAdresse->text(),
                                          ui->lineVille->text(),listIdSelected, ui->dateRDV->date(),
                                          ui->lineTelephone->text(), ui->spinCP->value(), ui->spinDuree->value(),
                                        ui->spinPriorite->value(), ui->textCommentaire->document()))
            this->accept();
        else
             QMessageBox::warning(this,"Erreur","L'ajout du client a échoué !");


    }
}
