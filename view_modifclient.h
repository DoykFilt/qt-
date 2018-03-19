#ifndef MODIFCLIENT_H
#define MODIFCLIENT_H

#include <QDialog>
#include "controler_client.h"

namespace Ui {
class ModifClient;
}

class ModifClient : public QDialog
{
    Q_OBJECT

public:
    explicit ModifClient(QWidget *parent = 0);
    ~ModifClient();

private slots:
    void on_bouttonAppliquer_clicked();

    void on_bouttonOK_clicked();

    void on_bouttonAnnuler_clicked();

private:
    Ui::ModifClient *ui;
    ControlerClient controlerClient;
};

#endif // MODIFCLIENT_H
