#ifndef CLIENTINFO_H
#define CLIENTINFO_H
#include <QString>
#include <QDate>
#include <QVector>
#include <vector>
#include "model_personne.h"
#include "db_management.h"

class ClientInfos : public ModelPersonne
{
private :
    QString adresse;
    QString ville;
    int codePostal;
    QDate dateRdv;
    int dureeRdv;
    int priorite;
    QString tel;
    QVector<int> id_ressources;


public:
    ClientInfos();
    ClientInfos(int ID, QString n, QString p, QString a, QString v,int CP,QDate drdv, int dureeConsultation, int prio,QString t, QVector<int> * ids);
    ClientInfos(int ID, int dureeConsultation, int prio);


    QString getAdresse() const;
    void setAdresse(const QString &value);
    QString getVille() const;
    void setVille(const QString &value);
    int getCodePostal() const;
    void setCodePostal(int value);
    QDate getDateRdv() const;
    void setDateRdv(const QDate &value);
    int getDureeRdv() const;
    void setDureeRdv(int value);
    int getPriorite() const;
    void setPriorite(int value);
    QString getTel() const;
    void setTel(const QString &value);
    QVector<int>* getId_ressources();
    void setId_ressources(QVector<int> *value1);
    bool ajouterClient(QString qprenom, QString qnom, QString qadresse,
                       QString qville, QStringList affectations, QDate date,
                       QString qtelephone, int CP, double duree,
                       int priorite, QString commentaire);
    bool supprimerClient(QString id);
    bool modifierClient(QString Id, QString qprenom, QString qnom, QString qadresse, QString qville, QStringList affectations, QDate date, QString qtelephone, int CP, double duree, int priorite, QString commentaire);
};

#endif // CLIENTINFO_H
