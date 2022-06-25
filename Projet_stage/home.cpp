#include "home.h"
#include "QDate"
#include "ui_home.h"
#include <QProcess>
#include <QDir>
#include <QMessageBox>
#include <QFileDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QDebug>
#include <dbconnection.h>
#include <QPrintDialog>
#include <QPrinter>
#include <QTextDocument>
#include <QDate>
#include <QTimer>
#include <QtMultimedia/QCameraInfo>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QTime>
#include <QImage>


Home::Home(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home), mdconnection()
{
    ui->setupUi(this);
      QDateTime current = QDateTime::currentDateTime();
     ui->label_4->setText(current.toString("dddd le dd/MM/yyyy"));
     ui->stackedWidget->setCurrentIndex(0);
     ui->stackedWidget2->setCurrentIndex(0);
     ui->tableView->horizontalHeader ()->setStyleSheet ("QHeaderView{font: 14pt Arial; color: blue; font-weight: bold;}");
     ui->tableView->verticalHeader ()->setVisible (false);
     ui->tableView->setAlternatingRowColors (true);
    // ui->tableView->setStyleSheet ("alternate-background-color: cyan; background-color: #333;");
     ui->refreshbutton->setIcon(QIcon("D:/stage/Projet_stage/images/refresh.png"));


     ui->rechtable->setVisible(false);
     ui->visualiser->setVisible(false);
     ui->modifier->setVisible(false);
     ui->supprimer->setVisible(false);



}



Home::~Home()
{
    delete ui;
}



QString idcatglobal;
void Home::loadComboCategorie()
{

    /*if(qryperiode.exec()) {
        while(qryperiode.next())
        {
            ui->Periodee->addItem(qryperiode.value(0).toString()+"->"+qryperiode.value(1).toString() );

        }
        dbc.closeconnection();
    }
    else {
        QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    }


*/

    /* ----------------------------------------------------------*/


qDebug() <<"id categorie est : \'"+idcatglobal+"\' ";


    /*QSqlQueryModel * modal = new QSqlQueryModel();
    QSqlQuery* qry = new QSqlQuery(MyDB);
    qry->prepare("SELECT Categorie FROM dbo.Categorie");
    qry->exec();
    modal->setQuery(*qry);

    ui->category->setModel(modal);

    qry->next();
    qDebug() << (modal->rowCount());
*/
}


void Home::loadComboPeriode()
{
    ui->Periodee->clear();
    QSqlQuery qryperiode;
    qryperiode.prepare("SELECT pr.PeriodeDebut, pr.PeriodeFin FROM dbo.Periode pr WHERE pr.idCategorie=\'"+ idcatglobal +"\' ");
    if(qryperiode.exec()) {
        while(qryperiode.next())
        {
            ui->Periodee->addItem(qryperiode.value(0).toString()+"->"+qryperiode.value(1).toString() );

        }
        //dbc.closeconnection();
    }
    else {
        QMessageBox::critical(this,tr("error::"),qryperiode.lastError().text());
    }



}

void Home::loadComboSemaine()
{


}


void Home::loadComboJour()
{


}

void Home::on_nav2_clicked()
{
    ui->label_2->setText("Espace Admin");
    ui->stackedWidget->setCurrentIndex(1);
    ui->espace_admin->setCurrentIndex(0);
}

void Home::on_nav1_clicked()
{
    ui->label_2->setText("Bonjour");
     ui->stackedWidget->setCurrentIndex(0);
}

void Home::on_nav3_clicked()
{
    ui->label_2->setText("Espace Pointage");
     ui->stackedWidget->setCurrentIndex(2);
     QString path1 = QCoreApplication::applicationDirPath();
         QString  command1("python");
         QStringList params1 = QStringList() << "D:/stage/faces-train.py";

         QProcess *process1 = new QProcess();
         process1->startDetached(command1, params1, path1);
         process1->waitForFinished();
         process1->close();

    /* QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
         foreach (const QCameraInfo &cameraInfo, cameras) {
             qDebug() << "Name: " << cameraInfo.deviceName();
             qDebug() << "Position: " << cameraInfo.position();
             qDebug() << "Orientation: " << cameraInfo.orientation();
             ui->camerainfo->addItem(cameraInfo.deviceName());
         } */
         const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
         for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
             if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
                  //qDebug() << address.toString();
                ui->ipinfo->addItem(address.toString());

         }
}

