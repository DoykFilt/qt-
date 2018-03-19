#include "view_modifpersonnel.h"
#include "ui_modifpersonnel.h"
#include "view_login.h"
#include <QMessageBox>

ModifPersonnel::ModifPersonnel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifPersonnel)
{
    ui->setupUi(this);
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
    Login login;
    //tests si les champs sont renseignés
    if(!ui->lineNom->text().compare("") || !ui->linePrenom->text().compare("") || ui->comboBoxType->currentIndex() == -1)
        QMessageBox::warning(this,"Erreur","Veuillez remplir tout les champs !");
    else if((!ui->comboBoxType->currentText().compare("Informaticien") && login.exec() == QDialog::Accepted)
            || ui->comboBoxType->currentText().compare("Informaticien")){
        controlerPersonnel.modifierPersonnel(0, ui->lineNom->text(), ui->linePrenom->text(), ui->comboBoxType->currentText());
        this->accept();
    }
}
