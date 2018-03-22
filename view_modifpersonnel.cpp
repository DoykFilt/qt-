#include "view_modifpersonnel.h"
#include "ui_modifpersonnel.h"
#include "view_login.h"
#include <QMessageBox>
#include "model_personnelinfos.h"
#include "model_type.h"

ModifPersonnel::ModifPersonnel(QWidget *parent, QString text) :
    QDialog(parent), ui(new Ui::ModifPersonnel)
{
    ui->setupUi(this);

    personnelInfos ressource;

    QStringList elems = text.split('|');
    QString ID = elems[0];
    ressource.setID(ID.toInt());
    ressource.db_charger();

    ui->lineNom->setText(ressource.getNom());
    ui->linePrenom->setText(ressource.getPrenom());

    //On rempli la combobox des différents types et on sélectionne le précédent type de la ressource
    std::vector<Type> types = Type::getListType();
    Type type = Type::getTypeOf(ID.toInt());
    int index = 0;
    for(std::vector<Type>::iterator it = types.begin(); it != types.end(); it++)
    {
        ui->comboBoxType->addItem(it->getLabel());
        if(it->getId() == type.getId())
            ui->comboBoxType->setCurrentIndex(index);
        index++;
    }

    if(ui->comboBoxType->currentText()=="Informaticien")
    {
        ui->linePassword->setEnabled(true);
    }
    else
    {
        ui->linePassword->setEnabled(false);
    }
}

ModifPersonnel::~ModifPersonnel()
{
    delete ui;
}

void ModifPersonnel::on_buttonAnnuler_clicked()
{
    this->close();
}

void ModifPersonnel::on_buttonOK_clicked()
{
    //tests si les champs sont renseignés
    if(!ui->lineNom->text().compare("") || !ui->linePrenom->text().compare("") || ui->comboBoxType->currentIndex() == -1)
        QMessageBox::warning(this,"Erreur","Veuillez remplir tout les champs !");
    else if(ui->linePassword->isEnabled())
        {
            if(!(controlerPersonnel.testMdp(ui->linePassword->text())))
            {
                QMessageBox::warning(this,"Erreur","Veuillez remplir le champs mot de passe");
            }
        }
        if(controlerPersonnel.modifierPersonnel(0, ui->lineNom->text(), ui->linePrenom->text(), ui->comboBoxType->currentIndex(), ui->linePassword->text()))
        {
            this->accept();
        }
        else
        {
            QMessageBox::warning(this,"Erreur","La modification du personnel a échouée !");
        }
}

void ModifPersonnel::on_comboBoxType_currentIndexChanged(const QString &arg1)
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
