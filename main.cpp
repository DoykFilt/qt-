#include "view_login.h"
#include "view_mainwindow.h"
#include <QApplication>
#include "db_init.h"
#include "db_management.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login w1 ;
    MainWindow w2;
    DB_init::Creation_BD();
    DB_management * db = DB_management::getInstance();
    db->open();
    if(w1.exec()==QDialog::Accepted)
    {
        w2.show();
        return a.exec();
        db->close();
        DB_management::kill();
    }
    db->close();
    DB_management::kill();
    return 0;
}
