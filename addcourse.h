#ifndef ADDCOURSE_H
#define ADDCOURSE_H

#include <QDialog>

namespace Ui {
class addcourse;
}

class addcourse : public QDialog
{
    Q_OBJECT

public:
    explicit addcourse(QWidget *parent = nullptr);
    ~addcourse();

private slots:
    void on_done_clicked();

private:
    Ui::addcourse *ui;
};

#endif // ADDCOURSE_H
