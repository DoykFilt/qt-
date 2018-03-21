#include "model_clientinfos.h"
#include "QString"
#include "string"
#include "QSqlQuery"
#include <QDebug>



QString ClientInfos::getAdresse() const
{
    return adresse;
}

void ClientInfos::setAdresse(const QString &value)
{
    adresse = value;
}

QString ClientInfos::getVille() const
{
    return ville;
}

void ClientInfos::setVille(const QString &value)
{
    ville = value;
}

int ClientInfos::getCodePostal() const
{
    return codePostal;
}

void ClientInfos::setCodePostal(int value)
{
    codePostal = value;
}

QDate ClientInfos::getDateRdv() const
{
    return dateRdv;
}

void ClientInfos::setDateRdv(const QDate &value)
{
    dateRdv = value;
}

int ClientInfos::getDureeRdv() const
{
    return dureeRdv;
}

void ClientInfos::setDureeRdv(int value)
{
    dureeRdv = value;
}

int ClientInfos::getPriorite() const
{
    return priorite;
}

void ClientInfos::setPriorite(int value)
{
    priorite = value;
}

QString ClientInfos::getTel() const
{
    return tel;
}

void ClientInfos::setTel(const QString &value)
{
    tel = value;
}

QVector<int>* ClientInfos::getId_ressources()
{
    return &id_ressources;
}

void ClientInfos::setId_ressources(QVector<int> *value1)
{
    id_ressources.clear();
    for(int i=0;i<value1->size();i++)
    {
        id_ressources.append(value1->value(i));
    }
}

ClientInfos::ClientInfos(){
    ModelPersonne();
    adresse  = "";
    ville = "";
    codePostal = 0;
    dureeRdv = 60;
    priorite = 1;
    tel = "";
    dateRdv.setDate(0, 0, 0);
}

ClientInfos::ClientInfos(int ID, QString n, QString p, QString a, QString v,int CP,QDate drdv, int dureeConsultation, int prio,QString t, QVector<int> * ids):
ModelPersonne(n,p, ID), adresse(a), ville(v), codePostal(CP), dateRdv(drdv), dureeRdv(dureeConsultation), priorite(prio), tel(t){
    for(int compteur = 0; compteur < ids->size(); compteur++)
        id_ressources.append(ids->value(compteur));
}

ClientInfos::ClientInfos(int ID, int dureeConsultation, int prio):
ModelPersonne("", "", ID), dureeRdv(dureeConsultation), priorite(prio)
{}
bool ClientInfos::ajouterClient(QString qprenom, QString qnom, QString qadresse,
                                QString qville, QStringList affectations, QDate date,
                                QString qtelephone, int CP, double duree,
                                int priorite, QString commentaire){
    QSqlQuery query(DB_management::getInstance()->getDb());


    if (query.exec("INSERT INTO TClient(Nom,Prenom,Adresse,Ville,CP,Commentaire,Tel,DateRdv,DureeRdv,Priorite) "
                   "VALUES ('"+qnom+"', '"+qprenom+"', '"+qadresse+"', '"+qville+"', "+QString::number(CP)+", '"+commentaire+"', '"+qtelephone+"', '"+date.toString(QString("yyyy-MM-dd"))+"', "+QString::number(duree)+", "+QString::number(priorite)+")"))
    {
        QSqlQuery query2(DB_management::getInstance()->getDb());

    if(query.exec("SELECT Id FROM TClient "
                   "WHERE Nom = '"+qnom+"' AND Prenom = '"+qprenom+"'"))
    {
        while(query.next())
        {
            QString ID=query.value(0).toString();
            for(int i=0;i<affectations.size();i++)
            {
                if(query.exec("INSERT INTO TRdv(IdClient,IdRessource)"
                              "VALUES ('"+ID+"','"+affectations.value(i)+"')"))
                {
                    qInfo() << "yes";
                }
            }
            return true;

        }
     }


    }
      return false;

}

bool ClientInfos::modifierClient(QString Id, QString qprenom, QString qnom, QString qadresse,
                                QString qville, QStringList affectations, QDate date,
                                QString qtelephone, int CP, double duree,
                                int priorite, QString commentaire)
{
    QSqlQuery query(DB_management::getInstance()->getDb());

    if(query.exec("UPDATE TClient "
                  "SET Nom = '"+qnom+"', Prenom = '"+qprenom+"', Adresse = '"+qadresse+"', Ville = '"+qville+"', CP = "+QString::number(CP)+", Commentaire = '"+commentaire+"', Tel = '"+qtelephone+"', DateRdv = '"+date.toString(QString("yyyy-MM-dd"))+"', DureeRdv = "+QString::number(duree)+", Priorite = "+QString::number(priorite)+" "
                  "WHERE Id = "+Id))
    {
        if(query.exec("DELETE FROM 'TRdv' "
                      "WHERE IdClient = "+Id))
        {
            for(int i=0;i<affectations.size();i++)
            {
                if(query.exec("INSERT INTO TRdv(IdClient,IdRessource)"
                              "VALUES ('"+Id+"','"+affectations.value(i)+"')"))
                {
                    qInfo() << "yes";
                }
            }
            return true;
        }
        return true;
    }
    return false;

}

bool ClientInfos::supprimerClient(QString id)
{


     QSqlQuery query(DB_management::getInstance()->getDb());
     if(query.exec("DELETE FROM 'TClient'"
                   "WHERE Id = "+id))
     {
         if(query.exec("DELETE FROM 'TRdv' "
                       "WHERE IdClient = "+id))

         return true;
     }
     return false;
}

