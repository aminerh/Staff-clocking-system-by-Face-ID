#include "images.h"
#include "ui_images.h"
#include <QFileDialog>
#include <QMessageBox>

Images::Images(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Images)
{

    ui->setupUi(this);
}

Images::~Images()
{
    delete ui;
}

void Images::on_p1_clicked()
{
    QString file_name= QFileDialog::getOpenFileName(this,"Select picture");
   // QMessageBox::information(this,"..",file_name);
    image1;
    bool valid =image1.load(file_name);
    if(valid){
        image1=image1.scaledToWidth(ui->img1->width(),Qt::SmoothTransformation);
        ui->img1->setPixmap(QPixmap::fromImage(image1));
    }

}

void Images::on_p2_clicked()
{
    QString file_name= QFileDialog::getOpenFileName(this,"Select picture");
   // QMessageBox::information(this,"..",file_name);
    image2;
    bool valid =image2.load(file_name);
    if(valid){
        image2=image2.scaledToWidth(ui->img2->width(),Qt::SmoothTransformation);
        ui->img2->setPixmap(QPixmap::fromImage(image2));
    }
}

void Images::on_p3_clicked()
{
    QString file_name= QFileDialog::getOpenFileName(this,"Select picture");
   // QMessageBox::information(this,"..",file_name);
    image3;
    bool valid =image3.load(file_name);
    if(valid){
        image3=image3.scaledToWidth(ui->img3->width(),Qt::SmoothTransformation);
        ui->img3->setPixmap(QPixmap::fromImage(image3));
    }
}

void Images::on_p4_clicked()
{
    QString file_name= QFileDialog::getOpenFileName(this,"Select picture");
   // QMessageBox::information(this,"..",file_name);
    image4;
    bool valid =image4.load(file_name);
    if(valid){
        image4=image4.scaledToWidth(ui->img4->width(),Qt::SmoothTransformation);
        ui->img4->setPixmap(QPixmap::fromImage(image4));
    }
}

void Images::setfilename(QString name){
    filename=name;
}

void Images::on_confirm_clicked()
{
   if(!filename.isEmpty()){
    if(!image1.isNull()){
         bool v=image1.save("C:/Users/PC/Desktop/stage/images/"+filename+"/1.png");
    }
    if(!image2.isNull()){
         bool v=image2.save("C:/Users/PC/Desktop/stage/images/"+filename+"/2.png");
    }
    if(!image3.isNull()){
         bool v=image3.save("C:/Users/PC/Desktop/stage/images/"+filename+"/3.png");
    }
    if(!image4.isNull()){
         bool v=image4.save("C:/Users/PC/Desktop/stage/images/"+filename+"/4.png");
    }
   }
    Images::destroy();
}
