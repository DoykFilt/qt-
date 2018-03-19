#include "controler_personne.h"

controller_personne::controller_personne()
{

}

std::string controller_personne::computeString(QString qstring){
    //On met une majuscule au premier caractère du nom et du prenom, le reste en minuscule
    std::string string = qstring.toStdString();
    std::transform(string.begin(), string.begin()+1, string.begin(), toupper);
    return string;
}
