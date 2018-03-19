#ifndef LOGIN_H
#define LOGIN_H

#include "db_management.h"
#include <QDialog>
#include "view_mainwindow.h"
#include "string.h"
#include "controller_login.h"
using namespace std;

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();
private:

private slots:
    void on_annulerButton_clicked();

    void on_connecterButton_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
