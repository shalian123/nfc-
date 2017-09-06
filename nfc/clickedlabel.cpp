#include "clickedlabel.h"

ClickedLabel::ClickedLabel(QWidget *parent) :
    QLabel(parent)
{
}
void ClickedLabel::mouseReleaseEvent(QMouseEvent *)
{
    emit clicked(this); // 在点击事件中发送信号
}
