#include "qwaterprogressbar.h"


qwaterprogressbar::qwaterprogressbar(QWidget *parent)
    : QWidget{parent}
{
    this->setAttribute(Qt::WA_TranslucentBackground);

    m_iTpye = true;   // true： 矩形   false: 椭圆、圆形
    m_iBorderWidth = 0;//边框厚度
    m_iValue = 90;//当前进度条进度
    m_dOffset = 0;//水波偏移量
    m_dStep = 0.15; // 自增步距离

    m_waterColor.setRgb(43, 123, 234);//水波颜色
    m_backgroundColor.setRgb(255, 255, 255);//背景颜色
    m_borderColor.setRgb(120, 120, 120);//边框颜色
    m_textColor.setRgb(0, 0, 0);//文本颜色

    m_timer = new QTimer(this);//控制水波移动的定时器
    m_timer->setSingleShot(false);

    connect(m_timer, &QTimer::timeout, this, [=](){
        if (this->isVisible())
        {
            //偏移量控制，每次绘制自加，当超过一个正弦余弦2π周期时，就回退为0，加上定时器每50ms绘制一下，就触发了曲线的动态效果
            m_dOffset +=m_dStep;
            if (m_dOffset > 2 * M_PI)
            {
                m_dOffset = 0;
            }
            this->update();
        }
    });
    m_timer->start(50);
}

qwaterprogressbar::~qwaterprogressbar()
{

}

void qwaterprogressbar::setProgressValue(int data){
    m_iValue = data;
    update();
}
int  qwaterprogressbar::getProgressValue(){
    return m_iValue;
}

void qwaterprogressbar::paintEvent(QPaintEvent *event)
{
    //进度条不可见的情况下就不重绘了
    if (!this->isVisible())
    {
        return;
    }
    m_iValue = this->m_iValue < 0 ? 0 : this->m_iValue > 100 ? 100 : this->m_iValue;//初始化时QT进度条的进度为-1，避免负进度的出现

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);//开启图和字体抗锯齿

    drawBackGround(&painter);//绘制背景
    drawWaterWave(&painter);//绘制水波
    drawText(&painter);//绘制进度文本
}

void qwaterprogressbar::drawBackGround(QPainter* painter)
{
    int width = this->width();
    int height = this->height();

    if (m_iBorderWidth > 0)
    {
        painter->save();
        painter->setBrush(QBrush(m_borderColor));
        painter->setPen(Qt::NoPen);
        //绘制边框背景，然后用内部背景覆盖，即可得到边框
        //根据窗口的长宽最小值得到外部背景直径
        if(m_iTpye == true){
            painter->drawRoundedRect(0,0, width, height,5,5);
        } else {
            painter->drawEllipse(0, 0, width, height);
        }
        painter->restore();
    }
    painter->save();

    painter->setBrush(QBrush(m_backgroundColor));
    painter->setPen(Qt::NoPen);
    //根据窗口的长宽最小值减去边框厚度得到内部背景直径
    if(m_iTpye == true){
        painter->drawRoundedRect(m_iBorderWidth, m_iBorderWidth, width - 2* m_iBorderWidth, height - 2*m_iBorderWidth, 5, 5);
    } else {
        painter->drawEllipse(m_iBorderWidth, m_iBorderWidth, width - 2 * m_iBorderWidth, height - 2 * m_iBorderWidth);
    }
    painter->restore();
}

void qwaterprogressbar::drawWaterWave(QPainter* painter)
{
    int width = this->width();
    int height = this->height();
    // //根据窗口的长宽最小值减去边框厚度得到直径
    // int diameter = qMin(width, height) - (2 * m_iBorderWidth);

    //sincos曲线的波峰，波峰越大，水浪越高
    double waveHeight = 0.04*height;
    //sincos曲线的周期，周期越大，水浪越密
    double cycle = 2 * M_PI / width * 1.5;
    //水的高度，可以理解为进度，注意由于我们的电脑坐标系是以左上角为原点，这和我们高中坐标系理解的不同
    double percent = (double)m_iValue / 100;
    double waterHeight = (1 - percent)*height + m_iBorderWidth;

    painter->save();
    QPainterPath totalPath;
    //加入路径
    if(m_iTpye == true)
        totalPath.addRoundedRect(m_iBorderWidth, m_iBorderWidth, width - 2* m_iBorderWidth, height - 2*m_iBorderWidth,5,5);
    else
        totalPath.addEllipse(m_iBorderWidth, m_iBorderWidth, width - 2* m_iBorderWidth, height - 2*m_iBorderWidth);

    //水波路径,先画浅色，再画深色
    QPainterPath water1;
    QPainterPath water2;

    water1.moveTo(0,  height);
    water2.moveTo(0,  height);

    //从左边起始点到右边结束点绘制两条波浪曲线
    for (int i = 0; i <=  width; i++)
    {
        double waterY1 = 0;
        double waterY2 = 0;

        if (m_iValue == 0 || m_iValue == 100)
        {
            waterY1 = waterY2 = waterHeight;
        }
        else
        {
            //第一条波浪Y轴
            waterY1 = (double)(waveHeight * qSin(cycle * i + m_dOffset - M_PI / 2)) + waterHeight;//当正弦曲线前进π/2，sin的波峰和cos的波谷就对上了
            //第二条波浪Y轴
            waterY2 = (double)(waveHeight * qCos(cycle * i + m_dOffset)) + waterHeight;
        }
        water1.lineTo(i, waterY1);
        water2.lineTo(i, waterY2);

    }

    //封闭
    water1.lineTo( width,  height);
    water2.lineTo( width,  height);

    water1.closeSubpath();
    water2.closeSubpath();

    QPainterPath path;
    QColor waterColor1 = m_waterColor;
    waterColor1.setAlpha(100);
    QColor waterColor2 = m_waterColor;
    waterColor2.setAlpha(200);

    //第一条波浪
    path = totalPath & water1; //totalPath.intersected(water1);
    painter->setBrush(waterColor1);
    painter->setPen(Qt::NoPen);
    painter->drawPath(path);
    painter->restore();
    painter->save();

    //第二条波浪挖去后的路径
    path = totalPath & water2; //totalPath.intersected(water2);
    painter->setBrush(waterColor2);
    painter->setPen(Qt::NoPen);
    painter->drawPath(path);

    painter->restore();
}

void qwaterprogressbar::drawText(QPainter* painter)
{
    painter->save();
    int width = this->width();
    int height = this->height();
    int fontSize = qMin(width, height) / 4;
    //设置文本字体
    QFont font;
    font.setFamily("微软雅黑");
    font.setPixelSize(fontSize);
    font.setBold(true);
    //绘制文本
    painter->setFont(font);
    painter->setPen(m_textColor);
    painter->drawText(QRectF(0, 0, width, height), Qt::AlignCenter, QString("%1%").arg(m_iValue));
    painter->restore();
}
