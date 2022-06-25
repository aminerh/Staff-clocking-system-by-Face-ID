#include "dbconnection.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QDebug>
#include <QListView>

dbconnection::dbconnection()
{
    MyDB= QSqlDatabase::addDatabase("QODBC");
}

bool dbconnection::openDataBase(QString *error){
    MyDB.setDatabaseName("DRIVER={SQL SERVER};SERVER=WIN-9SCM6JLQTD9;DATABASE=PFET;UID=sa;PWD=FalahFes123");
    if(!MyDB.open()){
        if(error != nullptr){
            *error = MyDB.lastError().text();
        }
        return false;
    }
    return true;
}

void dbconnection::closeconnection() {
    MyDB.close();
}

/*bool dbconnection::loadCombos(QString User, QString Pwd)
{


        QSqlQueryModel * modal = new QSqlQueryModel();
        QSqlQuery* qry;
        qry->prepare("SELECT FaceID FROM templateinfo");
        qry->exec();
        modal->setQuery(*qry);

        //ui->comboBox->setModel(modal);

        qry->next();
        qDebug() << (modal->rowCount());
}*/

bool dbconnection::verifie(QString User, QString Pwd)
{
    if(!MyDB.isOpen()){

        return false;
    }
    QSqlQuery qry;
    if(qry.exec("Select Email, Mdp FROM dbo.Admin  WHERE Email=\'"+ User +"\' AND Mdp=\'"+ Pwd +"\'") ){
        if(qry.next())
        {
           return true;
        }else{
           return false;
        }
    }
    return false;
}

bool dbconnection::loadtable(QTableView* table,QString periodedebut, QString periodefin , QString weekS,QString weekE,QString day,QString category)
{

    if(!MyDB.isOpen()){
        return false;
    }
    QSqlQueryModel * modal = new QSqlQueryModel();
        modal->setQuery("Select  ps.CNI , ps.Nom, ps.Prenom , cat.Categorie, abs.Access, acs.Date, acs.int, acs.out From dbo.Personnel ps, dbo.Categorie cat, dbo.Periode pr, dbo.Semaine sem, dbo.Jour jr, dbo.Absent abs, dbo.Access acs Where ps.idCategorie=cat.idCategorie and pr.idCategorie=cat.idCategorie and sem.idPeriode=pr.idPeriode and abs.idPerso=ps.idPerso and abs.idJour=jr.idJour and acs.idPerso=ps.idPerso and acs.idJour=jr.idJour  and pr.PeriodeDebut= \'"+ periodedebut +"\' and pr.PeriodeFin= \'"+ periodefin +"\' and sem.SemaineDebut=\'"+ weekS +"\' and sem.SemaineFin= \'"+ weekE +"\' and jr.Jour= \'"+ day +"\'  and cat.Categorie= \'"+ category +"\' ");
        table->setModel(modal);

    return true;
}

bool dbconnection::loadtableCategorie(QTableView* table,QString category)
{

    if(!MyDB.isOpen()){
        return false;
    }
    QSqlQueryModel * modal = new QSqlQueryModel();
        modal->setQuery("Select  ps.CNI , ps.Nom, ps.Prenom , cat.Categorie, abs.Access, acs.Date, acs.int, acs.out From dbo.Personnel ps, dbo.Categorie cat, dbo.Absent abs, dbo.Access acs Where ps.idCategorie=cat.idCategorie and abs.idPerso=ps.idPerso  and acs.idPerso=ps.idPerso  and  cat.Categorie= \'"+ category +"\' ");
        table->setModel(modal);

    return true;
}




bool dbconnection::loadListView(QListView* view)
{

    if(!MyDB.isOpen()){
        return false;
    }
    QSqlQueryModel * modal = new QSqlQueryModel();
        modal->setQuery("SELECT Date FROM dbo.Historique");
        view->setModel(modal);

    return true;
}

/*bool dbconnection::loadtableCategorie(QTableView* table,QString category)
{

    if(!MyDB.isOpen()){
        return false;
    }
    QSqlQueryModel * modal = new QSqlQueryModel();
        modal->setQuery("Select  ps.CNI , ps.Nom, ps.Prenom , cat.Categorie, abs.Access, acs.Date, acs.int, acs.out From dbo.Personnel ps, dbo.Categorie cat, dbo.Absent abs, dbo.Access acs Where ps.idCategorie=cat.idCategorie and abs.idPerso=ps.idPerso  and acs.idPerso=ps.idPerso  and  cat.Categorie= \'"+ category +"\' ");
        table->setModel(modal);

    return true;
}*/








