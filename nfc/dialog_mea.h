#ifndef DIALOG_MEA_H
#define DIALOG_MEA_H

#include <QDialog>
#include <paintline.h>
#include <QHBoxLayout>
#include <QPainter>
#include <QPainterPath>

namespace Ui {
class Dialog_mea;
}

class Dialog_mea : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_mea(QWidget *parent = 0);
    ~Dialog_mea();
signals:

    void Dialog_meaEvent();

protected slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void Button_clicked();

private:
    Ui::Dialog_mea *ui;
   // PaintLine *line;
   // QHBoxLayout  *layout_1;
};

#endif // DIALOG_MEA_H
