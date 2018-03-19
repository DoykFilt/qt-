#include "model_rdv.h"

int ModelRdv::getID() const
{
    return ID;
}

void ModelRdv::setID(int value)
{
    ID = value;
}

int ModelRdv::getIDClient() const
{
    return IDClient;
}

void ModelRdv::setIDClient(int value)
{
    IDClient = value;
}

int ModelRdv::getIDRessource() const
{
    return IDRessource;
}

void ModelRdv::setIDRessource(int value)
{
    IDRessource = value;
}

ModelRdv::ModelRdv()
{
    ID=-1;
    IDClient=-1;
    IDRessource=-1;

}

ModelRdv::ModelRdv(int ID1, int IDClient1, int IDRessource1)
{
    ID=ID1;
    IDClient=IDClient1;
    IDRessource=IDRessource1;


}
