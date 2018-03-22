#include "db_management.h"
#include <QTextStream>
using namespace std;

DB_management * DB_management::instance = NULL;

QSqlDatabase DB_management::getDb() const
{
    return db;
}

void DB_management::setDb(const QSqlDatabase &value)
{
    db = value;
}

DB_management::DB_management()
{
    this->open();
}

DB_management * DB_management::getInstance(){
    if(instance == NULL)
        instance = new DB_management();
    return instance;
}

void DB_management::kill(){
    if(instance != NULL){
        delete instance;
        instance = NULL;
    }
}

bool DB_management::open(){
    bool b_test;
    db = QSqlDatabase::addDatabase("QSQLITE");

    if(db.isValid())
    {
        db.setHostName("localhost");
        db.setUserName("root");
        db.setPassword("password");
        db.setDatabaseName("base_tmp.sqli");
        db.open();
        return true;
    }
    else
        return false;
}


void DB_management::close(){
    db.close();
}

QSqlError DB_management::lastError(){
    return db.lastError();
}
