#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "home.h"
#include "QDate"
#include <QProcess>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    h=new Home(this);
    h->show();

}


void MainWindow::on_qrbutton_clicked()
{
    QString path1 = QCoreApplication::applicationDirPath();
        QString  command1("python");
        QStringList params1 = QStringList() << "D:/stage/Projet_stage/barcode_scanner_video.py";

        QProcess *process1 = new QProcess();
        process1->startDetached(command1, params1, path1);
        process1->waitForFinished();
        process1->close();
}
