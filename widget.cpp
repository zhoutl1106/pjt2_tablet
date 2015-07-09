#include "widget.h"
#include "ui_widget.h"
#include <QDate>
#include <QTime>

extern Dialog* g_dialog;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    dlg = new Dialog;
    g_dialog = dlg;
    ui->stackedWidget->insertWidget(2,dlg);
    ui->stackedWidget->setCurrentIndex(2);
    memset(versions,0,12*2*sizeof(int));
    list.append(ui->radioButton_1);
    list.append(ui->radioButton_2);
    list.append(ui->radioButton_3);
    list.append(ui->radioButton_4);
    list.append(ui->radioButton_5);
    list.append(ui->radioButton_6);
    list.append(ui->radioButton_7);
    list.append(ui->radioButton_8);
    list.append(ui->radioButton_9);
    list.append(ui->radioButton_10);
    list.append(ui->radioButton_11);
    list.append(ui->radioButton_12);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    memset(versions,0,12*2*sizeof(int));
    QDate dat = QDate::currentDate();
    QTime tim = QTime::currentTime();
    QByteArray cmd;
    cmd.append(char(0x01));
    cmd.append(char(0x00));
    cmd.append(char(dat.year()-2000));
    cmd.append(char(dat.month()));
    cmd.append(char(dat.day()));
    cmd.append(char(tim.hour()));
    cmd.append(char(tim.minute()));
    cmd.append(char(tim.second()));
    g_dialog->cmdSocket->writeDatagram(cmd,QHostAddress("192.168.1.255"),UDP_CMD_WRITE_PORT);
}

void Widget::updateDisplay()
{
    ui->radioButton_All->setChecked(true);
    for(int i = 0;i<12;i++)
    {
        qDebug()<<i<<versions[i][0]<<versions[i][1];
        if(versions[i][0] == 0 && versions[i][1] == 0)
        {
            list.at(i)->setText("色选机" + QString::number(i+1)
                                +"\n未知");
            list.at(i)->setEnabled(false);
            list.at(i)->setChecked(false);
        }
        else
        {
            list.at(i)->setText("色选机" + QString::number(i+1)
                                +"\nv " + QString::number(versions[i][0])
                    +"."+QString::number(versions[i][1]));
            list.at(i)->setEnabled(true);
            list.at(i)->setChecked(true);
        }
    }
}

QString Widget::getTarget()
{
    QString str = "192.168.1.";
    if(ui->radioButton_1->isChecked())
        return str + "101";
    if(ui->radioButton_2->isChecked())
        return str + "102";
    if(ui->radioButton_3->isChecked())
        return str + "103";
    if(ui->radioButton_4->isChecked())
        return str + "104";
    if(ui->radioButton_5->isChecked())
        return str + "105";
    if(ui->radioButton_6->isChecked())
        return str + "106";
    if(ui->radioButton_7->isChecked())
        return str + "107";
    if(ui->radioButton_8->isChecked())
        return str + "108";
    if(ui->radioButton_9->isChecked())
        return str + "109";
    if(ui->radioButton_10->isChecked())
        return str + "110";
    if(ui->radioButton_11->isChecked())
        return str + "111";
    if(ui->radioButton_12->isChecked())
        return str + "112";
    if(ui->radioButton_All->isChecked())
        return str + "255";
    return "";
}

void Widget::on_pushButton_sync_clicked()
{
    QByteArray cmd;
    cmd.append(char(0x05));
    cmd.append(char(0x00));
    g_dialog->cmdSocket->writeDatagram(cmd,QHostAddress(getTarget()),UDP_CMD_WRITE_PORT);
}
