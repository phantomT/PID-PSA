#include "chart.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAbstractAxis>
#include <QSplineSeries>
#include <QValueAxis>
#include <QRandomGenerator>
#include <QRandomGenerator64>
#include <QtCore/QDebug>

Chart::Chart(QGraphicsItem *parent, Qt::WindowFlags wFlags):
    QChart (QChart::ChartTypeCartesian,parent,wFlags),
    m_series(nullptr),
    m_axisX(new QValueAxis()),
    m_axisY(new QValueAxis()),
    m_step(0),
    m_x(40),
    m_y(0)
{
    QObject::connect(&m_timer,&QTimer::timeout,this,&Chart::handleTimeout);
    //m_timer.setInterval(500);
    m_timer.setInterval(pidtimer);

    m_series = new QSplineSeries(this);
    QPen green(Qt::red);
    green.setWidth(3);
    m_series->setPen(green);
    m_series->append(m_x,m_y);

    addSeries(m_series);
    m_series->setUseOpenGL(true);
    //QDebug()<<m_series->useOpenGL();

    addAxis(m_axisX,Qt::AlignBottom);
    addAxis(m_axisY,Qt::AlignLeft);
    m_series->attachAxis(m_axisX);
    m_series->attachAxis(m_axisY);
    m_axisX->setTickCount(20);
    m_axisY->setTickCount(15);
    m_axisX->setRange(0,40);
    m_axisY->setRange(-5,10);

    m_timer.start();
}

Chart::~Chart()
{

}

void Chart::handleTimeout()
{
    qreal x = plotArea().width() / m_axisX->tickCount();
    qreal y = (m_axisX->max() - m_axisX->min()) / m_axisX->tickCount();
    m_x += y;
    m_y = sin(m_x);
    m_series->append(m_x,m_y);
    scroll(x,0);
    //if(m_x == 100)
    //    m_timer.stop();
}
