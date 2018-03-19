#ifndef CONTROLER_CLIENT_H
#define CONTROLER_CLIENT_H

#include <QDate>
#include <QComboBox>
#include <QTextDocument>
#include "model_personne.h"
#include "controler_personne.h"
#include "model_clientinfos.h"


class ControlerClient : public controller_personne
{
private:
    ClientInfos ci;
public:
    ControlerClient();
    bool testDate(QDate date);
    bool ajouterClient(QString qprenom, QString qnom, QString qadresse,
                       QString qville, QString affectations, QDate date,
                       QString qtelephone, int CP, double duree,
                       int priorite, QTextDocument * commentaire);
    void modifierClient(QString ID, QString qprenom, QString qnom,
                       QString qadresse, QString qville, QString affectations,
                       QDate date, QString qtelephone, int CP, double duree,
                       int priorite, QTextDocument * commentaire);
    bool supprimerClient(QString ID);
};

#endif // CONTROLER_CLIENT_H
