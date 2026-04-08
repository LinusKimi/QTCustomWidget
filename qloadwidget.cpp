#include "qloadwidget.h"

qloadwidget::qloadwidget(QWidget *parent)
    : QWidget{parent}
{
    this->setAttribute(Qt::WA_TranslucentBackground);
    dotPosList.clear();
    dotDiaList.clear();

    itemIndex = 0;
    dist = 100;
    itemCnt = 10;
    // 手动指定窗口大小(长宽相等 需要与实际一致)，计算点位，启动定时器
    itemMaxDiameter = dist / 5;
    itemMinDiameter = itemMaxDiameter / itemCnt;

    float half = dist / 2;
    float _centerDistance = half - itemMaxDiameter / 2 -1;

    float gap = (itemMaxDiameter - itemMinDiameter) / (itemCnt - 1) / 2;
    float angleGap = (2 * M_PI) / itemCnt;

    for(int i=0; i < itemCnt; i++){
        dotDiaList.append(itemMaxDiameter / 2 - i * gap);
        dotPosList.append(QPointF(half + _centerDistance*qCos(-angleGap * i),
                                  half - _centerDistance*qSin(-angleGap * i)) );
    }

    mtimer = new QTimer(this);
    connect(mtimer, &QTimer::timeout, [=](){
        itemIndex++;
        if(itemIndex >= itemCnt)
            itemIndex = 0;
        this->update();
    });
    mtimer->start(160);
}

void qloadwidget::paintEvent(QPaintEvent *event){
    if(!this->isVisible())
        return;

    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::blue);

    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);//开启图和字体抗锯齿

    for(int i = 0; i < itemCnt; i++){
        int idx = (itemCnt + itemIndex - i) % itemCnt;
        float r = dotDiaList.at(idx);
        painter.drawEllipse(dotPosList.at(i), r, r);
    }

}
