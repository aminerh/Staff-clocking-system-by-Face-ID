#ifndef VISUALISE_H
#define VISUALISE_H

#include <QWidget>
#include "dbconnection.h"
#include <QImage>

namespace Ui {
class Visualise;
}

class Visualise : public QWidget
{
    Q_OBJECT

public:
    explicit Visualise(QWidget *parent = nullptr);
    void setCIN(QString name);
    ~Visualise();

private:
    Ui::Visualise *ui;
    dbconnection mdconnection;
     QImage imageresh;
     QString Cin;
};

#endif // VISUALISE_H
