#include "dialog_mea.h"
#include "ui_dialog_mea.h"
#include "paintline.h"
#include <QPainter>
#include <QPainterPath>
Dialog_mea::Dialog_mea(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_mea)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);//去掉窗体的标题栏

    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(Button_clicked()));
}


Dialog_mea::~Dialog_mea()
{
    delete ui;
}
//叉掉
void Dialog_mea::on_pushButton_clicked()
{
    this->close();
}
//取消
void Dialog_mea::on_pushButton_3_clicked()
{
    this->close();
}
//确定
void Dialog_mea::Button_clicked()
{
    emit Dialog_meaEvent();
    this->close();
}
