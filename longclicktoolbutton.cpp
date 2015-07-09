#include "longclicktoolbutton.h"
#include <QDebug>

LongClickToolButton::LongClickToolButton(QWidget *parent, int index, int delta):QToolButton(parent)
{
    m_index = index;
    m_delta = delta;
    if(delta > 0)
        setStyleSheet("QToolButton {border-image : url(:/image/upG.png);} QToolButton::pressed {border-image : url(:/image/upR.png);}");
    else
        setStyleSheet("QToolButton {border-image : url(:/image/downG.png);} QToolButton::pressed {border-image : url(:/image/downR.png);}");
    connect(this,SIGNAL(clicked()),this,SLOT(onclick()));
    connect(this,SIGNAL(pressed()),this,SLOT(pressed()));
    connect(this,SIGNAL(released()),this,SLOT(released()));
    timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(onTimer()));
    setSizePolicy(QSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred));
}

LongClickToolButton::~LongClickToolButton()
{

}

void LongClickToolButton::paintEvent(QPaintEvent *p)
{
    QToolButton::paintEvent(p);
}

void LongClickToolButton::pressed()
{
    //qDebug()<<"press";
    timer->setInterval(300);
    timer->start();
}

void LongClickToolButton::released()
{
    //qDebug()<<"release";
    timer->stop();
    emit released(m_index,m_delta);
}

void LongClickToolButton::onclick()
{
    //qDebug()<<"click";
}

void LongClickToolButton::onTimer()
{
    timer->setInterval(100);
    emit longClick(m_index,m_delta);
}
