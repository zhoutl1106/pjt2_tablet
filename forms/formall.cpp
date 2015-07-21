#include "formall.h"
#include "ui_formall.h"
#include "../dialog.h"
#include "../widget.h"
#include <QVBoxLayout>

extern Dialog* g_dialog;
extern Widget* g_widget;
void beep(int length_us, int index = 0);
extern bool isBeep;
extern QString stylesheet;
void g_setValve();
void g_setVibrator();

FormAll::FormAll(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormAll)
{
    ui->setupUi(this);
    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),ui->lcdNumber,SLOT(display(int)));
    ui->horizontalSlider->setValue(0);
    for(int i = 0;i<2;i++)
    {
        lbtn[i] = new LongClickToolButton(NULL,i/2,i%2==0?1:-1,LongClickToolButton::horizontal);
        connect(lbtn[i],SIGNAL(longClick(int,int)),this,SLOT(lbtnValue(int,int)));
        connect(lbtn[i],SIGNAL(released(int,int)),this,SLOT(lbtnValue(int,int)));
        QVBoxLayout *layout = new QVBoxLayout;
        layout->setMargin(0);
        layout->addWidget(lbtn[i]);
        if(i == 1)
            ui->widget_left->setLayout(layout);
        else
            ui->widget_right->setLayout(layout);
    }
    longPressTimer = new QTimer();
    longPressTimer->setInterval(2500);
    connect(longPressTimer,SIGNAL(timeout()),this,SLOT(onLongPressTimer()));
}

FormAll::~FormAll()
{
    delete ui;
}

void FormAll::setValve(bool value)
{
    if(value)
    {
        ui->toolButtonValve->setStyleSheet("border-image: url(:/image/btnR.png); color: rgb(255, 255, 255);");
        ui->toolButtonValve->setText("喷阀 开");
    }
    else
    {
        ui->toolButtonValve->setStyleSheet("border-image: url(:/image/btnG.png); color: rgb(255, 255, 255);");
        ui->toolButtonValve->setText("喷阀 关");
    }
}

void FormAll::setVibrator(bool value)
{
    if(value)
    {
        ui->toolButtonVibrator->setStyleSheet("border-image: url(:/image/btnR.png); color: rgb(255, 255, 255);");
        ui->toolButtonVibrator->setText("供料 开");
    }
    else
    {
        ui->toolButtonVibrator->setStyleSheet("border-image: url(:/image/btnG.png); color: rgb(255, 255, 255);");
        ui->toolButtonVibrator->setText("供料 关");
    }
}

void FormAll::lbtnValue(int index, int value)
{
    ui->horizontalSlider->setValue(ui->horizontalSlider->value()+value);
}

void FormAll::on_toolButtonOK_clicked()
{
    QByteArray cmd;
    cmd.append(char(0x0d));
    cmd.append(char(ui->horizontalSlider->value()));
    g_dialog->cmdSocket->writeDatagram(cmd,QHostAddress(g_widget->getTarget()),UDP_CMD_WRITE_PORT);
}

void FormAll::on_toolButtonValve_clicked()
{
    g_setValve();
}

void FormAll::on_toolButtonVibrator_clicked()
{
    g_setVibrator();
}

void FormAll::on_toolButtonExit_pressed()
{
    longPressTimer->start();
}

void FormAll::on_toolButtonExit_released()
{
    longPressTimer->stop();
}

void FormAll::onLongPressTimer()
{
    longPressTimer->stop();
    //*** ask whether to save the parameters

    DialogAutoCloseMessageBox box1(NULL,"关机","是否关机","是","否",10,true);
    if(box1.exec() == QDialog::Accepted)
    {
        QByteArray cmd;
        cmd.append(char(0x07));
        cmd.append(char(0x00));
        g_dialog->cmdSocket->writeDatagram(cmd,QHostAddress(g_widget->getTarget()),UDP_CMD_WRITE_PORT);
        memset(g_widget->versions,0,12*2*sizeof(int));
        g_widget->updateDisplay();
        g_dialog->setModeAndMem(0,0);
    }
}
