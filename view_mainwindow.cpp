#include "view_mainwindow.h"
#include "ui_mainwindow.h"
#include "view_apropos.h"
#include "view_ajouterclient.h"
#include "view_modifclient.h"				 
#include "model_personnelinfos.h"
#include "model_type.h"
#include "qlignearbre.h"
#include <QTreeView>
#include <QStandardItemModel>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);

    //Affichage des clients
    modelClient = new QSqlTableModel(this,DB_management::getInstance()->getDb());
    modelClient->setTable("TClient");
    modelClient->select();
    ui->tableViewClient->setModel(modelClient);
    ui->tableViewClient->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewClient_2->setModel(modelClient);
    ui->tableViewClient_2->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //Affichage du personnel

    QStandardItemModel * standardModel = new QStandardItemModel(this);
    QStandardItem * rootNode = standardModel->invisibleRootItem();

    std::vector<Type> types = Type::getListType();
    for(std::vector<Type>::iterator itT = types.begin(); itT != types.end(); itT++)
    {
        QStandardItem * typeItem = new QStandardItem(itT->getLabel());
        rootNode->appendRow(typeItem);
        typeItem->setEditable(false);
        typeItem->setSelectable(false);
        std::vector<personnelInfos> ressources = itT->getRessourcesRelatifs();
        for(std::vector<personnelInfos>::iterator itP = ressources.begin(); itP != ressources.end(); itP++)
        {
            /*
            QStandardItem * ressourceItem = new QStandardItem(itP->getNom());
            ressourceItem->setEditable(false);
            typeItem->appendRow(ressourceItem);*/
            //QLigneArbre * ressourceItem = new QLigneArbre(itP->getID(), itP->getNom());
            //typeItem->appendRow(ressourceItem);

        }
    }
    ui->treeViewPersonnel->setModel(standardModel);
    ui->treeViewPersonnel->expandAll();

    statusBar()->showMessage(tr("Connecté"));
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
}

void MainWindow::on_actionclient_triggered()
{
    AjouterClient* cw = new AjouterClient();
    if(cw->exec()==QDialog::Accepted)
    {
        statusBar()->showMessage(tr("Client ajouté"));
        if(modelClient!=NULL)
        {
            delete modelClient;
        }
        modelClient = new QSqlTableModel(this,DB_management::getInstance()->getDb());
        modelClient->setTable("TClient");
        modelClient->select();
        ui->tableViewClient->setModel(modelClient);
        ui->tableViewClient->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tableViewClient_2->setModel(modelClient);
        ui->tableViewClient_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
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

}

void MainWindow::on_bouttonModifierPersonnel_clicked()
{
    /*QModelIndex index = ui->treeViewPersonnel->currentIndex();
    QVariant data = ui->treeViewPersonnel->model()->data(index);
    if(data.canConvert<personnelInfos>())
        personnelInfos personnel = data.value<personnelInfos>();*/
    //personnelInfos personnel = qvariant_cast<personnelInfos>(data);
}

void MainWindow::on_buttonSupprimerPersonnel_clicked()
{
    QModelIndex index = ui->treeViewPersonnel->currentIndex();
    if(!index.isValid())
        QMessageBox::warning(this,"Erreur","Veuillez sélectionner un élément");
    else {
        QVariant data = ui->treeViewPersonnel->currentIndex().data();
        int id = data.toInt();
        cPersonnel.supprimerPersonnel(id);

        QModelIndexList indexes = ui->treeViewPersonnel->selectionModel()->selectedIndexes();
        if (indexes.size() > 0) {
            QModelIndex selectedIndex = indexes.at(0);
            selectedIndex.data();
		}
	}
}

void MainWindow::on_buttonSupprimerClient_clicked()
{
    if(!ui->tableViewClient_2->currentIndex().isValid())
    {
        QMessageBox::warning(this,"Erreur","Veuillez sélectionner une case ou une ligne");
    }
	
    QModelIndex currentindex = ui->tableViewClient_2->currentIndex();
    qInfo() << ui->tableViewClient_2->model()->data( ui->tableViewClient_2->model()->index(currentindex.row(),0)).toString();
    qInfo( "C Style Info Message" );
    if(!cClient.supprimerClient(ui->tableViewClient_2->model()->data( ui->tableViewClient_2->model()->index(currentindex.row(),0)).toString()))
    {
        QMessageBox::warning(this,"Erreur","Erreur de suppression");
    }

    if(modelClient!=NULL)
    {
        delete modelClient;
    }
    modelClient = new QSqlTableModel(this,DB_management::getInstance()->getDb());
    modelClient->setTable("TClient");
    modelClient->select();
    ui->tableViewClient->setModel(modelClient);
    ui->tableViewClient->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewClient_2->setModel(modelClient);
    ui->tableViewClient_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    statusBar()->showMessage(tr("Client Supprimé"));
}

void MainWindow::on_buttonModifierClient_clicked()
{
    if(!ui->tableViewClient_2->currentIndex().isValid())
    {
        QMessageBox::warning(this,"Erreur","Veuillez sélectionner une case ou une ligne");
    }

    QModelIndex currentindex = ui->tableViewClient_2->currentIndex();
    QString id = ui->tableViewClient_2->model()->data( ui->tableViewClient_2->model()->index(currentindex.row(),0)).toString();

    ModifClient* cw = new ModifClient(this,id);
    if(cw->exec()==QDialog::Accepted)
    {
        statusBar()->showMessage(tr("Client Modifié"));
        if(modelClient!=NULL)
        {
            delete modelClient;
        }
        modelClient = new QSqlTableModel(this,DB_management::getInstance()->getDb());
        modelClient->setTable("TClient");
        modelClient->select();
        ui->tableViewClient->setModel(modelClient);
        ui->tableViewClient->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tableViewClient_2->setModel(modelClient);
        ui->tableViewClient_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
        delete cw;
    }
    else
        statusBar()->showMessage(tr(""));

}

