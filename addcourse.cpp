#include "addcourse.h"
#include "ui_addcourse.h"
#include <QtSql>
#include <QMessageBox>

addcourse::addcourse(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addcourse)
{
    ui->setupUi(this);
}

addcourse::~addcourse()
{
    delete ui;
}

void addcourse::on_done_clicked()
{
    QString code = ui->coursecode->text().toUpper();
    QString coursename = ui->coursename->text().toUpper();
    QString type = ui->options->currentText().toUpper();
    QString degree;

    if (type == "BS" || type == "BA")
    {
     degree = type + " IN " + coursename;
    } else {
     degree = type + " OF " + coursename;
    }

    QSqlQuery check;
    check.prepare("SELECT coursename FROM course WHERE coursename =:degree");
    check.bindValue(":degree",degree);

    if (check.exec())
    {
     if(check.next())
     {
         QMessageBox::information(this, " ", "Program already exists.");
         ui->coursecode->clear();
         ui->options->setCurrentIndex(-1);
         ui->coursename->clear();
         return;
     } else {
         QSqlQuery query;
         query.prepare("INSERT INTO course (coursename, coursecode) VALUES (:coursename, :code)");
         query.bindValue(":coursename", degree);
         query.bindValue(":code", code);

         if (query.exec()) {
             QMessageBox::information(this, " ", "Added Successfully.");
             ui->coursecode->clear();
             ui->options->setCurrentIndex(-1);
             ui->coursename->clear();
         }
     }

    }
}

