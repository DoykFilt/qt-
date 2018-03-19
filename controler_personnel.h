#ifndef CONTROLER_PERSONNEL_H
#define CONTROLER_PERSONNEL_H
#include "controler_personne.h"



#include <QString>

class ControlerPersonnel : public controller_personne
{
public:
    ControlerPersonnel();
    void ajouterPersonnel(QString qnom, QString qprenom, QString type);
    void modifierPersonnel(int ID, QString qnom, QString qprenom, QString type);
    void supprimerPersonnel(int ID);
    //QSqlTableModel recupererPersonnel();
};

#endif // CONTROLER_PERSONNEL_H
