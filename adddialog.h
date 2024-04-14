#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSql>
#include <QCompleter>

namespace Ui {
class addDialog;
}

class addDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addDialog(QWidget *parent = nullptr);
    explicit addDialog(const QString &searchid, QWidget *parent = nullptr);
    ~addDialog();

public slots:
     void registerstud();

private slots:
    void addHide();
    void searchHide();
    void update();


    void on_done_clicked();

    void on_editbtn_clicked();

    void on_deletebutton_clicked();

private:
    Ui::addDialog *ui;
    QCompleter *courseCompleter;
    QString infostud(const QString &searchid);
    int val;

signals:
    void done();
};

#endif // ADDDIALOG_H