void Home::on_nav4_clicked()
{

}

void Home::on_nav5_clicked()
{

}

void Home::on_nav6_clicked()
{
     QApplication::quit();
}

void Home::on_add_pers_clicked()
{
     ui->espace_admin->setCurrentIndex(0);

}

void Home::on_add_cat_clicked()
{
      ui->espace_admin->setCurrentIndex(2);
}

void Home::on_historique_clicked()
{
    ui->espace_admin->setCurrentIndex(1);
    //mdconnection.loadListView(ui->listViewHistorique);
    QSqlQueryModel* model = new QSqlQueryModel();
    mdconnection.openDataBase();
    QSqlQuery* query = new QSqlQuery(mdconnection.MyDB2);
    query->prepare("Select Historique From dbo.Historique ORDER BY idHistorique ASC");
    query->exec();
    model->setQuery(*query);
    ui->listViewHistorique->setModel(model);

}


void Home::on_logo_clicked()
{
    ui->label_2->setText("Bonjour");
     ui->stackedWidget->setCurrentIndex(0);
}



void Home::on_fiche_presence_clicked()
{
     ui->espace_admin->setCurrentIndex(5);
     //ui->Add_pics->setVisible(false);
}

void Home::on_fiche_presence_2_clicked()
{
 ui->espace_admin->setCurrentIndex(3);
}

void Home::on_pushButton_3_clicked()
{
    QDate createdDate;
    createdDate=QDate::currentDate();
    QString DateONHistorique;
    DateONHistorique=createdDate.toString("dd/MM/yyyy");
    QTime times = QTime::currentTime();
    QString TimeHistorique;
    TimeHistorique = times.toString();
    mdconnection.AjoutSurHistorique("La Camera de surveillance a déclenché le pointage ",DateONHistorique, TimeHistorique);

    QString path = QCoreApplication::applicationDirPath();
    QString  command("python");
    QStringList params = QStringList() << "D:/stage/Projet_stage/main_window.py";

    QProcess *process = new QProcess();
    process->startDetached(command, params, path);

    process->waitForFinished();
    process->close();



}

void Home::on_Add_pics_clicked()
{
    QString nom=ui->nom->text();
    QString prenom=ui->prenom->text();
    QString dossier=nom+"_"+prenom+"_";

    QDir fold("D:/stage/images/"+dossier);
        if(fold.exists()){
            QMessageBox::critical(this, tr("Error!"), tr("Exist deja"));
        }else{
            QDir dir;
                bool ok = dir.mkpath("D:/stage/images/"+dossier);     //this function creates the path, with all its necessary parents;

                if(!ok)
                {
                    //error message, could not create the required directory structure!
                     QMessageBox::critical(this, tr("Error!"), tr("Error creating directory structure"));
                    return;
                }

                pics = new Images();
                pics->show();
                pics->setfilename(dossier);

        }
}

