#ifndef DIALOG_SET_H
#define DIALOG_SET_H

#include <QDialog>

namespace Ui {
class Dialog_set;
}

class Dialog_set : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_set(QWidget *parent = 0);
    ~Dialog_set();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog_set *ui;
};

#endif // DIALOG_SET_H
