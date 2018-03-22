#ifndef PERSONNELINFOS_H
#define PERSONNELINFOS_H
#include "model_personne.h"
#include <QVector>


class personnelInfos : public ModelPersonne
{
private :
    int type;

public:
    personnelInfos();
    personnelInfos(int ID, QString n,QString p, int type1);
    int getType() const;
    void setType(const int &value);

    void db_charger();
    bool db_supprimer();
    bool db_ajouter(QString nom, QString prenom,int type,QString password);
    static QVector<personnelInfos> db_getListPersonnel(bool withoutAdmin);
};

#endif // PERSONNELINFOS_H
