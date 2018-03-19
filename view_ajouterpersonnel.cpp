#include "view_ajouterpersonnel.h"
#include "ui_ajouterpersonnel.h"
#include "view_login.h"
#include <QMessageBox>

AjouterPersonnel::AjouterPersonnel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjouterPersonnel)
{
    ui->setupUi(this);
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
    Login login;
    //tests si les champs sont renseignés
    if(!ui->lineNom->text().compare("") || !ui->linePrenom->text().compare("") || ui->comboBoxType->currentIndex() == -1)
        QMessageBox::warning(this,"Erreur","Veuillez remplir tout les champs !");
    else if((!ui->comboBoxType->currentText().compare("Informaticien") && login.exec() == QDialog::Accepted)
            || ui->comboBoxType->currentText().compare("Informaticien")){
        controlerPersonnel.ajouterPersonnel(ui->lineNom->text(), ui->linePrenom->text(), ui->comboBoxType->currentText());
        this->accept();
    }
}
