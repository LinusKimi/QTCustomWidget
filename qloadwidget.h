#ifndef QLOADWIDGET_H
#define QLOADWIDGET_H

#include <QObject>
#include <QWidget>

#include <QPainter>
#include <QPoint>
#include <QColor>
#include <QTimer>
#include <QtMath>
#include <QList>

#include <QDebug>

class qloadwidget : public QWidget
{
    Q_OBJECT
public:
    explicit qloadwidget(QWidget *parent = nullptr);


protected:
    void paintEvent(QPaintEvent *event);

private:
    int dist;               // 长宽取小值
    int itemCnt;            // 点个数
    float itemMaxDiameter;  // 最大直径
    float itemMinDiameter;  // 最小直径

    int itemIndex;

    QTimer *mtimer;
    QList<QPointF> dotPosList;
    QList<float>   dotDiaList;
};

#endif // QLOADWIDGET_H
