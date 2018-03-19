#ifndef QLIGNEARBRE_H
#define QLIGNEARBRE_H

#include "QStandardItem"


class QLigneArbre : QStandardItem
{
public:
    QLigneArbre(int id, QString label);
    int getId();
private :
    int id;
};

#endif // QLIGNEARBRE_H
