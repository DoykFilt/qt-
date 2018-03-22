#ifndef CONTROLER_PERSONNEL_H
#define CONTROLER_PERSONNEL_H
#include "controler_personne.h"
#include "model_personnelinfos.h"

#include <QString>

class ControlerPersonnel : public controller_personne
{
private :
    personnelInfos pi;

public:
    ControlerPersonnel();
    bool ajouterPersonnel(QString qnom, QString qprenom, int type, QString password);
    bool modifierPersonnel(int ID, QString qnom, QString qprenom, int type, QString password);
    void supprimerPersonnel(QString ID);

    bool testChamps(QString qnom, QString qprenom);
    bool testMdp(QString Mdp);
};

#endif // CONTROLER_PERSONNEL_H