void Home::on_pushButton_2_clicked()
{
    QString categoryrecherche=ui->category->currentText();
    QString periode=ui->Periodee->currentText();
    QString week=ui->week->currentText();
    QString day=ui->day->currentText();
    QString periodedebut;
    QString periodefin;
    QString startweek;
    QString endweek;
    if(categoryrecherche!="------") {
        categoryrecherche=ui->category->currentText();
    } else if(periode!="------"){
        QStringList list2 = periode.split("->");
        QString periodedebut=list2[0];
        QString periodefin=list2[1];
    } else if(week!="------"){
        QStringList list1 = week.split("->");
        QString startweek=list1[0];
        QString endweek=list1[1];
    }else if(day=="------"){
            day = "";
    }




    if(categoryrecherche=="------") {
        categoryrecherche = "";
    } else if(periode=="------"){
        periodedebut = "";
        periodefin = "";
    } else if(week=="------"){
        startweek = "";
        endweek = "";
    }else if(day=="------"){
            day = "";
    }

    if(periodedebut==""){
        mdconnection.loadtableCategorie(ui->tableView,categoryrecherche);
    }/*else if (){

    }*/
    else{
    mdconnection.loadtable(ui->tableView,periodedebut,periodefin,startweek,endweek,day,categoryrecherche);
    }

}
int categorybuzz = 0;
void Home::on_category_activated(int index)
{
    if (ui->category->count()==1 ){
        ui->category->clear();
        /*ui->Periodee->clear();
        ui->week->clear();
        ui->day->clear();
        ui->Periodee->addItem(("------"));
        ui->week->addItem(("------"));
        ui->day->addItem(("------"));*/
        categorybuzz++;
        //dbconnection dbc;
        if(!mdconnection.openDataBase()) {
            qDebug() <<"Failed to open databse";
            return;
        }
        mdconnection.openDataBase();
        QSqlQuery qry;
        //QSqlQuery qry, qryperiode;
        qry.prepare("SELECT idCategorie, Categorie FROM dbo.Categorie");
        QString idcat = qry.value(0).toString();
        idcatglobal=idcat;
        //qryperiode.prepare("SELECT pr.PeriodeDebut, pr.PeriodeFin FROM dbo.Periode pr WHERE pr.idCategorie=\'"+ idcat +"\' ");
        if(qry.exec()) {
            while(qry.next())
            {
                ui->category->addItem(qry.value(1).toString() );

            }
            //mdconnection.closeconnection();
        }
        else {
            QMessageBox::critical(this,tr("error::"),qry.lastError().text());
        }
        qDebug() <<"ID is : \'"+idcatglobal+"\'";
    } else if(categorybuzz>0){
        //ui->category->clear();
        ui->Periodee->clear();
        ui->week->clear();
        ui->day->clear();
        ui->Periodee->addItem(("------"));
        ui->week->addItem(("------"));
        ui->day->addItem(("------"));
        categorybuzz++;
        //dbconnection dbc;
        if(!mdconnection.openDataBase()) {
            qDebug() <<"Failed to open databse";
            return;
        }
        mdconnection.openDataBase();
        QSqlQuery qry;
        //QSqlQuery qry, qryperiode;
        qry.prepare("SELECT idCategorie, Categorie FROM dbo.Categorie");
        QString idcat = qry.value(0).toString();
        idcatglobal=idcat;
        //qryperiode.prepare("SELECT pr.PeriodeDebut, pr.PeriodeFin FROM dbo.Periode pr WHERE pr.idCategorie=\'"+ idcat +"\' ");
        if(qry.exec()) {
            while(qry.next())
            {
                ui->category->addItem(qry.value(1).toString() );

            }
            //mdconnection.closeconnection();
        }
        else {
            QMessageBox::critical(this,tr("error::"),qry.lastError().text());
        }
        qDebug() <<"ID is : \'"+idcatglobal+"\'";

    }
    //QStringList listt = ui->category->mousePressEvent()


}



void Home::on_Periodee_activated(int index)
{
    if (ui->Periodee->count()==1){
        ui->Periodee->clear();
        //dbconnection dbv;
        if(!mdconnection.openDataBase()) {
            qDebug() <<"Failed to open databse";
            return;
        }
        mdconnection.openDataBase();
        QSqlQuery qry;
        QString currentcat = ui->category->currentText();
        int idcategorie = mdconnection.getCategoriID(currentcat);
        QString s = QString::number(idcategorie);
        qry.prepare("SELECT pr.PeriodeDebut, pr.PeriodeFin FROM dbo.Periode pr WHERE pr.idCategorie=\'"+ s + "\' ");


        if(qry.exec()) {
            while(qry.next())
            {
                ui->Periodee->addItem(qry.value(0).toString()+"->"+qry.value(1).toString() );

            }
            //mdconnection.closeconnection();
        }
        else {
            QMessageBox::critical(this,tr("error::"),qry.lastError().text());
        }
        qDebug() <<"ID is : \'"+idcatglobal+"\'";
    }

}

void Home::on_week_activated(int index)
{
   // if (ui->week->count()==1){
        ui->week->clear();
        QString periode=ui->Periodee->currentText();
        if (periode!=NULL) {
            //dbconnection dbv;
            if(!mdconnection.openDataBase()) {
                qDebug() <<"Failed to open databse";
                return;
            }
            mdconnection.openDataBase();
            QSqlQuery qry;
            QStringList list = periode.split("->");
            QString periodedebut=list[0];
            QString periodefin=list[1];
            int idPeriode = mdconnection.getPeriodeID(periodedebut, periodefin);
            QString s = QString::number(idPeriode);
            qry.prepare("SELECT sm.SemaineDebut, sm.SemaineFin FROM dbo.Semaine sm WHERE sm.idPeriode=\'"+ s + "\' ");


            if(qry.exec()) {
                while(qry.next())
                {
                    ui->week->addItem(qry.value(0).toString()+"->"+qry.value(1).toString() );

                }
                //mdconnection.closeconnection();
            }
            else {
                QMessageBox::critical(this,tr("error::"),qry.lastError().text());
            }
            qDebug() <<"ID is : \'"+idcatglobal+"\'";
        }

     //   }

}

