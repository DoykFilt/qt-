#ifndef VIEW_AJOUTERPERSONNEL_H
#define VIEW_AJOUTERPERSONNEL_H

#include <QDialog>
#include "controler_personnel.h"

namespace Ui {
    class AjouterPersonnel;
}

class AjouterPersonnel : public QDialog
{
    Q_OBJECT

public:
    explicit AjouterPersonnel(QWidget *parent = 0);
    ~AjouterPersonnel();

private slots:
    void on_buttonAnnuler_clicked();
    void on_buttonOK_clicked();

    void on_comboBoxType_currentIndexChanged(const QString &arg1);

private:
    Ui::AjouterPersonnel *ui;
    ControlerPersonnel controlerPersonnel;
    QStringList ListType;
};

#endif // VIEW_AJOUTERPERSONNEL_H
