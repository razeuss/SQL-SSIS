#include "adddialog.h"
#include "ui_adddialog.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlTableModel>


addDialog::addDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addDialog)
{
    ui->setupUi(this);
    addHide();

    QSqlQueryModel *courseModel = new QSqlQueryModel(this);
    courseModel->setQuery("SELECT coursename FROM course");

    courseCompleter = new QCompleter(courseModel, this);
    courseCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    ui->course->setCompleter(courseCompleter);
}

void addDialog::addHide()
{
    ui->label->hide();
    ui->label_2->hide();
    ui->label_4->hide();
    ui->label_5->hide();
    ui->label_6->hide();

    ui->deletebutton->hide();
    ui->editbtn->hide();

    ui->yrlvlbox->setCurrentIndex(-1);
    ui->genderBox->setCurrentIndex(-1);

    val = 1;
}

void addDialog::registerstud()
{
    QString name = ui->name->text().toUpper();
    QString id = ui->idnum->text().toUpper();
    QString gender = ui->genderBox->currentText();
    QString yr = ui->yrlvlbox->currentText();
    QString courseName = ui->course->text().toUpper();

    QSqlQuery courseQuery;
    courseQuery.prepare("SELECT coursecode FROM course WHERE coursename = :course");
    courseQuery.bindValue(":course", courseName);

    if (!courseQuery.exec()) {
        QMessageBox::warning(this, "Error", "Failed to check course availability.");
        return;
    }

    if (!courseQuery.next()) {
        QMessageBox::warning(this, "Error", "Course not found. Cannot register.");
        return;
    }

    QString courseCode = courseQuery.value(0).toString();  // Retrieve course code from the query result

    QSqlQuery check;
    check.prepare("SELECT name, id FROM students WHERE name = :name AND id = :id");
    check.bindValue(":name", name);
    check.bindValue(":id", id);

    if (check.exec()) {
        if (check.next()) {
            QMessageBox::information(this, " ", "User already exists.");
            return;
        } else {
            QSqlQuery query;
            query.prepare("INSERT INTO students (name, id, gender, yearlvl, code) VALUES (:name, :id, :gender, :yearlevel, :code)");
            query.bindValue(":name", name);
            query.bindValue(":id", id);
            query.bindValue(":gender", gender);
            query.bindValue(":yearlevel", yr);
            query.bindValue(":code", courseCode);  // Use course code in the INSERT query

            if (query.exec()) {
                ui->name->setText("");
                ui->idnum->setText("");
                ui->course->setText("");
                ui->genderBox->setCurrentIndex(-1);
                ui->yrlvlbox->setCurrentIndex(-1);
                QMessageBox::information(this, " ", "Registered.");
            }
        }
    }
}

addDialog::addDialog(const QString &searchid, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addDialog)
{
    ui->setupUi(this);
    searchHide();

    infostud(searchid);
}

addDialog::~addDialog()
{
    delete ui;
}

void addDialog::searchHide()
{
    ui->done->hide();
    ui->name->setEnabled(false);
    ui->idnum->setEnabled(false);
    ui->yrlvlbox->setEnabled(false);
    ui->genderBox->setEnabled(false);
    ui->course->setEnabled(false);
    val = 0;

}

void addDialog::on_done_clicked()
{
    if (val == 0) {
        infostud(ui->idnum->text());
    } else if (val == 1) {
        registerstud();
        emit done();
    } else if (val == 3) {
        update();
    }
}

QString addDialog::infostud(const QString &searchid)
{
    QSqlQuery query;
    query.prepare("SELECT name, id, gender, yearlvl, code FROM students WHERE id = :id");
    query.bindValue(":id", searchid);

    if (query.exec() && query.next())
    {
        QString name = query.value(0).toString();
        QString id = query.value(1).toString();
        QString gender = query.value(2).toString();
        QString yearlvl = query.value(3).toString();
        QString code = query.value(4).toString();

        ui->name->setText(name);
        ui->idnum->setText(id);
        ui->genderBox->setCurrentText(gender);
        ui->yrlvlbox->setCurrentText(yearlvl);
        ui->course->setText(code);


        return id;
    }
    else
    {

        QMessageBox::warning(this, "Error", "Student ID not found.");
        return "";
    }
}

void addDialog::update()
{
    QString name = ui->name->text().toUpper();
    QString gender = ui->genderBox->currentText();
    QString yearlvl = ui->yrlvlbox->currentText();
    QString courseName = ui->course->text().toUpper();

    QSqlQuery courseQuery;
    courseQuery.prepare("SELECT coursecode FROM course WHERE coursename = :courseName");
    courseQuery.bindValue(":courseName", courseName);

    if (!courseQuery.exec() || !courseQuery.next()) {
        QMessageBox::warning(this, "Error", "Failed to retrieve course code.");
        return;
    }

    QString courseCode = courseQuery.value(0).toString();

    QString id = ui->idnum->text();

    QSqlQuery query;
    query.prepare("UPDATE students SET name = :name, gender = :gender, yearlvl = :year, code = :courseCode WHERE id = :idnum");
    query.bindValue(":name", name);
    query.bindValue(":gender", gender);
    query.bindValue(":year", yearlvl);
    query.bindValue(":courseCode", courseCode);
    query.bindValue(":idnum", id);

    if(query.exec()){
        QMessageBox::information(this, "Success", "Updated Successfully.");

        ui->name->clear();
        ui->idnum->clear();
        ui->genderBox->setCurrentIndex(0);
        ui->yrlvlbox->setCurrentIndex(0);
        ui->course->clear();
    }
    else {
        QMessageBox::warning(this, "Error", "Update failed.");
    }
}

void addDialog::on_editbtn_clicked()
{
    ui->done->show();
    ui->name->setEnabled(true);
    ui->yrlvlbox->setEnabled(true);
    ui->genderBox->setEnabled(true);
    ui->course->setEnabled(true);


    QString style = "border: 1px solid black; border-radius: 10px; background-color: white; padding-left: 10px; padding-right: 10px;";
    ui->name->setStyleSheet(style);
    ui->yrlvlbox->setStyleSheet(style);
    ui->genderBox->setStyleSheet(style);
    ui->course->setStyleSheet(style);

    QSqlQueryModel *courseModel = new QSqlQueryModel(this);
    courseModel->setQuery("SELECT coursename FROM course");

    courseCompleter = new QCompleter(courseModel, this);
    courseCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    ui->course->setCompleter(courseCompleter);

    val = 3;
}


void addDialog::on_deletebutton_clicked()
{
    QString id = ui->idnum->text();

    QSqlQuery query;
    query.prepare("DELETE FROM students WHERE id = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        QMessageBox::information(this, "Success", "Student record deleted.");

        ui->name->clear();
        ui->idnum->clear();
        ui->genderBox->setCurrentIndex(-1);
        ui->yrlvlbox->setCurrentIndex(-1);
        ui->course->clear();

    } else {
        QMessageBox::warning(this, "Error", "Failed to delete student record.");
    }
}

