#ifndef MODEL_COMPTE_H
#define MODEL_COMPTE_H
#include <QString>
#include "db_management.h"


class ModelCompte
{
private :
int Id;
int IdRessource;
QString Login;
QString Mdp;
public:
    ModelCompte();
    ModelCompte(int Id1,int IdRessource1,QString Login1,QString Mdp1);
    int getId() const;
    void setId(int value);
    int getIdRessource() const;
    void setIdRessource(int value);
    QString getLogin() const;
    void setLogin(const QString &value);
    QString getMdp() const;
    void setMdp(const QString &value);
    bool isLoginCorrect(QString login,QString password);
};

#endif // MODEL_COMPTE_H
