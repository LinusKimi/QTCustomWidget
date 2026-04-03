#ifndef QWATERPROGRESSBAR_H
#define QWATERPROGRESSBAR_H

#include <QObject>
#include <QWidget>

#include <QTimer>
#include <QColor>
#include <QtMath>
#include <QPainter>
#include <QPainterPath>

class qwaterprogressbar : public QWidget
{
    Q_OBJECT
public:
    explicit qwaterprogressbar(QWidget *parent = nullptr);
    ~qwaterprogressbar();

protected:
    //页面重绘事件
    void paintEvent(QPaintEvent *event);
private:
    void drawBackGround(QPainter* painter);
    void drawWaterWave(QPainter* painter);
    void drawText(QPainter* painter);

private:
    int m_iBorderWidth;//边框厚度
    int m_iValue;//当前进度条进度
    double m_dOffset;//水波偏移量

    QColor m_waterColor;//水波颜色
    QColor m_backgroundColor;//背景颜色
    QColor m_borderColor;//边框颜色
    QColor m_textColor;//文本颜色
    QTimer *m_timer;//控制水波移动的定时器
};

#endif // QWATERPROGRESSBAR_H
