#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QSqlDatabase>
#include <QtSql>
#include <QCompleter>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_home_clicked();
    void on_studmanage_clicked();
    void on_progmanage_clicked();
    void on_search_clicked();
    void on_studreg_clicked();
    void on_searchButt_clicked();

    void on_addprog_clicked();
    void showstud();
    void showcourses();

    void on_del_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase database;
    QCompleter *idcomp;
    QCompleter *courseCompleter;
};
#endif // MAINWINDOW_H
