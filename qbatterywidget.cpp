#include "qbatterywidget.h"
#include "QDebug"
qbatterywidget::qbatterywidget(QWidget *parent)
    : QWidget{parent}
{
    setAttribute(Qt::WA_TranslucentBackground);

    boardColor.setRgb(60,60,60);  // 灰色
    alarmColor.setRgb(255, 69, 58);
    littleColor.setRgb(255, 159, 10);
    normalColor.setRgb(48, 209, 88);
    setMinimumSize(50,25);
}


void qbatterywidget::paintEvent(QPaintEvent *) {
    if(!this->isVisible()){
        return;
    }

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    int w_width = this->width();
    int w_height = this->height();
    int w_margin = 3;

    int h_width = w_width / 16;
    int radius = 3;

    //绘制电池框体
    painter.setPen(QPen(boardColor, 2));
    painter.setBrush(Qt::NoBrush);

    QPointF b_topleft(w_margin, w_margin);
    QPointF b_bottomright(w_width - h_width - w_margin ,  w_height - 3);
    QRectF b_rect(b_topleft, b_bottomright);
    painter.drawRoundedRect(b_rect, radius, radius);

    // 绘制电池头
    painter.setPen(Qt::NoPen);
    painter.setBrush(boardColor);

    QPointF h_topleft(w_width - h_width - w_margin, w_height / 3);
    QPointF h_bottomright(w_width - w_margin, w_height - w_height / 3 );
    QRectF h_rect(h_topleft, h_bottomright);
    painter.drawRoundedRect(h_rect, radius, radius);


    // 绘制电池背景
    painter.setPen(Qt::NoPen);
    if(currentValue >= alarmValue)
        painter.setBrush(normalColor);
    else if(currentValue >= alarmValue / 2)
        painter.setBrush(littleColor);
    else
        painter.setBrush(alarmColor);

    double bg_unit = (b_rect.width() - w_margin * 2) / 100;
    double bg_width = bg_unit * (currentValue > 100 ? 100 : currentValue <= 1 ? 1 : currentValue);
    QPointF bg_topleft(b_rect.topLeft() + QPointF(w_margin, w_margin));
    QPointF bg_bottomright(b_rect.topLeft().x() + bg_width + w_margin, b_rect.bottomRight().y() - w_margin);
    if(bg_topleft.x() > bg_bottomright.x()) // 防止溢出
        bg_bottomright.setX(bg_topleft.x());
    QRectF bg_rect(bg_topleft, bg_bottomright);
    painter.drawRoundedRect(bg_rect, radius, radius);

    // // 绘制电池电量
    painter.setPen(QPen(Qt::black));
    QFont font = painter.font();
    font.setFamily("微软雅黑");
    font.setPixelSize(qMin(w_width, w_height) * 0.5);
    font.setBold(true);
    painter.setFont(font);
    painter.drawText(b_rect,Qt::AlignCenter,QString::number(currentValue));
}

void    qbatterywidget::setCurrentValue(int data){
    currentValue = data;
    update();
}
int     qbatterywidget::getCurrentValue(){
    return currentValue;
}

void    qbatterywidget::setAlarmValue(int data){
    alarmValue = data;
    update();
}

int     qbatterywidget::getAlarmValue(){
    return alarmValue;
}
