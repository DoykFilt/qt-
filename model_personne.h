#ifndef MODEL_PERSONNE_H
#define MODEL_PERSONNE_H

#include "string"
#include "QString"

class ModelPersonne
{
private:
    QString nom;
    QString prenom;
    int ID;
public:
    ModelPersonne();
    ModelPersonne(QString nom1,QString prenom1, int id);
    QString getNom() const;
    void setNom(const QString &value);
    QString getPrenom() const;
    void setPrenom(const QString &value);
    int getID() const;
    void setID(int value);

    std::string computeString(QString qstring);
};

#endif // MODEL_PERSONNE_H
