#ifndef IMAGES_H
#define IMAGES_H

#include <QWidget>

namespace Ui {
class Images;
}

class Images : public QWidget
{
    Q_OBJECT

public:
    explicit Images(QWidget *parent = nullptr);
    void setfilename(QString name);
    ~Images();

private slots:
    void on_p1_clicked();

    void on_p2_clicked();

    void on_p3_clicked();

    void on_p4_clicked();

    void on_confirm_clicked();



private:
    Ui::Images *ui;
    QString filename;
    QImage image1;
    QImage image2;
    QImage image3;
    QImage image4;
};

#endif // IMAGES_H