void Home::on_day_activated(int index)
{
    if (ui->day->count()==1){
        ui->day->clear();
        if (ui->week->currentText()!=NULL) {
            //dbconnection dbv;
            if(!mdconnection.openDataBase()) {
                qDebug() <<"Failed to open databse";
                return;
            }
            mdconnection.openDataBase();
            QSqlQuery qry;
            qry.prepare("SELECT Jour FROM dbo.Jour ");


            if(qry.exec()) {
                while(qry.next())
                {
                    ui->day->addItem(qry.value(0).toString());

                }
                //mdconnection.closeconnection();
            }
            else {
                QMessageBox::critical(this,tr("error::"),qry.lastError().text());
            }
            qDebug() <<"ID is : \'"+idcatglobal+"\'";
        }
        }

}

void Home::on_refreshbutton_clicked()
{
    ui->category->clear();
    ui->Periodee->clear();
    ui->week->clear();
    ui->day->clear();
    ui->category->addItem(("------"));
    ui->Periodee->addItem(("------"));
    ui->week->addItem(("------"));
    ui->day->addItem(("------"));
}

void Home::on_pushButton_clicked()
{
    QString s = QDate::currentDate().toString();
    const QString format("<td>%1</td>");
        QString html;
        QAbstractItemModel *md = ui->tableView->model();
        html = "<html><head><style>.marginauto{  margin: 10px auto 20px; display: block; width:50%; } footer{color:black; font-family:verdana; margin-top:50%;} table, th, td{ border: 1px solid black; text-align:center;   font-size:18px; width:90%; white-space: nowrap; overflow: hidden; text-overflow:ellipsis;}    h1{text-align:center; }</style></head><body><div ><img src=\"D:/estlogo.png\" class=\"marginauto\"></div><br><br><br><br><header><h1>Fiche de Presence<\h1><\header><br><br><table  style=\"background-color:#00FF00\" class=\"tablesspace\">";

        html += "<td></td>";
        for(int column = 0; column < md->columnCount();
            column++) {
            QString data = md->headerData(column, Qt::Horizontal, Qt::DisplayRole).toString();
            html += format.arg(data);
        }
        for(int row = 0; row < md->rowCount() ; row++) {
            html += "<tr>";
            QString data = md->headerData(row, Qt::Vertical, Qt::DisplayRole).toString();
            html += format.arg(data);
            for(int column = 0; column < md->columnCount();
                column++) {
                QString data = md->index(row, column).data(Qt::DisplayRole).toString();
                html += format.arg(data);
            }
            html += "</tr>";
        }
        html += "</table></body><br><br><br><br><br><footer><p>Signature du responsable.......................Le.....\'"+ s +"\'......</p></footer></html>";

        QPrinter printer;
        QPrintDialog *dialog = new QPrintDialog(&printer);
        if(dialog->exec() == QDialog::Accepted) {
            QTextDocument document;
            document.setHtml(html);
            document.print(&printer);
        }
        QDate createdDate;
        createdDate=QDate::currentDate();
        QString DateONHistorique;
        DateONHistorique=createdDate.toString("dd/MM/yyyy");
        QTime times = QTime::currentTime();
        QString TimeHistorique;
        TimeHistorique = times.toString();
        mdconnection.AjoutSurHistorique("Un Fiche de presence a été imprimé ",DateONHistorique, TimeHistorique);
}

void Home::on_nextESTUI_clicked()
{
    ui->stackedWidget2->setCurrentIndex(1);
}

void Home::on_previousESTUI_clicked()
{
    ui->stackedWidget2->setCurrentIndex(0);
}

void Home::on_comboBox_activated(int index)
{
if(combobuzz==0){
    ui->comboBox->clear();
    if(!mdconnection.openDataBase()) {
        qDebug() <<"Failed to open databse";
        return;
    }
    mdconnection.openDataBase();
    QSqlQuery qry;
    qry.prepare("SELECT idCategorie, Categorie FROM dbo.Categorie");
    QString idcat = qry.value(0).toString();
    idcatAjoutPs=idcat;
    if(qry.exec()) {
        while(qry.next())
        {
            ui->comboBox->addItem(qry.value(1).toString() );

        }
    }
    else {
        QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    }
   }

    combobuzz++;
}

