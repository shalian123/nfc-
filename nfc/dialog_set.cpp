#include "dialog_set.h"
#include "ui_dialog_set.h"

Dialog_set::Dialog_set(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_set)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);//去掉窗体的标题栏
    //setAttribute(Qt::WA_TranslucentBackground);//背景透明

}

Dialog_set::~Dialog_set()
{
    delete ui;
}

void Dialog_set::on_pushButton_clicked()
{
    this->close();
}
