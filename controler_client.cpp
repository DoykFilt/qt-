#include "controler_client.h"

ControlerClient::ControlerClient(){

}

bool ControlerClient::testDate(QDate date){
    if(date < QDate::currentDate())
        return false;
    return true;
}

bool ControlerClient::ajouterClient(QString qprenom, QString qnom, QString qadresse,
                                      QString qville, QStringList affectations, QDate date,
                                      QString qtelephone, int CP, double duree,
                                    int priorite, QTextDocument * commentaire){
    return ci.ajouterClient(computeString(qprenom), computeString(qnom), qadresse, qville, affectations, date,
                     qtelephone, CP, duree, priorite, commentaire->toPlainText());

}

void ControlerClient::modifierClient(QString ID, QString qprenom, QString qnom,
                   QString qadresse, QString qville, QStringList affectations,
                   QDate date, QString qtelephone, int CP, double duree,
                                     int priorite, QTextDocument * commentaire)
{
    ci.modifierClient(ID,computeString(qprenom),computeString(qnom), qadresse, qville,affectations, date,
                      qtelephone,CP,duree, priorite,commentaire->toPlainText());
}

bool ControlerClient::supprimerClient(QString ID)
{
    return ci.supprimerClient(ID);
}
