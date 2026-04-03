#ifndef QBATTERYWIDGET_H
#define QBATTERYWIDGET_H

#include <QObject>
#include <QWidget>

#include <QPainter>
#include <QPoint>
#include <QColor>

class qbatterywidget : public QWidget
{
    Q_OBJECT
public:
    explicit qbatterywidget(QWidget *parent = nullptr);

    void    setCurrentValue(int);
    int     getCurrentValue();

    void    setAlarmValue(int);
    int     getAlarmValue();

private:
    int currentValue = 0;
    int alarmValue = 20;

    QColor alarmColor, littleColor, normalColor, boardColor;


protected:
    void paintEvent(QPaintEvent *) override ;

signals:
};

#endif // QBATTERYWIDGET_H
