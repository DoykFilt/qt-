#include "view_apropos.h"
#include "ui_apropos.h"

aPropos::aPropos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aPropos)
{
    ui->setupUi(this);
    setWindowTitle("A propos");
}

aPropos::~aPropos()
{
    delete ui;
}
