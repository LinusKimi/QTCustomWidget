#include "qloadanimation.h"

qloadanimation::qloadanimation(QWidget *parent)
    : QWidget{parent}
{
    this->setAttribute(Qt::WA_TranslucentBackground);
    itemCnt = 6;
}


void qloadanimation::setAngle(int angle){
    mangle = angle;
    update();
}

int qloadanimation::angle() {
    return mangle;
}

void qloadanimation::paintEvent(QPaintEvent *event){
    if(!this->isVisible())
        return;

    int width = this->width();
    int height = this->height();

    int dist = qMin(width, height);
    QRectF winrect(QPointF(0,0), QPointF(dist,dist));

    float maxDiameter = winrect.width() / 5;
    float minDiameter = maxDiameter / itemCnt;

    float rgap = (maxDiameter - minDiameter) / itemCnt / 2;
    float anglegap = (2 * M_PI / 4 * 3) / itemCnt;

    float half = winrect.width() / 2;
    float dotcenter = half - maxDiameter/2 -1;

    QPainter painter(this);
    painter.setPen(Qt::red);
    painter.setBrush(Qt::blue);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.save();
    painter.translate(winrect.center());
    painter.rotate(mangle);

    for(int i = 0; i < itemCnt; i++){
        painter.drawEllipse(QPointF(dotcenter*qCos(anglegap * i) ,
                                    -dotcenter*qSin(anglegap * i)),
                            maxDiameter / 2 - i * rgap,
                            maxDiameter / 2 - i * rgap
            );
    }
    // debug
    painter.drawLine(QPointF(0,0), QPointF(200,0));

    painter.restore();
}
