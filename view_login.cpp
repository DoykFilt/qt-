#include "view_login.h"
#include "view_mainwindow.h"
#include "ui_Login.h"
#include <QMessageBox>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->linePassword->setEchoMode(QLineEdit::Password);
    setWindowTitle("Se connecter");
}

Login::~Login()
{
    delete ui;
}


void Login::on_annulerButton_clicked()
{
    this->close();
}


void Login::on_connecterButton_clicked()
{
    ControllerLogin c;
    if(c.isLoginCorrect(ui->lineLogin->text(),ui->linePassword->text()))
    {
       accept();
    }
    else
    {
        QMessageBox::warning(this,"Erreur","Login ou mot de passe incorrect !");
        ui->linePassword->clear();
    }


}

