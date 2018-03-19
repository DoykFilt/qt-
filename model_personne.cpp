#include "model_personne.h"

int ModelPersonne::getID() const
{
    return ID;
}

ModelPersonne::ModelPersonne(QString nom1,QString prenom1, int id)
{
    nom=nom1;
    prenom=prenom1;
    ID=id;
}

QString ModelPersonne::getNom() const
{
    return nom;
}

void ModelPersonne::setNom(const QString &value)
{
    nom = value;
}

QString ModelPersonne::getPrenom() const
{
    return prenom;
}

void ModelPersonne::setPrenom(const QString &value)
{
    prenom = value;
}

void ModelPersonne::setID(int value)
{
    ID = value;
}

ModelPersonne::ModelPersonne()
{
    nom = "";
    prenom = "";
    ID = -1;
}
