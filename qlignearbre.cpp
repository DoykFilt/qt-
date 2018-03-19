#include "qlignearbre.h"


QLigneArbre::QLigneArbre(int ID, QString label){
    QStandardItem(label);
    id = ID;
    setEditable(false);
}
int QLigneArbre::getId(){
    return id;
}
