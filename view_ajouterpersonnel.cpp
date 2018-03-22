#include "view_ajouterpersonnel.h"
#include "ui_ajouterpersonnel.h"
#include "view_login.h"
#include <QMessageBox>

AjouterPersonnel::AjouterPersonnel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjouterPersonnel)
{
    ui->setupUi(this);
    QSqlQuery * query=new QSqlQuery(DB_management::getInstance()->getDb());
    if (query->exec("SELECT Label FROM 'TType'"))
         {
             while(query->next())
             {

                ListType.append(query->value(0).toString());
             }

         }
    ui->comboBoxType->addItems(ListType);



    delete query;
}

AjouterPersonnel::~AjouterPersonnel()
{
    delete ui;
}

void AjouterPersonnel::on_buttonAnnuler_clicked()
{
    this->close();
}

void AjouterPersonnel::on_buttonOK_clicked()
{
    if(!(controlerPersonnel.testChamps(ui->lineNom->text(), ui->linePrenom->text())))
    {
        QMessageBox::warning(this,"Erreur","Veuillez remplir tout les champs obligatoires !");
    }

    if(ui->linePassword->isEnabled())
    {
        if(!(controlerPersonnel.testMdp(ui->linePassword->text())))
        {
            QMessageBox::warning(this,"Erreur","Veuillez remplir le champs mot de passe");
        }
    }

       if(controlerPersonnel.ajouterPersonnel(ui->lineNom->text(), ui->linePrenom->text(), ui->comboBoxType->currentIndex(),ui->linePassword->text()))
       {
           this->accept();
       }
       else
       {
           QMessageBox::warning(this,"Erreur","L'ajout du personnel n'a pas marché !");
       }

}

void AjouterPersonnel::on_comboBoxType_currentIndexChanged(const QString &arg1)
{
    if(arg1=="Informaticien")
    {
        ui->linePassword->setEnabled(true);
    }
    else
    {
        ui->linePassword->setEnabled(false);
    }
}
