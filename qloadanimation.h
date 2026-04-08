#ifndef QLOADANIMATION_H
#define QLOADANIMATION_H

#include <QObject>
#include <QWidget>

#include <QPainter>
#include <QPoint>
#include <QColor>
#include <QTimer>
#include <QtMath>
#include <QList>
#include <QRect>

#include <QDebug>

// // // use
// QPropertyAnimation *animation = new QPropertyAnimation(ui->widget_4, "angle");
// // 3. 配置动画：时长、起始位置、结束位置
// animation->setDuration(1000);
// animation->setStartValue(0);
// animation->setEndValue(360);
// animation->setLoopCount(-1);
// // 4. 启动
// animation->start();

class qloadanimation : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int angle READ angle WRITE setAngle )
public:
    explicit qloadanimation(QWidget *parent = nullptr);

    void setAngle(int angle);
    int angle() ;

private:
    int mangle; // 旋转角度
    int itemCnt;

protected:
    void paintEvent(QPaintEvent *event);

signals:
};

#endif // QLOADANIMATION_H
