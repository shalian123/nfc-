#ifndef PAINTLINE_H
#define PAINTLINE_H

#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QTimer>
class PaintLine : public QWidget
{
    Q_OBJECT
public:
    explicit PaintLine(QWidget *parent = 0);
    QPoint Point;   /* 线条绘制点的坐标 */
    void paintEvent(QPaintEvent *); /* 重绘事件函数 */
    QTimer *timer;
signals:

private slots:
    void timerUpDate();     /* 定时器槽函数 */
private:
    unsigned int t; /* 用来保存时间 */
    int p; /* 用来调整坐标原点 */
    QPainterPath *path;

};

#endif // PAINTLINE_H
