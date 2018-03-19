#include "model_personnelinfos.h"
#include "db_management.h"
#include <QDebug>

int personnelInfos::getType() const
{
    return type;
}

void personnelInfos::setType(const int &value)
{
    type = value;
}

personnelInfos::personnelInfos()
{
    ModelPersonne();
}
personnelInfos::personnelInfos(int ID, QString n, QString p, int type1)
{
    ModelPersonne(n,p, ID);
    type=type1;

}

bool personnelInfos::db_supprimer(){

    DB_management * db = DB_management::getInstance();

    QSqlQuery query(db->getDb());
    query.prepare("Delete From 'TRessource' Where 'Id' = ?");
    query.addBindValue(getID());

    bool result = query.exec();
    if(!result)
    {
        qDebug() << query.lastError().text();
        qDebug() << "Ressource non supprimée !\n";
        return false;
    }
    return true;
}

void personnelInfos::db_charger(){

    DB_management * db = DB_management::getInstance();
    std::vector<personnelInfos> list;

    QSqlQuery query(db->getDb());
    query.prepare("SELECT * FROM TRessource WHERE Id = ?");
    query.addBindValue(getID());

    bool result = query.exec();
    if(!result)
    {
        qDebug() << query.lastError().text();
        qDebug() << "La requête db_charger a échouée !\n";
    }
    while(query.next()){

        QString nom = query.value(1).toString();
        QString prenom = query.value(2).toString();
        int ressource = query.value(3).toInt();
        setNom(nom);
        setPrenom(prenom);
        setType(ressource);
        qDebug() << "RessourceChargée";
    }
}

bool personnelInfos::db_ajouterOUmodifier(){
    DB_management * db = DB_management::getInstance();
    std::vector<personnelInfos> list;

    QSqlQuery query(db->getDb());
    query.prepare("SELECT * FROM TRessource WHERE Id = ?");
    query.addBindValue(getID());

    bool result = query.exec();
    if(!result || query.size() == -1)
    {
        qDebug() << query.lastError().text();
        qDebug() << "La requête db_ajouterOUmodifier a échouée !\n";
    }
    if(query.size() < 1)
        db_ajouter();
    else
        db_modifier();
}

bool personnelInfos::db_modifier(){

    DB_management * db = DB_management::getInstance();

    QSqlQuery query(db->getDb());
    query.prepare("UPDATE TRessources Nom = ?, Prenom = ?, IdType = ? WHERE Id = ?");
    /*query.addBindValue(0, getNom());
    query.addBindValue(1, getPrenom());
    query.addBindValue(2, getType());
    query.addBindValue(3, getID());*/

    bool result = query.exec();
    if(!result)
    {
        qDebug() << query.lastError().text();
        qDebug() << "La requête db_modifier a échouée !\n";
    }
}

bool personnelInfos::db_ajouter(){
    DB_management * db = DB_management::getInstance();

    QSqlQuery query(db->getDb());
    query.prepare("INSERT INTO TRessources (Nom, Prenom, IdType) VALUES (?, ?, ?");
    /*query.addBindValue(0, getNom());
    query.addBindValue(1, getPrenom());
    query.addBindValue(2, getType());*/

    bool result = query.exec();
    if(!result)
    {
        qDebug() << query.lastError().text();
        qDebug() << "La requête db_ajouter a échouée !\n";
    }
}
