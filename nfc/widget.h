#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPixmap>
#include "clickedlabel.h"
#include "dialog_set.h"
#include "dialog_mea.h"
#include <QVector>
#include <QQueue>
#include <QList>
#include <QPainter>
#include <QPainterPath>
#include "paintline.h"
#include <QHBoxLayout>
#include <QTableWidget>

class QSqlTableModel;

namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
     QVector <QPushButton*> widgetvec;


private slots:

    void on_icn_mesure_pre_clicked();

    void on_menu_icn_set_pre_clicked();

    void on_icn_check_pre_clicked();

    void on_icn_mng_pre_clicked();

    void on_icn_syn_pre_clicked();

    void on_icn_help_pre_clicked();

    void on_radioButton_6_clicked();

    void on_checkBox_3_clicked();

    void on_radioButton_7_clicked();

   // void on_label_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();



    void on_pushButton_8_clicked();



    void on_radioButton_11_clicked();

    void on_radioButton_12_clicked();

    void on_radioButton_13_clicked();

    void on_radioButton_14_clicked();

    void on_radioButton_15_clicked();

    void on_radioButton_16_clicked();

    void timerUpdate();

    void on_pushButton_17_clicked();
protected slots:

    void on_pushButton_9_clicked();
    void on_textButton_clicked();//槽

    void SonWindowEventClicked() ;//响应子窗体信号的槽

private:

    Ui::Widget *ui;
    QPixmap pixmap;
   // ClickedLabel *clickLabel;
    Dialog_set dialog1;//新对话框
    Dialog_mea dialog2;
    QTimer *timer;//定时器

    int timer_count;//计数产生随机数的次数
    int point_id; //每个测点的id
    QString text1;//设备名称
    QString text2;//测量部位
    QString text3;//操作压力
    QString text4;//操作温度
    QString text5;//管内介质
    QString text6;//管道材料
    QString text7;//公称直径
    QString text8;//公称壁厚
    QString img_path;//图片路径

    QPushButton *textButton1;
    QPushButton *textButton2;
    QPushButton *textButton3 ;
    QPushButton *textButton4 ;
    QPushButton *textButton5 ;
    QPushButton *textButton6 ;
    QPushButton *textButton7 ;
    QPushButton *textButton8 ;

    //QQueue<QPushButton*>  widgetvec;
    //unsigned int t; /* 用来保存时间 */
    //int p; /* 用来调整坐标原点 */
   // QPainterPath *path;
   // QPainter *painter;
    PaintLine *pp;
    QHBoxLayout  *layout;

    QTableWidget *tableWidget;//用于manage显示

};

#endif // WIDGET_H
