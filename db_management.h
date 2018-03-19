#ifndef DB_MANAGEMENT_H
#define DB_MANAGEMENT_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QString>
#include<QSqlQuery>
#include <QSqlTableModel>

class DB_management
{
private :
    QSqlDatabase db;
    static DB_management * instance;
    QSqlTableModel model;
    DB_management();

public:
    static DB_management * getInstance();
    static void kill();
    bool open();
    void close();
    QSqlError lastError();

    QSqlDatabase getDb() const;
    void setDb(const QSqlDatabase &value);
};

#endif // DB_MANAGEMENT_H
