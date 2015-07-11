#include "formaccuracyadjust.h"
#include "ui_formaccuracyadjust.h"
#include <QDebug>
#include "../dialog.h"
#include <QVBoxLayout>

void beep(int length_us, int index = 0);
extern bool isBeep;
extern QString stylesheet;
extern Dialog* g_dialog;


FormAccuracyAdjust::FormAccuracyAdjust(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormAccuracyAdjust)
{
    ui->setupUi(this);
    setStyleSheet(stylesheet);
    connect(ui->verticalSlider11,SIGNAL(valueChanged(int)),ui->lcdNumber11,SLOT(display(int)));
    connect(ui->verticalSlider12,SIGNAL(valueChanged(int)),ui->lcdNumber12,SLOT(display(int)));
    connect(ui->verticalSlider13,SIGNAL(valueChanged(int)),ui->lcdNumber13,SLOT(display(int)));
    connect(ui->verticalSlider21,SIGNAL(valueChanged(int)),ui->lcdNumber21,SLOT(display(int)));
    connect(ui->verticalSlider22,SIGNAL(valueChanged(int)),ui->lcdNumber22,SLOT(display(int)));
    connect(ui->verticalSlider23,SIGNAL(valueChanged(int)),ui->lcdNumber23,SLOT(display(int)));
    connect(ui->verticalSlider31,SIGNAL(valueChanged(int)),ui->lcdNumber31,SLOT(display(int)));
    connect(ui->verticalSlider32,SIGNAL(valueChanged(int)),ui->lcdNumber32,SLOT(display(int)));
    connect(ui->verticalSlider33,SIGNAL(valueChanged(int)),ui->lcdNumber33,SLOT(display(int)));
    ui->verticalSlider11->setValue(0);
    ui->verticalSlider12->setValue(0);
    ui->verticalSlider13->setValue(0);
    ui->verticalSlider21->setValue(0);
    ui->verticalSlider22->setValue(0);
    ui->verticalSlider23->setValue(0);
    ui->verticalSlider31->setValue(0);
    ui->verticalSlider32->setValue(0);
    ui->verticalSlider33->setValue(0);
    listSlider.append(ui->verticalSlider11);
    listSlider.append(ui->verticalSlider12);
    listSlider.append(ui->verticalSlider13);
    listSlider.append(ui->verticalSlider21);
    listSlider.append(ui->verticalSlider22);
    listSlider.append(ui->verticalSlider23);
    listSlider.append(ui->verticalSlider31);
    listSlider.append(ui->verticalSlider32);
    listSlider.append(ui->verticalSlider33);

    listWidget.append(ui->widget_11u);
    listWidget.append(ui->widget_11d);
    listWidget.append(ui->widget_12u);
    listWidget.append(ui->widget_12d);
    listWidget.append(ui->widget_13u);
    listWidget.append(ui->widget_13d);
    listWidget.append(ui->widget_21u);
    listWidget.append(ui->widget_21d);
    listWidget.append(ui->widget_22u);
    listWidget.append(ui->widget_22d);
    listWidget.append(ui->widget_23u);
    listWidget.append(ui->widget_23d);
    listWidget.append(ui->widget_31u);
    listWidget.append(ui->widget_31d);
    listWidget.append(ui->widget_32u);
    listWidget.append(ui->widget_32d);
    listWidget.append(ui->widget_33u);
    listWidget.append(ui->widget_33d);

    btn = new MultiStatusToolButton(NULL,2,"前相机","font-size:20px;border-image: url(:/image/btnR.png);color: rgb(255, 255, 255);"
                                    ,"后相机","font-size:20px;border-image: url(:/image/btnG.png);color: rgb(255, 255, 255);");

    connect(btn,SIGNAL(clicked()),this,SLOT(onCameraClicked()));
    QVBoxLayout *box = new QVBoxLayout;
    box->setMargin(0);
    box->addWidget(btn);
    ui->widget->setLayout(box);

    for(int i = 0;i<18;i++)
    {
        lbtn[i] = new LongClickToolButton(NULL,i/2,i%2==0?1:-1,LongClickToolButton::vertical);
        connect(lbtn[i],SIGNAL(longClick(int,int)),this,SLOT(lbtnValue(int,int)));
        connect(lbtn[i],SIGNAL(released(int,int)),this,SLOT(lbtnValue(int,int)));
        QVBoxLayout *layout = new QVBoxLayout;
        layout->setMargin(0);
        layout->addWidget(lbtn[i]);
        listWidget.at(i)->setLayout(layout);
    }
}


