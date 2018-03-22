#include "view_mainwindow.h"
#include "ui_mainwindow.h"
#include "view_apropos.h"
#include "view_ajouterclient.h"
#include "view_modifclient.h"				 
#include "model_personnelinfos.h"
#include "model_type.h"
#include "view_modifpersonnel.h"
#include <QTreeView>
#include <QStandardItemModel>
#include <QDebug>
#include <QMessageBox>
#include <sstream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    //Affichage des clients
    createTableView();

    //Affichage du personnel
    createTreeView();

    statusBar()->showMessage(tr("Connecté"));
}

void MainWindow::createTableView(){
    if(modelClient!=NULL)
    {
        delete modelClient;
    }
    modelClient = new QSqlTableModel(this,DB_management::getInstance()->getDb());
    modelRecherche = new QSqlTableModel(this,DB_management::getInstance()->getDb());
    modelClient->setTable("TClient");
    modelClient->select();
    modelRecherche->setTable("TClient");
    modelRecherche->select();
    ui->tableViewClient->setModel(modelClient);
    ui->tableViewClient->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewClient_2->setModel(modelClient);
    ui->tableViewClient_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::createTreeView(){

    //Si l'arbre existe déjà on le delete. Ses enfants sont désalloué automatiquement
    if(ui->treeViewPersonnel->model() != NULL)
    {
        delete ui->treeViewPersonnel->model();
    }

    //Ensuite on créer l'arbre
    QStandardItemModel * standardModel = new QStandardItemModel(this);
    QStandardItem * rootNode = standardModel->invisibleRootItem();

    //On insère les noeuds des types
    std::vector<Type> types = Type::getListType();
    for(std::vector<Type>::iterator itT = types.begin(); itT != types.end(); itT++)
    {
        QStandardItem * typeItem = new QStandardItem(itT->getLabel());
        rootNode->appendRow(typeItem);
        typeItem->setEditable(false);
        typeItem->setSelectable(false);

        //On insère sous le type les ressources associés
        std::vector<personnelInfos> ressources = itT->getRessourcesRelatifs();
        for(std::vector<personnelInfos>::iterator itP = ressources.begin(); itP != ressources.end(); itP++)
        {
            std::stringstream out;
            out << itP->getID();
            QString qString = QString::fromStdString(out.str() + " | " + itP->getNom().toStdString());

            QStandardItem * ressourceItem = new QStandardItem(qString);
            ressourceItem->setEditable(false);
            typeItem->appendRow(ressourceItem);
        }
    }
    ui->treeViewPersonnel->setModel(standardModel);
    ui->treeViewPersonnel->expandAll();
}

MainWindow::~MainWindow()
{
    delete ui;
    if(modelClient!=NULL)
    {
        delete modelClient;
    }
    if(modelRessource!=NULL)
    {
        delete modelRessource;
    }
    if(modelRecherche!=NULL)
    {
        delete modelRecherche;
    }
}

void MainWindow::on_actionclient_triggered()
{
    AjouterClient* cw = new AjouterClient();
    if(cw->exec()==QDialog::Accepted)
    {
        statusBar()->showMessage(tr("Client ajouté"));
        createTableView();
        delete cw;
    }
    else
        statusBar()->showMessage(tr(""));
}

void MainWindow::on_actionQuitter_triggered()
{
    this->close();
}

void MainWindow::on_actionPersonnel_triggered()
{
    AjouterPersonnel* ap= new AjouterPersonnel();
    if(ap->exec()==QDialog::Accepted)
    {
        statusBar()->showMessage(tr("Personnel ajouté"));
        createTreeView();
        delete ap;
    }
    else
        statusBar()->showMessage(tr(""));

}

void MainWindow::on_actionA_propos_triggered()
{
    apropos.exec();
}

void MainWindow::on_BouttonRechercherClient_clicked()
{
    if(modelRecherche!=NULL)
    {
        delete modelRecherche;
    }
    modelRecherche = new QSqlTableModel(this,DB_management::getInstance()->getDb());
    modelRecherche->setTable("TClient");

    if(ui->dateRdvDebut->date() > ui->dateRdvFin->date())
    {
        QMessageBox::warning(this,"Erreur","L'intervalle des dates n'est pas valide");
    }
    if(ui->dateRdvDebut->date().toString(QString("yyyy-MM-dd")) == "2000-01-01" && ui->dateRdvFin->date().toString(QString("yyyy-MM-dd")) == "2000-01-01")
    {
        //les valeurs par défaut n'ont pas été modifié : pas de filtre sur la date
        modelRecherche->setFilter(QString("Nom LIKE '"+ui->lineNom->text()+"%'AND Prenom LIKE '" +ui->linePrenom->text()+"%' AND "
                                          "Id LIKE '"+ui->lineNumeroID->text()+"%'"));

    }
    else
    {
        //On applique le filtre
        modelRecherche->setFilter(QString("Nom LIKE '"+ui->lineNom->text()+"%'AND Prenom LIKE '"+ui->linePrenom->text()+"%' AND "
                                          "Id LIKE '"+ui->lineNumeroID->text()+"%'AND DateRdv BETWEEN '"+ui->dateRdvDebut->date().toString(QString("yyyy-MM-dd"))+""
                                          "' AND '"+ui->dateRdvFin->date().toString(QString("yyyy-MM-dd"))+"'"));

    }

    modelRecherche->select();
    ui->tableViewClient->setModel(modelRecherche);

    ui->tableViewClient->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::on_buttonSupprimerPersonnel_clicked()
{
    QModelIndex index = ui->treeViewPersonnel->currentIndex();
    index.row();
    if(!index.isValid())
        QMessageBox::warning(this,"Erreur","Veuillez sélectionner un élément");
    else {
        QVariant data = ui->treeViewPersonnel->model()->data(index);
        QString text = data.toString();

        if(text.compare("1 | Admin") == 0)
            QMessageBox::warning(this,"Erreur","Impossible de supprimer l'administrateur !");
        else{
            cPersonnel.supprimerPersonnel(text);
            createTreeView();
        }
	}
}

void MainWindow::on_buttonSupprimerClient_clicked()
{
    if(!ui->tableViewClient_2->currentIndex().isValid())
    {
        QMessageBox::warning(this,"Erreur","Veuillez sélectionner une case ou une ligne");
        return;
    }
	
    QModelIndex currentindex = ui->tableViewClient_2->currentIndex();
    qDebug() << ui->tableViewClient_2->model()->data( ui->tableViewClient_2->model()->index(currentindex.row(),0)).toString();
    qDebug() << "C Style Info Message";
    if(!cClient.supprimerClient(ui->tableViewClient_2->model()->data( ui->tableViewClient_2->model()->index(currentindex.row(),0)).toString()))
    {
        QMessageBox::warning(this,"Erreur","Erreur de suppression");
    }

    createTableView();
    statusBar()->showMessage(tr("Client Supprimé"));
}

void MainWindow::on_buttonModifierClient_clicked()
{
    if(!ui->tableViewClient_2->currentIndex().isValid())
    {
        QMessageBox::warning(this,"Erreur","Veuillez sélectionner une case ou une ligne");
        return;
    }

    QModelIndex currentindex = ui->tableViewClient_2->currentIndex();
    QString id = ui->tableViewClient_2->model()->data( ui->tableViewClient_2->model()->index(currentindex.row(),0)).toString();

    ModifClient* cw = new ModifClient(this,id);
    if(cw->exec()==QDialog::Accepted)
    {
        statusBar()->showMessage(tr("Client Modifié"));
        createTableView();
        delete cw;
    }
    else
        statusBar()->showMessage(tr(""));

}


void MainWindow::on_buttonModifierPersonnel_clicked()
{
    QModelIndex index = ui->treeViewPersonnel->currentIndex();
    index.row();
    if(!index.isValid())
        QMessageBox::warning(this,"Erreur","Veuillez sélectionner un élément");
    else {
        QVariant data = ui->treeViewPersonnel->model()->data(index);
        QString text = data.toString();

        if(text.compare("1 | Admin") == 0)
            QMessageBox::warning(this,"Erreur","Impossible de modifier l'administrateur !");
        else{

            ModifPersonnel* pw = new ModifPersonnel(this,text);
            if(pw->exec()==QDialog::Accepted)
            {
                statusBar()->showMessage(tr("Personnel Modifié"));
                createTreeView();
                delete pw;
            }
            else
                statusBar()->showMessage(tr(""));
        }
    }
}
