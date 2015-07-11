#include "formmain.h"
#include "ui_formmain.h"
#include "../dialog.h"
#include "../widget.h"
#include <QDebug>
#include "../dialogautoclosemessagebox.h"

extern bool isBeep;
void beep(int length_us, int index = 0);
void g_setValve();
void g_setVibrator();
extern Dialog* g_dialog;
extern Widget* g_widget;
void Sleep(int);

FormMain::FormMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormMain)
{
    ui->setupUi(this);
    longPressTimer = new QTimer();
    longPressTimer->setInterval(2500);
    connect(longPressTimer,SIGNAL(timeout()),this,SLOT(onLongPressTimer()));
}

FormMain::~FormMain()
{
    delete ui;
}

void FormMain::showEvent(QShowEvent *e)
{
    qDebug()<<"main show";
    //isBeep = true;
}

void FormMain::setValve(bool value)
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

void FormMain::setVibrator(bool value)
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

void FormMain::on_toolButtonExit_pressed()
{
    longPressTimer->start();
}

void FormMain::on_toolButtonExit_released()
{
    longPressTimer->stop();
}

void FormMain::closeAllDevices()
{
//    //*** send cmd to close all devices
//    char tmp[3] = {0x02,0x00};
//    QByteArray tmp1(tmp,3);
//    g_dialog->serialManager->writeCmd(0,tmp1);
//    tmp1.data()[0] = 0x04;
//    g_dialog->serialManager->writeCmd(0,tmp1);
//    tmp1.data()[0] = 0x06;
//    g_dialog->serialManager->writeCmd(0,tmp1);
//    tmp1.data()[0] = 0x08;
//    g_dialog->serialManager->writeCmd(0,tmp1);
//    tmp1.data()[0] = 0x0a;
//    g_dialog->serialManager->writeCmd(0,tmp1);
//    tmp1.data()[0] = 0x0c;
//    g_dialog->serialManager->writeCmd(0,tmp1);
//    tmp1.data()[0] = 0x0e;
//    g_dialog->serialManager->writeCmd(0,tmp1);
//    tmp1.data()[0] = 0x12;
//    g_dialog->serialManager->writeCmd(0,tmp1);

//    char tmp2[6]={0x07,0xaa,0x00};
//    g_dialog->serialManager->writeCmd(1,QByteArray(tmp2,6));
}

void FormMain::onLongPressTimer()
{
    longPressTimer->stop();
    //*** ask whether to save the parameters
    if(isBeep)beep(50000,24);

    DialogAutoCloseMessageBox box1(NULL,"关机","是否关机","是","否",10,true);
    if(box1.exec() == QDialog::Accepted)
    {
        //closeAllDevices();

        DialogAutoCloseMessageBox box(NULL,"保存","是否保存模式参数","是","否",10,true);
        if(box.exec() == QDialog::Accepted)
        {
           g_dialog->fileManager->writeConfig(g_dialog->fileManager->mode,g_dialog->fileManager->mem);
        }
        Sleep(1000);
        QByteArray cmd;
        cmd.append(char(0x07));
        cmd.append(char(0x00));
        g_dialog->cmdSocket->writeDatagram(cmd,QHostAddress(g_widget->getTarget()),UDP_CMD_WRITE_PORT);
        int id = g_widget->getTarget().right(3).toInt()-100;
        g_widget->versions[id-1][0] = g_widget->versions[id-1][1] = 0;
        qDebug()<<id<<"is set to 0";
        g_widget->updateDisplay();
        g_dialog->setModeAndMem(0,0);
    }
}

void FormMain::on_toolButton_5_clicked()
{
    //if(isBeep)beep(50000,25);
    emit switchToPage(1);
}

void FormMain::on_toolButton_6_clicked()
{
    //if(isBeep)beep(50000,26);
    emit switchToPage(2);
}

void FormMain::on_toolButton_8_clicked()
{
    //if(isBeep)beep(50000,27);
    emit switchToPage(3);
}

void FormMain::on_toolButtonValve_clicked()
{
    //if(isBeep)beep(50000,28);
    g_setValve();
}

void FormMain::on_toolButtonVibrator_clicked()
{
    //if(isBeep)beep(50000,28);
    g_setVibrator();
}

void FormMain::setVibratorEnable(bool value)
{
    ui->toolButtonVibrator->setEnabled(value);
}
