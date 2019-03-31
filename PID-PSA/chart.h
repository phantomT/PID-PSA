#ifndef CHART_H
#define CHART_H

#include <QtCharts/QChart>
#include <QtCore/QTimer>
#include <QChartView>
#include <QXYSeries>
#include <QLineSeries>
#include <QPieSeries>
#include <QAbstractAxis>
#include <QValueAxis>

QT_CHARTS_BEGIN_NAMESPACE
class QSplineSeries;
class QValueAxis;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

//![1]
class Chart: public QChart
{
    Q_OBJECT
public:
    Chart(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = nullptr);
    virtual ~Chart();
    QTimer m_timer;

public slots:
    void handleTimeout();

private:
    QLineSeries *m_line;
    QSplineSeries *m_series;
    QStringList m_titles;
    QValueAxis *m_axisX;
    QValueAxis *m_axisY;
    qreal m_step;
    qreal m_x;
    qreal m_y;

};

//![1]
extern int pidtimer;
#endif // CHART_H
