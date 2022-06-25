#ifndef MODIFIER_H
#define MODIFIER_H

#include <QWidget>
#include "dbconnection.h"

namespace Ui {
class Modifier;
}

class Modifier : public QWidget
{
    Q_OBJECT

public:
    explicit Modifier(QWidget *parent = nullptr);
    void setCIN(QString name);
    ~Modifier();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Modifier *ui;
    dbconnection mdconnection;
    QString Cin;
};

#endif // MODIFIER_H
