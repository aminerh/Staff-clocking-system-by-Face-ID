#ifndef DBCONNECTION_H
#define DBCONNECTION_H


#include <QSqlDatabase>
#include <QTableView>
#include <QListView>
//#include "perssonel.h"



class dbconnection
{
public:
    dbconnection();
    bool openDataBase(QString *error = nullptr);
    bool loadCombos(QString User,QString Pwd);
    bool verifie(QString User,QString Pwd);
    bool loadtable(QTableView* table,QString weekS,QString weekE,QString day,QString category, QString periodedebut, QString periodefin);
    bool loadtableCategorie(QTableView* table,QString category);
    bool loadtablePeriode(QTableView* table,QString category, QString periodedebut, QString periodefin);
    bool loadtableSemaine(QTableView* table,QString weekS,QString weekE,QString category, QString periodedebut, QString periodefin);
    int getCategoriID(QString nom);
    int getPeriodeID(QString PeriodeDebut, QString PeriodeFin);
    void closeconnection();
    bool ajouterPersonnel(QString cin,QString nom,QString prenom, QString tel, QString email, QString categorie);
    bool modifierPersonnel(QString cin,QString nom,QString prenom, QString tel, QString email);
    bool AjoutSurHistorique(QString message, QString Date, QString Heure);
    bool loadListView(QListView* view);

QSqlDatabase MyDB2;


private:
    QSqlDatabase MyDB;
};



#endif // DBCONNECTION_H
