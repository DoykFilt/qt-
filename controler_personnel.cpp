#include "controler_personnel.h"
#include "model_personnelinfos.h"
#include "QDebug"
#include <QMessageBox>


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

void ControlerPersonnel::supprimerPersonnel(int id){
    personnelInfos personnel;
    personnel.setID(id);
    personnel.db_charger();
    if(!personnel.db_supprimer())
        qDebug() << "Personnel non supprimé";
}

void ControlerPersonnel::modifierPersonnel(int ID, QString qnom, QString qprenom, QString type){
    //std::string nom = computeString(qnom);
    //std::string prenom = computeString(qprenom);
}

/*QSqlTableModel ControlerPersonnel::recupererPersonnel()
{
    return DB_management::getInstance()->recuperationPersonnel();
}*/
