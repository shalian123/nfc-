#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include<QPaintEvent>
#include<QPixmap>
#include<QPainter>
#include<QPoint>
#include<QMouseEvent>
#include <QHBoxLayout>
#include <QTableWidget>


struct MeasurePointInfo{
    QString orgseq;//装置序列
    QString pointpart;//测点部位
    QString equipname;//设备名称
    QString deviceid;//装置id
    double originthickness;//公称壁厚
    QString equipcode;//设备编号
    int equipid;//设备id
    QString parturl;//部位图url
    int id;  //测点id

};
struct MeasureRecordInfo{
    int pointid;//测点id
    double value;//测厚值
    QString checkdate;//测厚时间
};

class QFile;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void getMeasurePointInfo(QJsonObject data);                     //获取当日天气信息
    void getMeasureRecordInfo(QJsonObject data);


protected:
     void paintEvent(QPaintEvent *);
     void mouseMoveEvent(QMouseEvent *event);

private slots:
    void on_pushButton_clicked();
    void getReplyFinished(QNetworkReply *reply);//接受api发回来的jason天气数据
    void on_updateButton_clicked();
    void replyFinished(QNetworkReply* reply); //事件中提示用户上传完毕

    void OnUploadProgress(qint64 bytesSent,qint64 bytesTotal);//上传事件中更新进度条提示
    void updateDataReadProgress(qint64, qint64);
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Widget *ui;
   // QFile *qssFile;
    QNetworkAccessManager *manage;
    QNetworkAccessManager *manage1;
    QNetworkAccessManager *_uploadManager;//上传文件
    QNetworkReply *_reply; //上传
    QNetworkReply * reply;//下载
    char* m_buf;

    QPixmap pixmap;
    QPoint move_point;
    bool mouse_press;
    int uid;
    QTableWidget *tableWidget;//用于manage显示


};

#endif // WIDGET_H
