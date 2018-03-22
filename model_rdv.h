#ifndef MODELRDV_H
#define MODELRDV_H
#include <QVector>

class ModelRdv
{
private :
    int ID;
    int IDClient;
    int IDRessource;

public:
    ModelRdv();
    ModelRdv(int ID1,int IDClient1,int IDRessource1);

    int getID() const;
    void setID(int value);
    int getIDClient() const;
    void setIDClient(int value);
    int getIDRessource() const;
    void setIDRessource(int value);

    static QVector<int> getListRessources(int idClient);
};

#endif // MODELRDV_H