bool dbconnection::loadtablePeriode(QTableView *table, QString category, QString periodedebut, QString periodefin)
{

    if(!MyDB.isOpen()){
        return false;
    }
    QSqlQueryModel * modal = new QSqlQueryModel();
        modal->setQuery("Select  ps.CNI , ps.Nom, ps.Prenom , cat.Categorie, abs.Access, acs.Date, acs.int, acs.out From dbo.Personnel ps, dbo.Categorie cat, dbo.Periode pr, dbo.Absent abs, dbo.Access acs Where ps.idCategorie=cat.idCategorie and abs.idPerso=ps.idPerso  and acs.idPerso=ps.idPerso  and cat.Categorie= \'" +category+ "\' and pr.idPeriode=cat.idCategorie  and pr.PeriodeDebut= \'" +periodedebut+ "\' and pr.PeriodeFin= \'" +periodefin+ "\'  ");
        table->setModel(modal);

    return true;
}

bool dbconnection::loadtableSemaine(QTableView* table,QString weekS,QString weekE,QString category, QString periodedebut, QString periodefin)
{

    if(!MyDB.isOpen()){
        return false;
    }
    QSqlQueryModel * modal = new QSqlQueryModel();
        modal->setQuery("Select  ps.CNI , ps.Nom, ps.Prenom , cat.Categorie, abs.Access, acs.Date, acs.int, acs.out From dbo.Personnel ps, dbo.Categorie cat, dbo.Periode pr, dbo.Semaine sm , dbo.Absent abs, dbo.Access acs Where ps.idCategorie=cat.idCategorie and sm.idPeriode=pr.idPeriode and abs.idPerso=ps.idPerso  and acs.idPerso=ps.idPerso  and cat.Categorie= \'" +category+ "\' and pr.idPeriode=cat.idCategorie  and pr.PeriodeDebut= \'" +periodedebut+ "\' and pr.PeriodeFin= \'" +periodefin+ "\' and sm.SemaineDebut= \'" +weekS+ "\' and  sm.SemaineFin= \'" +weekE+ "\' ");
        table->setModel(modal);

    return true;
}

int dbconnection::getCategoriID(QString nom)
{
    if(!MyDB.isOpen()){
        return -1;
    }
    QSqlQuery qry;
    if(qry.exec("Select idCategorie FROM dbo.Categorie WHERE Categorie=\'"+ nom +"\'") ){
        while (qry.next()) {
               int salary = qry.value(0).toInt();
               return salary;
           }
    }
    return -1;

}

int dbconnection::getPeriodeID(QString PeriodeDebut, QString PeriodeFin)
{
    if(!MyDB.isOpen()){
        return -1;
    }
    QSqlQuery qry;
    if(qry.exec("Select idPeriode FROM dbo.Periode WHERE PeriodeDebut=\'"+ PeriodeDebut +"\' and PeriodeFin=\'"+ PeriodeFin +"\' ") ){
        while (qry.next()) {
               int salary = qry.value(0).toInt();
               return salary;
           }
    }
    return -1;

}


bool dbconnection::ajouterPersonnel(QString cin,QString nom,QString prenom, QString tel, QString email, QString categorie){
    if(!MyDB.isOpen()){
        return false;
    }
    QSqlQuery query;
        query.prepare("INSERT INTO dbo.Personnel (cni,nom,prenom, tel, email, idCategorie) "
                      "VALUES (?, ?, ?,?,?)");
        query.addBindValue(cin);
        query.addBindValue(nom);
        query.addBindValue(prenom);
        query.addBindValue(tel);
        query.addBindValue(email);
        query.addBindValue(getCategoriID(categorie));
        query.exec();

    return true;

}

bool dbconnection::modifierPersonnel(QString cinR,QString nomR,QString prenomR, QString telR, QString emailR){
    if(!MyDB.isOpen()){
        return false;
    }
    //int idcatint = getCategoriID(categorieR);
    //QString s = QString::number(idcatint);
    QSqlQuery query;
            query.prepare("UPDATE dbo.Personnel SET  Nom=:nomR, Prenom=:prenomR, Tel=:telR, Email=:emailR WHERE CNI=:cinR");
            query.bindValue(":nomR", nomR);
            query.bindValue(":prenomR", prenomR);
            query.bindValue(":telR", telR);
            query.bindValue(":emailR", emailR);
            query.bindValue(":cinR", cinR);
            query.exec();

    return true;

}

bool dbconnection::AjoutSurHistorique(QString message, QString Date, QString Heure){
    if(!MyDB.isOpen()){
        return false;
    }
    QSqlQuery query;
    query.prepare("INSERT INTO dbo.Historique (Date, Heure, Historique) "
                  "VALUES (?, ?, ?)");
    query.addBindValue(Date);
    query.addBindValue(Heure);
    query.addBindValue(message);
    query.exec();


    return true;

}