void Home::on_pushButton_6_clicked()
{

    QString nom = ui->nom->text();
    QString prenom = ui->prenom->text();
    QString tel = ui->tel->text();
    QString email = ui->email->text();
    QString cin = ui->cin->text();
    QString categorie = ui->category->currentText();
    mdconnection.ajouterPersonnel(cin, nom, prenom, tel, email, categorie);

    QDate createdDate;
    createdDate=QDate::currentDate();
    QString DateONHistorique;
    DateONHistorique=createdDate.toString("dd/MM/yyyy");
    QTime times = QTime::currentTime();
    QString TimeHistorique;
    TimeHistorique = times.toString();
    mdconnection.AjoutSurHistorique("Le personnel portant \'" +cin+ "\' a été ajouté ",DateONHistorique, TimeHistorique);

}

void Home::on_applicationip_clicked()
{
    QString path1 = QCoreApplication::applicationDirPath();
        QString  command1("python");
        QStringList params1 = QStringList() << "D:/stage/Projet_stage/DroidCam.py";

        QProcess *process1 = new QProcess();
        process1->startDetached(command1, params1, path1);
        process1->waitForFinished();
        process1->close();
}

void Home::on_cctvconnection_clicked()
{
    QString path1 = QCoreApplication::applicationDirPath();
        QString  command1("python");
        QStringList params1 = QStringList() << "D:/stage/Projet_stage/CCTV.py";

        QProcess *process1 = new QProcess();
        process1->startDetached(command1, params1, path1);
        process1->waitForFinished();
        process1->close();
}

void Home::on_refreshRecherche_clicked()
{
    //delete

}

void Home::on_pushButton_10_clicked()
{
    //ui->stackedWidgetCategorie->setCurrentIndex(0);
}


void Home::on_researchbtn_clicked()
{
    ui->rechtable->setVisible(true);
    ui->visualiser->setVisible(true);
    ui->modifier->setVisible(true);
    ui->supprimer->setVisible(true);
    QString value =ui->rechvalue->text();
   // QString cinR = ui->cinrecherche->text();
    if(!mdconnection.openDataBase()) {
        qDebug() <<"Failed to open databse";
        return;
    }
    mdconnection.openDataBase();
    QSqlQueryModel * modal = new QSqlQueryModel();
        modal->setQuery("SELECT CNI, Nom, Prenom, Email, Tel, Categorie FROM dbo.Personnel ps, dbo.Categorie cat WHERE cat.idCategorie=ps.idCategorie"
                        " and ps.CNI= \'" +value+ "\' or ps.Nom= \'" +value+ "\' or ps.Prenom= \'" +value+ "\' or ps.Email= \'" +value+ "\' or ps.Tel= \'" +value+ "\' or ps.Categorie= \'" +value+ "\' ");
        ui->rechtable->setModel(modal);



}

void Home::on_refreshrech_clicked(){
    ui->rechtable->setVisible(false);
    ui->visualiser->setVisible(false);
    ui->modifier->setVisible(false);
    ui->supprimer->setVisible(false);
}

void Home::on_fiche_presence_3_clicked()
{
     ui->espace_admin->setCurrentIndex(4);
}

void Home::on_visualiser_clicked()
{
    visualise = new Visualise();
    visualise->show();
    visualise->setCIN(selectedCIN);
}

void Home::on_rechtable_activated(const QModelIndex &index)
{
    QString val=ui->rechtable->model()->data(index).toString();
    //this val represent the selected collumn and selected row not always represente our cin

    //from that index i need to get the cin value
    //then putting it in selectefCIN
    //
    //i m trying to make those button clickable after selecting smth in the table
    ui->visualiser->setDisabled(false);
    ui->modifier->setDisabled(false);
    ui->supprimer->setDisabled(false);
    selectedCIN="cd1546";


}

void Home::on_modifier_clicked()
{
    modif = new Modifier();
    modif->show();
    modif->setCIN(selectedCIN);
}

void Home::on_supprimer_clicked()
{
    //calll the delete function to delete with cin

}


