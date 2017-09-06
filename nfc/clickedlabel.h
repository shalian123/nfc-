#ifndef CLICKEDLABEL_H
#define CLICKEDLABEL_H
#include <QWidget>
#include <QLabel>
#include <Qt>
//添加点击事件的Label

class ClickedLabel : public QLabel
{
    Q_OBJECT
public:
     ClickedLabel(QWidget *parent = 0);
     ~ClickedLabel() {}

signals:
     void clicked(ClickedLabel* click); // 点击信号

protected:
     void mouseReleaseEvent(QMouseEvent* ); // 重载了鼠标释放事件



};

#endif // CLICKEDLABEL_H
