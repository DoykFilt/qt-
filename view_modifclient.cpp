#include "view_modifclient.h"
#include "ui_modifclient.h"
#include "controler_client.h"
#include "view_mainwindow.h"
#include "model_rdv.h"
#include "model_clientinfos.h"
#include "model_personnelinfos.h"
#include <QMessageBox>
#include <QDebug>

ModifClient::ModifClient(QWidget *parent, QString id) :
    QDialog(parent),
    ui(new Ui::ModifClient)

{
    ui->setupUi(this);
    qDebug() << id;
    IdClient=id;

    /*QSqlQuery * query=new QSqlQuery(DB_management::getInstance()->getDb());

    if (query->exec("SELECT Nom, Prenom, Id FROM 'TRessource'"
                         "WHERE Nom != 'Admin'"))
         {
             while(query->next())
             {
                 listRessources.append(query->value(0).toString()+" "+query->value(1).toString());
                 listId.append(query->value(2).toString());

             }

         }*/
    QVector<personnelInfos> personnels =  personnelInfos::db_getListPersonnel(true);
    for(QVector<personnelInfos>::iterator it = personnels.begin(); it != personnels.end(); it++)
    {
        listRessources.append(it->getNom() + " " + it->getPrenom());
        listId.append(QString::number(it->getID()));
    }

    ui->listWidgetAffectation->addItems(listRessources);
    ui->listWidgetAffectation->setSelectionMode(QAbstractItemView::MultiSelection);

/*
    if(query->exec("SELECT IdRessource FROM 'TRdv'"
                   "WHERE IdClient = "+IdClient))
    {
        while(query->next())
        {
            QString value=query->value(0).toString();
            ui->listWidgetAffectation->item(listId.indexOf(value))->setSelected(true);
        }
    }*/
    QVector<int> ids = ModelRdv::getListRessources(IdClient.toInt());
    for(QVector<int>::iterator it = ids.begin(); it != ids.end(); it++){
        QString value=QString::number(*it);
        ui->listWidgetAffectation->item(listId.indexOf(value))->setSelected(true);
    }


    /* if (query->exec("SELECT * FROM 'TClient' WHERE Id = "+IdClient))
     {
         while(query->next())
         {
             ui->lineNom->setText(query->value(1).toString());
             ui->linePrenom->setText(query->value(2).toString());
             ui->lineAdresse->setText(query->value(3).toString());
             ui->lineVille->setText(query->value(4).toString());
             ui->spinCP->setValue(query->value(5).toInt());
             ui->textCommentaire->setText(query->value(6).toString());
             ui->lineTelephone->setText(query->value(7).toString());
             ui->dateRDV->setDate(query->value(8).toDate());
             ui->spinDuree->setValue(query->value(9).toInt());
             ui->spinPriorite->setValue(query->value(10).toInt());
         }
     }*/
    ClientInfos client;
    client.setID(IdClient.toInt());
    client.chargerClient();
    ui->lineNom->setText(client.getNom());
    ui->linePrenom->setText(client.getPrenom());
    ui->lineAdresse->setText(client.getAdresse());
    ui->lineVille->setText(client.getVille());
    ui->spinCP->setValue(client.getCodePostal());
    ui->textCommentaire->setText("");
    ui->lineTelephone->setText(client.getTel());
    ui->dateRDV->setDate(client.getDateRdv());
    ui->spinDuree->setValue(client.getDureeRdv());
    ui->spinPriorite->setValue(client.getPriorite());
}

ModifClient::~ModifClient()
{
    delete ui;
}


void ModifClient::on_bouttonOK_clicked()
{
    //tests si les champs sont renseignés
    if(!ui->linePrenom->text().compare("") || !ui->lineNom->text().compare("")|| !ui->lineAdresse->text().compare("")||
            !ui->lineVille->text().compare("")|| ui->listWidgetAffectation->selectedItems().size()==0)
        QMessageBox::warning(this,"Erreur","Veuillez remplir tout les champs obligatoires !");
    else if(!controlerClient.testDate(ui->dateRDV->date()))
        QMessageBox::warning(this,"Erreur","Veuillez donner une date valide");
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
        controlerClient.modifierClient(IdClient,ui->linePrenom->text(), ui->lineNom->text(), ui->lineAdresse->text(),
                                      ui->lineVille->text(), listIdSelected, ui->dateRDV->date(),
                                      ui->lineTelephone->text(), ui->spinCP->value(), ui->spinDuree->value(),
                                      ui->spinPriorite->value(), ui->textCommentaire->document());
        this->accept();
    }
}

void ModifClient::on_bouttonAnnuler_clicked()
{
    this->close();
}
