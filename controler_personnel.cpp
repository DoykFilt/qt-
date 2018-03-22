#include "controler_personnel.h"
#include "model_personnelinfos.h"
#include "QDebug"
#include <QMessageBox>
#include <stdlib.h>

ControlerPersonnel::ControlerPersonnel()
{

}
bool ControlerPersonnel::testChamps(QString qnom, QString qprenom)
{
    if(qnom=="" || qprenom=="")
    {
        return false;
    }
    return true;
}

bool ControlerPersonnel::testMdp(QString Mdp)
{
    if(Mdp=="")
    {
        return false;
    }
    return true;
}
bool ControlerPersonnel::ajouterPersonnel(QString qnom, QString qprenom, int type, QString password){

     return pi.db_ajouter(qnom,qprenom,type,password);
}

void ControlerPersonnel::supprimerPersonnel(QString id){
    personnelInfos personnel;
    //On récupère l'identifiant à partir de la chaîne du type "id | nom"
    QStringList elems = id.split('|');
    personnel.setID(elems[0].toInt());=

    //On charge la ressource à partir de son id puis on le supprime
    personnel.db_charger();
    if(!personnel.db_supprimer())
        qDebug() << "Personnel non supprimé";
}

void ControlerPersonnel::modifierPersonnel(int ID, QString qnom, QString qprenom, QString type){
}
