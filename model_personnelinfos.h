#ifndef PERSONNELINFOS_H
#define PERSONNELINFOS_H
#include "model_personne.h"


class personnelInfos : public ModelPersonne
{
private :
    int type;
    bool db_modifier();
    bool db_ajouter();

public:
    personnelInfos();
    personnelInfos(int ID, QString n,QString p, int type1);
    int getType() const;
    void setType(const int &value);

    void db_charger();
    bool db_supprimer();
    bool db_ajouterOUmodifier();
};

#endif // PERSONNELINFOS_H
