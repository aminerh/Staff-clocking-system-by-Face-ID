#include "visualise.h"
#include "ui_visualise.h"
#include <QSqlQuery>
#include <QMessageBox>

Visualise::Visualise(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Visualise)
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
    QString id;
    QString nom;
    QString prenom;
    if(qry.exec()) {
        while(qry.next())
        {
            id="1";//get the id from the database i don t know the structure so well so do it when you can
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
    QString dossier=nom+"_"+prenom+"_"+id;
    bool valid =imageresh.load("C:/Users/PC/Desktop/stage/images/"+dossier+"/1.jpg");

    if(valid){
        imageresh=imageresh.scaledToWidth(ui->imgrech->width(),Qt::SmoothTransformation);
        ui->imgrech->setPixmap(QPixmap::fromImage(imageresh));
    }
}
void Visualise::setCIN(QString name) {
    Cin=name;
}

Visualise::~Visualise()
{
    delete ui;
}
