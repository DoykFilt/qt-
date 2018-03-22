#ifndef VIEW_MODIFPERSONNEL_H
#define VIEW_MODIFPERSONNEL_H

#include <QDialog>
#include "controler_personnel.h"

namespace Ui {
    class ModifPersonnel;
}

class ModifPersonnel : public QDialog
{
    Q_OBJECT

public:
    explicit ModifPersonnel(QWidget *parent = 0, QString ID="");
    ~ModifPersonnel();

private slots:
    void on_buttonAnnuler_clicked();
    void on_buttonOK_clicked();
    void on_comboBoxType_currentIndexChanged(const QString &arg1);

private:
    Ui::ModifPersonnel *ui;
    ControlerPersonnel controlerPersonnel;
};

#endif // VIEW_MODIFPERSONNEL_H
