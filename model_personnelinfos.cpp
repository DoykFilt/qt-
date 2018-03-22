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
    query.prepare("Delete From TRessource Where Id = ?");
    query.addBindValue(getID());

    bool result = query.exec();
    qDebug() << result;
    if(!result)
    {
        qDebug() << query.lastError().text();
        qDebug() << "Ressource non supprimée !\n";
        return false;
    }
    qDebug() << "Ressource supprimée !\n";
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

bool personnelInfos::db_modifier(int ID, QString nom, QString prenom,int type, QString password){

    DB_management * db = DB_management::getInstance();

    QSqlQuery query(db->getDb());
    query.prepare("UPDATE TRessources Nom = :nom, Prenom = :prenom, IdType = :type WHERE Id = :id");
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":type", type);
    query.bindValue(":id", ID);

    bool result = query.exec();
    if(!result)
    {
        qDebug() << query.lastError().text();
        qDebug() << "La requête db_modifier a échouée !\n";
    }

    if(!password.isEmpty())
    {
        query.prepare("DELETE TCompte WHERE IdRessource = :id");
        query.bindValue(":id", ID);
        query.exec();

        if(query.exec("SELECT Id FROM TRessource "
                       "WHERE Nom = '"+nom+"' AND Prenom = '"+prenom+"'"))
        {
            while (query.next())
            {
                QString ID=query.value(0).toString();
                if(query.exec("INSERT INTO TCompte(IdRessource,Login,MdP) "
                              "VALUES ('"+ID+"','"+ID+"' , '"+password+"')"))
                {
                    qDebug() << "Valeur insérée";
                }
            }
        }
    }
}

bool personnelInfos::db_ajouter(QString nom, QString prenom, int type, QString password){
    QSqlQuery query(DB_management::getInstance()->getDb());
    QSqlQuery query2(DB_management::getInstance()->getDb());
    bool result=(query.exec("INSERT INTO TRessource(Nom, Prenom, IdType) "
                  "VALUES ('"+nom+"', '"+prenom+"', "+QString::number(type)+")"));

    if(!result)
    {
        return false;
    }
    if(!password.isEmpty())
    {
        if(query2.exec("SELECT Id FROM TRessource "
                       "WHERE Nom = '"+nom+"' AND Prenom = '"+prenom+"'"))
        {
            while (query2.next())
            {
                QString ID=query.value(0).toString();
                if(query.exec("INSERT INTO TCompte(IdRessource,Login,MdP) "
                              "VALUES ('"+ID+"','"+ID+"' , '"+password+"')"))
                {
                    qDebug() << "Valeur insérée";
                }
            }
        }



    }
    return true;
}

//Permet de récupérer la liste des ressources
QVector<personnelInfos> personnelInfos::db_getListPersonnel(bool withoutAdmin){

    QString s;
    if(withoutAdmin)
        s = "SELECT Nom, Prenom, Id FROM 'TRessource' WHERE Nom != 'Admin'";
    else
        s = "SELECT Nom, Prenom, Id FROM 'TRessource'";

    QSqlQuery * query = new QSqlQuery(DB_management::getInstance()->getDb());
    QVector<personnelInfos> personnels;
    if (query->exec(s))
    {
        while(query->next())
        {
            personnelInfos personnel;
            personnel.setNom(query->value(0).toString());
            personnel.setPrenom(query->value(1).toString());
            personnel.setID(query->value(2).toInt());
            personnels.append(personnel);
        }
    }
    delete query;
    return personnels;
}
