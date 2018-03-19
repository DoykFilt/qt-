#ifndef CONTROLLER_PERSONNE_H
#define CONTROLLER_PERSONNE_H
#include "QString"
#include "string"
#include "db_management.h"


class controller_personne
{
public:
    controller_personne();
    std::string computeString(QString qstring);
};

#endif // CONTROLLER_PERSONNE_H
