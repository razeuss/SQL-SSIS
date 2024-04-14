#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "adddialog.h"
#include "addcourse.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("localhost");
    database.setUserName("root");
    database.setPassword("");
    database.setDatabaseName("ssis");

    if(!database.open())
    {
        qDebug() << "Database connection error:" << database.lastError().text();
        qApp->quit();
    } else {
        ui->home->setStyleSheet("background-color: #e0e1dd; color: #1b263b");
        ui->home->setIcon(QIcon("C:/Users/jradl/Downloads/blue-home.png"));
        ui->home->setIconSize(QSize(20,20));
        ui->showprofile->hide();

        QSqlQueryModel *studid = new QSqlQueryModel(this);
        studid->setQuery("SELECT id FROM students");

        idcomp = new QCompleter(studid, this);
        idcomp->setCaseSensitivity(Qt::CaseInsensitive);
        ui->idnum->setCompleter(idcomp);

    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showstud()
{
    QSqlQueryModel *studid = new QSqlQueryModel(this);
    studid->setQuery("SELECT id FROM students");

    idcomp = new QCompleter(studid, this);
    idcomp->setCaseSensitivity(Qt::CaseInsensitive);
    ui->idsearch->setCompleter(idcomp);



    QSqlTableModel *model = new QSqlTableModel(this, database);
    model->setTable("students");
    model->select();

    model->setHeaderData(0, Qt::Horizontal, tr("NAME"));
    model->setHeaderData(1, Qt::Horizontal, tr("ID"));
    model->setHeaderData(2, Qt::Horizontal, tr("GENDER"));
    model->setHeaderData(3, Qt::Horizontal, tr("YEAR LEVEL"));
    model->setHeaderData(4, Qt::Horizontal, tr("COURSE CODE"));

    ui->studView->setModel(model);


    ui->studView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->studView->setSelectionMode(QAbstractItemView::NoSelection);
    ui->studView->setFocusPolicy(Qt::NoFocus);
    ui->studView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->studView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->studView->horizontalHeader()->setStyleSheet("font-weight: bold;");
    int lastColumnIndex = model->columnCount() - 1;
    ui->studView->hideColumn(lastColumnIndex);
}

void MainWindow::showcourses()
{
    QSqlQueryModel *courseModel = new QSqlQueryModel(this);
    courseModel->setQuery("SELECT coursename FROM course");

    courseCompleter = new QCompleter(courseModel, this);
    courseCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    ui->delprog->setCompleter(courseCompleter);




    QSqlTableModel *model = new QSqlTableModel(this, database);
    model->setTable("course");
    model->select();

    model->setHeaderData(0, Qt::Horizontal, tr("ACADEMIC PROGRAM"));
    model->setHeaderData(1, Qt::Horizontal, tr("CODE"));

    ui->courseview->setModel(model);

    ui->courseview->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->courseview->setSelectionMode(QAbstractItemView::NoSelection);
    ui->courseview->setFocusPolicy(Qt::NoFocus);
    ui->courseview->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->courseview->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->courseview->horizontalHeader()->setStyleSheet("font-weight: bold;");
    int lastColumnIndex = model->columnCount() - 1;
    ui->courseview->hideColumn(lastColumnIndex);
}


void MainWindow::on_home_clicked()
{
    if (ui->pages->currentIndex() != 0) {
        ui->home->setStyleSheet("background-color: #e0e1dd; color: #1b263b");
        ui->studmanage->setStyleSheet("background-color: transparent; color: #e0e1dd");
        ui->progmanage->setStyleSheet("background-color: transparent; color: #e0e1dd");
        ui->pages->setCurrentIndex(0);
        ui->showprofile->hide();

        QSqlQueryModel *studid = new QSqlQueryModel(this);
        studid->setQuery("SELECT id FROM students");

        idcomp = new QCompleter(studid, this);
        idcomp->setCaseSensitivity(Qt::CaseInsensitive);
        ui->idnum->setCompleter(idcomp);

        ui->home->setIcon(QIcon("C:/Users/jradl/Downloads/blue-home.png"));
        ui->home->setIconSize(QSize(20,20));

        ui->studmanage->setIcon(QIcon("C:/Users/jradl/Downloads/icons8-management-96 (3).png"));
        ui->studmanage->setIconSize(QSize(20,20));

        ui->progmanage->setIcon(QIcon("C:/Users/jradl/Downloads/icons8-requirements-96.png"));
        ui->progmanage->setIconSize(QSize(20,20));
    }
}


void MainWindow::on_studmanage_clicked()
{
    if (ui->pages->currentIndex() != 1) {
        ui->studmanage->setStyleSheet("background-color: #e0e1dd; color: #1b263b");
        ui->home->setStyleSheet("background-color: transparent; color: #e0e1dd");
        ui->progmanage->setStyleSheet("background-color: transparent; color: #e0e1dd");
        ui->pages->setCurrentIndex(1);

        showstud();

        ui->home->setIcon(QIcon("C:/Users/jradl/Downloads/icons8-home-96.png"));
        ui->home->setIconSize(QSize(20,20));

        ui->studmanage->setIcon(QIcon("C:/Users/jradl/Downloads/blue-studman.png"));
        ui->studmanage->setIconSize(QSize(20,20));

        ui->progmanage->setIcon(QIcon("C:/Users/jradl/Downloads/icons8-requirements-96.png"));
        ui->progmanage->setIconSize(QSize(20,20));
    }
}

void MainWindow::on_progmanage_clicked()
{
    if (ui->pages->currentIndex() != 2) {
        ui->progmanage->setStyleSheet("background-color: #e0e1dd; color: #1b263b");
        ui->home->setStyleSheet("background-color: transparent; color: #e0e1dd");
        ui->studmanage->setStyleSheet("background-color: transparent; color: #e0e1dd");
        ui->pages->setCurrentIndex(2);

        showcourses();

        ui->home->setIcon(QIcon("C:/Users/jradl/Downloads/icons8-home-96.png"));
        ui->home->setIconSize(QSize(20,20));

        ui->studmanage->setIcon(QIcon("C:/Users/jradl/Downloads/icons8-management-96 (3).png"));
        ui->studmanage->setIconSize(QSize(20,20));

        ui->progmanage->setIcon(QIcon("C:/Users/jradl/Downloads/blue-prog.png"));
        ui->progmanage->setIconSize(QSize(20,20));
    }
}

//HOME

void MainWindow::on_search_clicked()
{
    QString id = ui->idnum->text();

    if (id.isEmpty())
    {
        QMessageBox::information(this, " ", "Please type the student's id.");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT name, id, gender, yearlvl, code FROM students WHERE id = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next())
    {
        QString name = query.value(0).toString();
        QString studentId = query.value(1).toString();
        QString gender = query.value(2).toString();
        QString yearlvl = query.value(3).toString();
        QString code = query.value(4).toString();

        QSqlQuery qry;
        qry.prepare("SELECT coursename FROM course WHERE coursecode = :code");
        qry.bindValue(":code", code);

        if (qry.exec() && qry.next())
        {
            QString course = qry.value(0).toString();
            ui->course->setText(course);
        }

        ui->name->setText(name);
        ui->id->setText(studentId);
        ui->genderbox->setCurrentText(gender);
        ui->yearlvlbox->setCurrentText(yearlvl);
        ui->coursecode->setText(code);
        ui->showprofile->show();
        ui->idnum->clear();
    }
}


//STUDENT MANAGEMENT

void MainWindow::on_studreg_clicked()
{
    addDialog addform(this);
    addform.setModal(true);
    addform.exec();

    showstud();
}

void MainWindow::on_searchButt_clicked()
{
    QString searchid = ui->idsearch->text();

    if (searchid.isEmpty()) {
        QMessageBox::information(this, " ", "Please type the student's id.");
        return;
    } else {
    addDialog addform(searchid, this);
    addform.setModal(true);
    addform.exec();

    showstud();
    ui->idsearch->clear();
    }
}

//PROGRAM MANAGEMENT

void MainWindow::on_addprog_clicked()
{
    addcourse add(this);
    add.setModal(true);
    add.exec();

    showcourses();
}


void MainWindow::on_del_clicked()
{
    QString course = ui->delprog->text();

    QMessageBox::StandardButton confirmDelete;
    confirmDelete = QMessageBox::question(this, "Confirm Deletion", "Are you sure you want to delete this Academic Program?",
                                          QMessageBox::Yes | QMessageBox::No);
    if (confirmDelete == QMessageBox::Yes) {
    QSqlQuery deleteStudentsQuery;
    deleteStudentsQuery.prepare("DELETE FROM students WHERE code = (SELECT coursecode FROM course WHERE coursename = :course)");
    deleteStudentsQuery.bindValue(":course", course);

    QSqlQuery deleteCourseQuery;
    deleteCourseQuery.prepare("DELETE FROM course WHERE coursename = :course");
    deleteCourseQuery.bindValue(":course", course);

    if (deleteStudentsQuery.exec() && deleteCourseQuery.exec()) {
            QMessageBox::information(this, "Success", "Academic Program deleted.");
            showcourses();
            ui->delprog->clear();
    } else {
            QMessageBox::warning(this, "Error", "Failed to delete Academic Program.");
    }
    }
}

