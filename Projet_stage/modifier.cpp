#include "modifier.h"
#include "ui_modifier.h"
#include <QDate>
#include <QSqlQuery>


Modifier::Modifier(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Modifier)
{
    ui->setupUi(this);
    //QString cinR = ui->cinrech->text();
    if(!mdconnection.openDataBase()) {
        //qDebug() <<"Failed to open databse";
        return;
    }
    mdconnection.openDataBase();
    QSqlQuery qry;
    qry.prepare("SELECT  Nom, Prenom, Email, Tel, Categorie FROM dbo.Personnel ps, dbo.Categorie cat WHERE cat.idCategorie=ps.idCategorie and ps.CNI= \'" +Cin+ "\' ");
    //QString idcat = qry.value(0).toString();
    //idcatAjoutPs=idcat;
    QString nom;
    QString prenom;
    if(qry.exec()) {
        while(qry.next())
        {
            nom=qry.value(0).toString();
            prenom=qry.value(1).toString();
            ui->nomrech->setText(qry.value(0).toString() );
            ui->prenomrech->setText(qry.value(1).toString() );
            ui->emailrech->setText(qry.value(2).toString() );
            ui->telrech->setText(qry.value(3).toString() );
            ui->cat->setText(qry.value(4).toString() );

        }
    }
    else {
       // QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    }

}
void Modifier::setCIN(QString name) {
    Cin=name;
}
Modifier::~Modifier()
{
    delete ui;
}

void Modifier::on_pushButton_clicked()
{
    QString nomrecherche = ui->nomrech->text();
    QString prenomrecherche = ui->prenomrech->text();
    QString telrecherche = ui->telrech->text();
    QString emailrecherche = ui->emailrech->text();
    QString cinrecherche = ui->cinrech->text();
    QString categorierecherche = ui->cat->text();
    mdconnection.modifierPersonnel(cinrecherche ,nomrecherche, prenomrecherche, telrecherche, emailrecherche);


    QDate createdDate;
    createdDate=QDate::currentDate();
    QString DateONHistorique;
    DateONHistorique=createdDate.toString("dd/MM/yyyy");
    QTime times = QTime::currentTime();
    QString TimeHistorique;
    TimeHistorique = times.toString();
    mdconnection.AjoutSurHistorique("Le personnel portant \'" +cinrecherche+ "\' a été modifié ",DateONHistorique, TimeHistorique);

}
