#include "model_rdv.h"

int ModelRdv::getID() const
{
    return ID;
}

void ModelRdv::setID(int value)
{
    ID = value;
}

int ModelRdv::getIDClient() const
{
    return IDClient;
}

void ModelRdv::setIDClient(int value)
{
    IDClient = value;
}

int ModelRdv::getIDRessource() const
{
    return IDRessource;
}

void ModelRdv::setIDRessource(int value)
{
    IDRessource = value;
}

ModelRdv::ModelRdv()
{
    ID=-1;
    IDClient=-1;
    IDRessource=-1;
}

ModelRdv::ModelRdv(int ID1, int IDClient1, int IDRessource1)
{
    ID=ID1;
    IDClient=IDClient1;
    IDRessource=IDRessource1;
}


QVector<int> ModelRdv::getListRessources(int idClient){
    QSqlQuery * query=new QSqlQuery(DB_management::getInstance()->getDb());
    if(query->exec("SELECT IdRessource FROM 'TRdv' WHERE IdClient = " + idClient))
    {
        while(query->next())
        {
            QString value=query->value(0).toString();
            ui->listWidgetAffectation->item(listId.indexOf(value))->setSelected(true);
        }
    }
}
