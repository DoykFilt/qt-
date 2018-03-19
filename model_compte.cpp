#include "model_compte.h"
#include <QSqlQuery>
#include <QVariant>

int ModelCompte::getId() const
{
    return Id;
}

void ModelCompte::setId(int value)
{
    Id = value;
}

int ModelCompte::getIdRessource() const
{
    return IdRessource;
}

void ModelCompte::setIdRessource(int value)
{
    IdRessource = value;
}

QString ModelCompte::getLogin() const
{
    return Login;
}

void ModelCompte::setLogin(const QString &value)
{
    Login = value;
}

QString ModelCompte::getMdp() const
{
    return Mdp;
}

void ModelCompte::setMdp(const QString &value)
{
    Mdp = value;
}

ModelCompte::ModelCompte()
{
    Id=-1;
    IdRessource=-1;
    Login="";
    Mdp="";

}
ModelCompte::ModelCompte(int Id1, int IdRessource1, QString Login1, QString Mdp1)
{
    Id=Id1;
    IdRessource=IdRessource1;
    Login=Login1;
    Mdp=Mdp1;
}

bool ModelCompte::isLoginCorrect(QString login,QString password)
{
    QSqlQuery * query=new QSqlQuery(DB_management::getInstance()->getDb());

    if (query->exec("SELECT Id FROM TCompte WHERE Login = '"+login+"' and Mdp = '"+password+"'"))
        {
         while (query->next())
         {
             if(query->value(0).toString().compare(login) && query->value(1).toString().compare(password))
             {
                 delete query;
                 return true;
             }
         }

        }
    delete query;
    return false;
}
