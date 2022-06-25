#ifndef HOME_H
#define HOME_H

#include <QSqlDatabase>
#include <QTableView>
#include <QWidget>
#include <QImage>
#include "images.h"
#include "dbconnection.h"
#include "visualise.h"
#include "modifier.h"

namespace Ui {
class Home;
}

class Home : public QWidget
{
    Q_OBJECT

public:
    explicit Home(QWidget *parent = nullptr);
    bool openDataBase(QString *error = nullptr);
    void loadComboCategorie();
    void loadComboPeriode();
    void loadComboSemaine();
    void loadComboJour();
    QSqlDatabase MyDB;
    QString idcatAjoutPs;
    bool flagofliberty=true;
    int combobuzz = 0;
    Home();
    ~Home();

private slots:


    void on_nav2_clicked();

    void on_nav1_clicked();

    void on_nav3_clicked();

    void on_nav4_clicked();

    void on_nav5_clicked();

    void on_nav6_clicked();

    void on_add_pers_clicked();


    void on_add_cat_clicked();

    void on_historique_clicked();

    void on_fiche_presence_2_clicked();

    void on_logo_clicked();

    void on_fiche_presence_clicked();


    
    void on_pushButton_3_clicked();

    void on_Add_pics_clicked();

    void on_pushButton_2_clicked();


    void on_category_activated(int index);


    void on_Periodee_activated(int index);

    void on_week_activated(int index);

    void on_day_activated(int index);

    void on_refreshbutton_clicked();

    void on_pushButton_clicked();



    //void on_pushButton_5_clicked();

    void on_nextESTUI_clicked();

    void on_previousESTUI_clicked();

    void on_comboBox_activated(int index);


    void on_pushButton_6_clicked();

    void on_applicationip_clicked();



    void on_cctvconnection_clicked();

    void on_refreshRecherche_clicked();

    void on_pushButton_10_clicked();

    //void on_pushButton_4_clicked();

    void on_researchbtn_clicked();

    void on_refreshrech_clicked();

    void on_fiche_presence_3_clicked();

    void on_visualiser_clicked();

    void on_rechtable_activated(const QModelIndex &index);

    void on_modifier_clicked();

    void on_supprimer_clicked();



private:
    Ui::Home *ui;
    Images *pics;
    Visualise *visualise;
    Modifier *modif;
    dbconnection mdconnection;
    QString selectedCIN;

};

#endif // HOME_H
