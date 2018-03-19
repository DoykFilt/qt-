#include "view_ajouterclient.h"
#include "ui_ajouterclient.h"
#include "QMessageBox"
#include "string"

AjouterClient::AjouterClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjouterClient)
{

    ui->setupUi(this);
    QSqlQuery * query=new QSqlQuery(DB_management::getInstance()->getDb());

     if (query->exec("SELECT Nom, Prenom FROM TRessource"))
     {
         while(query->next())
         {
             listRessources.append(query->value(0).toString()+" "+query->value(1).toString());

         }
     }
     ui->comboAffectation->addItems(listRessources);


    delete query;
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
    if(!ui->linePrenom->text().compare("") || !ui->lineNom->text().compare("")|| !ui->lineAdresse->text().compare("")||
            !ui->lineVille->text().compare("")|| ui->comboAffectation->size().isEmpty())
        QMessageBox::warning(this,"Erreur","Veuillez remplir tout les champs obligatoires !");
    else if(!controlerClient.testDate(ui->dateRDV->date()))
        QMessageBox::warning(this,"Erreur","Veuillez donner une date valide");
    else{
        if (controlerClient.ajouterClient(ui->linePrenom->text(), ui->lineNom->text(), ui->lineAdresse->text(),
                                      ui->lineVille->text(), ui->comboAffectation, ui->dateRDV->date(),
                                      ui->lineTelephone->text(), ui->spinCP->value(), ui->spinDuree->value(),
                                      ui->spinPriorite->value(), ui->textCommentaire->document()))
        {
            this->accept();
        }
        else
        {
             QMessageBox::warning(this,"Erreur","l'ajout n'a pas marché!");
        }


    }
}
