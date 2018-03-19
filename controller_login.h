#ifndef CONTROLLERLOGIN_H
#define CONTROLLERLOGIN_H

#include "db_management.h"
#include "model_compte.h"

class ControllerLogin
{
private :
    ModelCompte mc;
public:
    ControllerLogin();
    bool isLoginCorrect(QString login,QString password);
};

#endif // CONTROLLERLOGIN_H
