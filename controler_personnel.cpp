#include "controler_personnel.h"
#include "model_personnelinfos.h"
#include "QDebug"


ControlerPersonnel::ControlerPersonnel()
{

}

void ControlerPersonnel::ajouterPersonnel(QString qnom, QString qprenom, QString type){
    std::string nom = computeString(qnom);
    std::string prenom = computeString(qprenom);
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
