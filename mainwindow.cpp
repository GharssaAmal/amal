#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox> // Pour afficher les messages
#include "materiel.h"  // Assurez-vous d'inclure la classe Materiel
#include <QSqlQueryModel>
#include <QTableView>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QObject>
#include <QDate>
#include <QDateTime>
#include <QDateEdit>
#include <iostream>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Connectez le bouton ajouter_materiel au slot on_ajouter_Materiel_clicked
       connect(ui->ajouter_Materiel, &QPushButton::clicked, this, &MainWindow::on_ajouter_Materiel_clicked);
       connect(ui->supression_Materiel, &QPushButton::clicked, this, &MainWindow::on_supression_Materiel_clicked);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ajouter_Materiel_clicked()
{
    // Gather data from the UI fields
    int id = ui->id_materiel->text().toInt();
    QString nom = ui->nom_materiel->text();
    QString etat = ui->etat_materiel->text();
    QString date_achat = ui->date_achat_materiel->text();
    int duree_garantie = ui->duree_garantie_materiel->text().toInt();
    double prix = ui->prix_materiel->text().toDouble();
    int quantite_disponible = ui->quantite_materiel->text().toInt();
    int duree_de_vie = ui->duree_de_vie_materiel->text().toInt();

    // Create a Materiel object with the collected data
    Materiel materiel(id, nom, etat, date_achat, duree_garantie, prix, quantite_disponible, duree_de_vie);

    // Attempt to add the material to the database
    if (materiel.ajouter()) {
        // Refresh the table view to show the new entry
        ui->affichage->setModel(materiel.afficher());
        QMessageBox::information(this, tr("Success"), tr("Material added successfully."));
    } else {
        QMessageBox::critical(this, tr("Error"), tr("Failed to add material. The ID might already exist."));
    }
}

void MainWindow::on_modifier_Materiel_clicked() {
    // Retrieve data from the input fields and convert them to appropriate types
    int id = ui->id_materiel->text().toInt();
    QString nom = ui->nom_materiel->text();
    QString etat = ui->etat_materiel->text();
    QString date_achat = ui->date_achat_materiel->text();
    QString duree_garantie = ui->duree_garantie_materiel->text();
    double prix = ui->prix_materiel->text().toDouble();
    int quantite_disponible = ui->quantite_materiel->text().toInt();
    int duree_de_vie = ui->duree_de_vie_materiel->text().toInt();

    // Log input values for debugging
    qDebug() << "Attempting modification with ID:" << id;
    qDebug() << "New values - Nom:" << nom << ", Etat:" << etat
             << ", Date d'achat:" << date_achat << ", Durée de garantie:" << duree_garantie
             << ", Prix:" << prix << ", Quantité disponible:" << quantite_disponible
             << ", Durée de vie:" << duree_de_vie;

    // Create a Materiel object with the updated information
   Materiel materiel(id, nom, etat, date_achat, duree_garantie.toInt(), prix, quantite_disponible, duree_de_vie);
    // Attempt to modify the material record and log the result
    bool test = materiel.modifier(id);
    qDebug() << "Modifier function result:" << test;

    // Display a message based on the success of the modification
    if (test) {
        // Refresh the table view to reflect changes
        ui->affichage->setModel(materiel.afficher());
        QMessageBox::information(this, QObject::tr("OK"),
                                 QObject::tr("Modification effectuée\nCliquez sur Cancel pour quitter."),
                                 QMessageBox::Cancel);
    } else {
       QMessageBox::critical(this, QObject::tr("Erreur"),
                            QObject::tr("La modification n'a pas pu être effectuée.\nCliquez sur Cancel pour quitter."),
                           QMessageBox::Cancel);
    }
}

void MainWindow::on_supression_Materiel_clicked() {
    // Convert the text from the id_supp field to an integer
    int id = ui->id_supp->text().toInt();

    // Create a Materiel object and set its ID for deletion
    Materiel materiel;
    materiel.setId(id);

    // Call the supprimer() method of the Materiel object
    bool test = materiel.supprimer(materiel.getId());

    // Display a message based on the success of the deletion
    if (test) {
        // Refresh the table view only if the deletion succeeded
        ui->affichage->setModel(materiel.afficher());
        QMessageBox::information(this, QObject::tr("OK"),
                                 QObject::tr("Suppression effectuée\n"
                                             "Cliquez sur Annuler pour quitter."),
                                 QMessageBox::Cancel);
    } else {
        QMessageBox::critical(this, QObject::tr("Not OK"),
                              QObject::tr("Suppression non effectuée. Assurez-vous que l'ID existe.\n"
                                          "Cliquez sur Annuler pour quitter."),
                              QMessageBox::Cancel);
    }
}