FormAccuracyAdjust::~FormAccuracyAdjust()
{
    delete ui;
}

void FormAccuracyAdjust::lbtnValue(int index, int value)
{
    listSlider.at(index)->setValue(listSlider.at(index)->value()+value);
}

void FormAccuracyAdjust::on_toolButton_clicked()
{
    if(isBeep)beep(50000,0);
    emit switchToPage(0);
}

void FormAccuracyAdjust::onCameraClicked()
{
    if(isBeep)beep(50000,1);
}

void FormAccuracyAdjust::checkDataRange(int &v, int min, int max)
{
    if(v > max)v = max;
    if(v < min)v = min;
}

void FormAccuracyAdjust::on_toolButton_2_clicked()
{
    for(int i = 0 + btn->currentIndex() * 7; i < 7 + btn->currentIndex() * 7;i++)
    {
        if(g_dialog->fileManager->config.times[i] == 1)
        {
            g_dialog->fileManager->config.accuracy[i][0] += ui->verticalSlider11->value();
            checkDataRange(g_dialog->fileManager->config.accuracy[i][0],0,255);
            g_dialog->fileManager->config.accuracy[i][1] += ui->verticalSlider12->value();
            checkDataRange(g_dialog->fileManager->config.accuracy[i][1],0,255);
            g_dialog->fileManager->config.accuracy[i][2] += ui->verticalSlider13->value();
            checkDataRange(g_dialog->fileManager->config.accuracy[i][2],1,15);
        }
        if(g_dialog->fileManager->config.times[i] == 2)
        {
            g_dialog->fileManager->config.accuracy[i][0] += ui->verticalSlider21->value();
            checkDataRange(g_dialog->fileManager->config.accuracy[i][0],0,255);
            g_dialog->fileManager->config.accuracy[i][1] += ui->verticalSlider22->value();
            checkDataRange(g_dialog->fileManager->config.accuracy[i][1],0,255);
            g_dialog->fileManager->config.accuracy[i][2] += ui->verticalSlider23->value();
            checkDataRange(g_dialog->fileManager->config.accuracy[i][2],1,15);
        }
        if(g_dialog->fileManager->config.times[i] == 3)
        {
            g_dialog->fileManager->config.accuracy[i][0] += ui->verticalSlider31->value();
            checkDataRange(g_dialog->fileManager->config.accuracy[i][0],0,255);
            g_dialog->fileManager->config.accuracy[i][1] += ui->verticalSlider32->value();
            checkDataRange(g_dialog->fileManager->config.accuracy[i][1],0,255);
            g_dialog->fileManager->config.accuracy[i][2] += ui->verticalSlider33->value();
            checkDataRange(g_dialog->fileManager->config.accuracy[i][2],1,15);
        }
    }
    ui->verticalSlider11->setValue(0);
    ui->verticalSlider12->setValue(0);
    ui->verticalSlider13->setValue(0);
    ui->verticalSlider21->setValue(0);
    ui->verticalSlider22->setValue(0);
    ui->verticalSlider23->setValue(0);
    ui->verticalSlider31->setValue(0);
    ui->verticalSlider32->setValue(0);
    ui->verticalSlider33->setValue(0);
    g_dialog->fileManager->configChange();
    /*for(int i = 0;i<14;i++)
    {
        qDebug()<<i<<g_dialog->fileManager->config.times[i]
                  <<g_dialog->fileManager->config.accuracy[i][0]
                 <<g_dialog->fileManager->config.accuracy[i][1]
                <<g_dialog->fileManager->config.accuracy[i][2];
    }*/
    char tmp[6] = {0x02,0};
    QByteArray temp = QByteArray(tmp,6);
    char *p = temp.data();
    for(int i = 0;i<7;i++)
    {
        p[1] = btn->currentIndex()*7 + i + 1;
        p[2] = g_dialog->fileManager->config.accuracy[btn->currentIndex()*7 +i][0];
        p[3] = g_dialog->fileManager->config.accuracy[btn->currentIndex()*7 +i][1];
        p[4] = g_dialog->fileManager->config.accuracy[btn->currentIndex()*7 +i][2];
        g_dialog->writeUdpCmd(1,temp);
    }
    g_dialog->fileManager->writeConfig(g_dialog->fileManager->mode,g_dialog->fileManager->mem);
}
