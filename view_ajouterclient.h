#ifndef AJOUTERCLIENT_H
#define AJOUTERCLIENT_H

#include <QDialog>
#include "controler_client.h"
#include <db_management.h>

namespace Ui {
class AjouterClient;
}

class AjouterClient : public QDialog
{
    Q_OBJECT

public:
    explicit AjouterClient(QWidget *parent = 0);
    ~AjouterClient();

private slots:
    void on_buttonAnnuler_clicked();

    void on_buttonOK_clicked();

private:
    Ui::AjouterClient *ui;
    ControlerClient controlerClient;
    QStringList listRessources;
    QStringList listId;

};

#endif // AJOUTERCLIENT_H
