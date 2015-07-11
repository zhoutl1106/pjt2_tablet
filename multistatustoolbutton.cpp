#include "multistatustoolbutton.h"
#include <QDebug>

MultiStatusToolButton::MultiStatusToolButton(QWidget *parent, int statusCnt, ...)
    : QToolButton(parent)
{
    m_index = 0;
    connect(this,SIGNAL(clicked()),this,SLOT(onclick()));
    va_list args;
    va_start(args,statusCnt);
    bool temp = true;
    statusCnt += statusCnt;
    while(statusCnt>0)
    {
        if(temp)
            textList.append(QString(va_arg(args,char*)));
        else
            styleSheetList.append(QString(va_arg(args,char*)));
        temp = !temp;
        statusCnt--;
    }
    va_end(args);
    /*for(int i = 0;i<textList.length();i++)
        qDebug()<<textList.at(i);*/
    setText(textList.at(0));
    setStyleSheet(styleSheetList.at(0));
    setSizePolicy(QSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred));
}

MultiStatusToolButton::~MultiStatusToolButton()
{

}

void MultiStatusToolButton::onclick()
{
    //qDebug()<<"click";
    m_index ++;
    if(m_index >= textList.length())
        m_index = 0;
    setText(textList.at(m_index));
    setStyleSheet(styleSheetList.at(m_index));
}

int MultiStatusToolButton::currentIndex()
{
    return m_index;
}

void MultiStatusToolButton::setCurrentIndex(int v)
{
    m_index = v;
    if(m_index >= textList.length() || m_index < 0)
        m_index = 0;
    setText(textList.at(m_index));
    setStyleSheet(styleSheetList.at(m_index));
}
