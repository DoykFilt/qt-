#include "model_type.h"
#include "db_management.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>


QString Type::getLabel() const
{
    return label;
}

void Type::setLabel(const QString &value)
{
    label = value;
}

int Type::getId() const
{
    return id;
}

void Type::setId(int value)
{
    id = value;
}

Type::Type(int ID, QString LABEL)
{
    id = ID;
    label = LABEL;
}

//Renvoit la liste de tout les types existants dans la BDD
std::vector<Type> Type::getListType(){
    DB_management * db = DB_management::getInstance();
    std::vector<Type> list;

    QSqlQuery query(db->getDb());
    QString q = "SELECT * FROM TType";

    bool result = query.exec(q);
    if(!result)
    {
        qDebug() << query.lastError().text();
        qDebug() << "Ressource non supprimée !\n";
        return list;
    }

    while(query.next()){
        int ID = query.value(query.record().indexOf("Id")).toInt();
        QString LABEL = query.value(query.record().indexOf("Label")).toString();
        Type type(ID, LABEL);
        list.push_back(type);
    }

    return list;
}

//Renvoit la liste des Ressources appartenant au type de l'objet Type
std::vector<personnelInfos> Type::getRessourcesRelatifs(){
    DB_management * db = DB_management::getInstance();
    std::vector<personnelInfos> list;

    QSqlQuery query(db->getDb());
    query.prepare("SELECT * FROM TRessource WHERE IdType = ?");
    query.addBindValue(id);

    bool result = query.exec();
    if(!result)
    {
        qDebug() << query.lastError().text();
        qDebug() << "La requête getRessourcesRelatifs a échouée !\n";
        return list;
    }

    while(query.next()){

        int ID = query.record().value(0).toInt();
        QString nom = query.record().value(1).toString();
        QString prenom = query.record().value(2).toString();
        int ressource = query.record().value(3).toInt();
        personnelInfos personnel;
        personnel.setID(ID);
        personnel.setNom(nom);
        personnel.setPrenom(prenom);
        personnel.setType(ressource);
        list.push_back(personnel);
    }

    return list;
}
