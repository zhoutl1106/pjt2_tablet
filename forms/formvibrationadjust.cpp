#include "formvibrationadjust.h"
#include "ui_formvibrationadjust.h"
#include <QDebug>
#include "../dialog.h"
#include <QVBoxLayout>

extern Dialog* g_dialog;
void beep(int length_us, int index = 0);
extern bool isBeep;
extern QString stylesheet;
void g_setValve();
void g_setVibrator();

FormVibrationAdjust::FormVibrationAdjust(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormVibrationAdjust)
{
    ui->setupUi(this);
    isAll = false;
    memset(isOpen,0,7*sizeof(bool));

    setStyleSheet(stylesheet);

    styleSheet[1] = "font-size:20px;border-image: url(:/image/btnR.png);color: rgb(255, 255, 255);";
    styleSheet[0] = "font-size:20px;border-image: url(:/image/btnG.png);color: rgb(255, 255, 255);";
    ui->toolButton_Single->setStyleSheet(styleSheet[1]);
    ui->toolButton_All->setStyleSheet(styleSheet[0]);
    ui->pushButton_v1->setStyleSheet(styleSheet[0]);
    ui->pushButton_v2->setStyleSheet(styleSheet[0]);
    ui->pushButton_v3->setStyleSheet(styleSheet[0]);
    ui->pushButton_v4->setStyleSheet(styleSheet[0]);
    ui->pushButton_v5->setStyleSheet(styleSheet[0]);
    ui->pushButton_v6->setStyleSheet(styleSheet[0]);
    ui->pushButton_v7->setStyleSheet(styleSheet[0]);
    listSlider.append(ui->verticalSlider1);
    listSlider.append(ui->verticalSlider2);
    listSlider.append(ui->verticalSlider3);
    listSlider.append(ui->verticalSlider4);
    listSlider.append(ui->verticalSlider5);
    listSlider.append(ui->verticalSlider6);
    listSlider.append(ui->verticalSlider7);
    status = 0;
    memset(lastValue,0,7*sizeof(int));
    isAll = false;
    listWidget.append(ui->widget_1u);
    listWidget.append(ui->widget_1d);
    listWidget.append(ui->widget_2u);
    listWidget.append(ui->widget_2d);
    listWidget.append(ui->widget_3u);
    listWidget.append(ui->widget_3d);
    listWidget.append(ui->widget_4u);
    listWidget.append(ui->widget_4d);
    listWidget.append(ui->widget_5u);
    listWidget.append(ui->widget_5d);
    listWidget.append(ui->widget_6u);
    listWidget.append(ui->widget_6d);
    listWidget.append(ui->widget_7u);
    listWidget.append(ui->widget_7d);

    for(int i = 0;i<14;i++)
    {
        btn[i] = new LongClickToolButton(NULL,i/2,i%2==0?1:-1,LongClickToolButton::vertical);
        connect(btn[i],SIGNAL(longClick(int,int)),this,SLOT(lbtnValue(int,int)));
        connect(btn[i],SIGNAL(released(int,int)),this,SLOT(lbtnRelease(int,int)));
        QVBoxLayout *layout = new QVBoxLayout;
        layout->setMargin(0);
        layout->addWidget(btn[i]);
        listWidget.at(i)->setLayout(layout);
    }
}

FormVibrationAdjust::~FormVibrationAdjust()
{
    delete ui;
}

void FormVibrationAdjust::lbtnValue(int index, int value)
{
    listSlider.at(index)->setValue(listSlider.at(index)->value()+value);
}

void FormVibrationAdjust::lbtnRelease(int index, int delta)
{
    listSlider.at(index)->setValue(listSlider.at(index)->value()+delta);
    sendVibrationValue(index);
}

void FormVibrationAdjust::sendVibrationValue(int index)
{
    char tmp[3] = {0x82,0x00};
    QByteArray temp = QByteArray(tmp,3);
    if(!isAll)
    {
        temp.data()[0] = 0x82 + index;
        temp.data()[1] = listSlider.at(index)->value();
        g_dialog->writeUdpCmd(0,temp);
    }
    else
    {
        for(int i = 0;i<7;i++)
        {
            temp.data()[0] = 0x82 + i;
            temp.data()[1] = listSlider.at(i)->value();
            g_dialog->writeUdpCmd(0,temp);
        }
    }
}

void FormVibrationAdjust::setValve(bool value)
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

void FormVibrationAdjust::setVibrator(bool value)
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

void FormVibrationAdjust::updateData()
{
    bool tempBeep = isBeep;
    isBeep = false;
    ui->verticalSlider1->setValue(g_dialog->fileManager->config.vibration[0]);
    ui->verticalSlider2->setValue(g_dialog->fileManager->config.vibration[1]);
    ui->verticalSlider3->setValue(g_dialog->fileManager->config.vibration[2]);
    ui->verticalSlider4->setValue(g_dialog->fileManager->config.vibration[3]);
    ui->verticalSlider5->setValue(g_dialog->fileManager->config.vibration[4]);
    ui->verticalSlider6->setValue(g_dialog->fileManager->config.vibration[5]);
    ui->verticalSlider7->setValue(g_dialog->fileManager->config.vibration[6]);

    for(int i = 0;i<7;i++)
    {
        isOpen[i] = g_dialog->fileManager->config.vibratorStatusU8 & (1 << i);
        lastValue[i] = g_dialog->fileManager->config.vibration[i];
        //qDebug()<<isOpen[i]<<lastValue[i];
    }
    ui->pushButton_v1->setStyleSheet(styleSheet[isOpen[0]]);
    ui->pushButton_v2->setStyleSheet(styleSheet[isOpen[1]]);
    ui->pushButton_v3->setStyleSheet(styleSheet[isOpen[2]]);
    ui->pushButton_v4->setStyleSheet(styleSheet[isOpen[3]]);
    ui->pushButton_v5->setStyleSheet(styleSheet[isOpen[4]]);
    ui->pushButton_v6->setStyleSheet(styleSheet[isOpen[5]]);
    ui->pushButton_v7->setStyleSheet(styleSheet[isOpen[6]]);

    status = g_dialog->fileManager->config.vibratorStatusU8;

    isBeep = tempBeep;
}

void FormVibrationAdjust::on_toolButton_clicked()
{
    if(isBeep)beep(50000,70);
    g_dialog->fileManager->writeConfig(g_dialog->fileManager->mode,g_dialog->fileManager->mem);
    emit switchToPage(0);
}

void FormVibrationAdjust::on_verticalSlider1_valueChanged(int value)
{
    int delta = value - lastValue[0];
    ui->lcdNumber1->display(value);
    if(delta == 10 || delta == -10)
    {
        ui->verticalSlider1->setValue(lastValue[0]);
        ui->lcdNumber1->display(lastValue[0]);
        return;
    }
    lastValue[0] = value;

    if(isAll)
        deltaSlider(1,delta);

    g_dialog->fileManager->config.vibration[0] = value;
}

void FormVibrationAdjust::on_verticalSlider2_valueChanged(int value)
{
    int delta = value - lastValue[1];
    ui->lcdNumber2->display(value);
    if(delta == 10 || delta == -10)
    {
        ui->verticalSlider2->setValue(lastValue[1]);
        ui->lcdNumber2->display(lastValue[1]);
        return;
    }
    lastValue[1] = value;

    if(isAll)
        deltaSlider(2,delta);

    g_dialog->fileManager->config.vibration[1] = value;
}

void FormVibrationAdjust::on_verticalSlider3_valueChanged(int value)
{
    int delta = value - lastValue[2];
    ui->lcdNumber3->display(value);
    if(delta == 10 || delta == -10)
    {
        ui->verticalSlider3->setValue(lastValue[2]);
        ui->lcdNumber3->display(lastValue[2]);
        return;
    }
    lastValue[2] = value;

    if(isAll)
        deltaSlider(3,delta);

    g_dialog->fileManager->config.vibration[2] = value;
}

void FormVibrationAdjust::on_verticalSlider4_valueChanged(int value)
{
    int delta = value - lastValue[3];
    ui->lcdNumber4->display(value);
    if(delta == 10 || delta == -10)
    {
        ui->verticalSlider4->setValue(lastValue[3]);
        ui->lcdNumber4->display(lastValue[3]);
        return;
    }
    lastValue[3] = value;

    if(isAll)
        deltaSlider(4,delta);

    g_dialog->fileManager->config.vibration[3] = value;
}

void FormVibrationAdjust::on_verticalSlider5_valueChanged(int value)
{
    int delta = value - lastValue[4];
    ui->lcdNumber5->display(value);
    if(delta == 10 || delta == -10)
    {
        ui->verticalSlider5->setValue(lastValue[4]);
        ui->lcdNumber5->display(lastValue[4]);
        return;
    }
    lastValue[4] = value;

    if(isAll)
        deltaSlider(5,delta);

    g_dialog->fileManager->config.vibration[4] = value;
}

void FormVibrationAdjust::on_verticalSlider6_valueChanged(int value)
{
    int delta = value - lastValue[5];
    ui->lcdNumber6->display(value);
    if(delta == 10 || delta == -10)
    {
        ui->verticalSlider6->setValue(lastValue[5]);
        ui->lcdNumber6->display(lastValue[5]);
        return;
    }
    lastValue[5] = value;

    if(isAll)
        deltaSlider(6,delta);

    g_dialog->fileManager->config.vibration[5] = value;
}

void FormVibrationAdjust::on_verticalSlider7_valueChanged(int value)
{
    int delta = value - lastValue[6];
    ui->lcdNumber7->display(value);
    if(delta == 10 || delta == -10)
    {
        ui->verticalSlider7->setValue(lastValue[6]);
        ui->lcdNumber7->display(lastValue[6]);
        return;
    }
    lastValue[6] = value;

    if(isAll)
        deltaSlider(7,delta);

    g_dialog->fileManager->config.vibration[6] = value;
}

void FormVibrationAdjust::on_verticalSlider1_sliderReleased()
{
    isBeep = true;
    if(isBeep)beep(50000,78);
    sendVibrationValue(0);
}

void FormVibrationAdjust::on_verticalSlider2_sliderReleased()
{
    isBeep = true;
    if(isBeep)beep(50000,79);
    sendVibrationValue(1);
}

void FormVibrationAdjust::on_verticalSlider3_sliderReleased()
{
    isBeep = true;
    if(isBeep)beep(50000,80);
    sendVibrationValue(2);
}

void FormVibrationAdjust::on_verticalSlider4_sliderReleased()
{
    isBeep = true;
    if(isBeep)beep(50000,81);
    sendVibrationValue(3);
}

void FormVibrationAdjust::on_verticalSlider5_sliderReleased()
{
    isBeep = true;
    if(isBeep)beep(50000,82);
    sendVibrationValue(4);
}

void FormVibrationAdjust::on_verticalSlider6_sliderReleased()
{
    isBeep = true;
    if(isBeep)beep(50000,83);
    sendVibrationValue(5);
}

void FormVibrationAdjust::on_verticalSlider7_sliderReleased()
{
    isBeep = true;
    if(isBeep)beep(50000,84);
    sendVibrationValue(6);
}

void FormVibrationAdjust::on_verticalSlider1_sliderPressed()
{
    if(isBeep)beep(50000,85);
    isBeep = false;
}

void FormVibrationAdjust::on_verticalSlider2_sliderPressed()
{
    if(isBeep)beep(50000,86);
    isBeep = false;
}

void FormVibrationAdjust::on_verticalSlider3_sliderPressed()
{
    if(isBeep)beep(50000,87);
    isBeep = false;
}

void FormVibrationAdjust::on_verticalSlider4_sliderPressed()
{
    if(isBeep)beep(50000,88);
    isBeep = false;
}

void FormVibrationAdjust::on_verticalSlider5_sliderPressed()
{
    if(isBeep)beep(50000,89);
    isBeep = false;
}

void FormVibrationAdjust::on_verticalSlider6_sliderPressed()
{
    if(isBeep)beep(50000,90);
    isBeep = false;
}

void FormVibrationAdjust::on_verticalSlider7_sliderPressed()
{
    if(isBeep)beep(50000,91);
    isBeep = false;
}

void FormVibrationAdjust::on_pushButton_v1_clicked()
{
    if(isBeep)beep(50000,92);
    isOpen[0] = !isOpen[0];
    if(isOpen[0])
    {
        status |= V1;
    }
    else
    {
        status &= ~V1;
    }
    g_dialog->fileManager->config.vibratorStatusU8 = status;

    char temp[3] = {0x80,0x00,0x00};
    temp[1] = status;
    QByteArray cmd(temp,3);
    g_dialog->writeUdpCmd(0,cmd);
    ui->pushButton_v1->setStyleSheet(styleSheet[isOpen[0]]);
}

void FormVibrationAdjust::on_pushButton_v2_clicked()
{
    if(isBeep)beep(50000,93);
    isOpen[1] = !isOpen[1];
    if(isOpen[1])
    {
        status |= V2;
    }
    else
    {
        status &= ~V2;
    }
    g_dialog->fileManager->config.vibratorStatusU8 = status;
    char temp[3] = {0x80,0x00,0x00};
    temp[1] = status;
    QByteArray cmd(temp,3);
    g_dialog->writeUdpCmd(0,cmd);
    ui->pushButton_v2->setStyleSheet(styleSheet[isOpen[1]]);
}

void FormVibrationAdjust::on_pushButton_v3_clicked()
{
    if(isBeep)beep(50000,94);
    isOpen[2] = !isOpen[2];
    if(isOpen[2])
    {
        status |= V3;
    }
    else
    {
        status &= ~V3;
    }
    g_dialog->fileManager->config.vibratorStatusU8 = status;
    char temp[3] = {0x80,0x00,0x00};
    temp[1] = status;
    QByteArray cmd(temp,3);
    g_dialog->writeUdpCmd(0,cmd);
    ui->pushButton_v3->setStyleSheet(styleSheet[isOpen[2]]);
}

void FormVibrationAdjust::on_pushButton_v4_clicked()
{
    if(isBeep)beep(50000,95);
    isOpen[3] = !isOpen[3];
    if(isOpen[3])
    {
        status |= V4;
    }
    else
    {
        status &= ~V4;
    }
    g_dialog->fileManager->config.vibratorStatusU8 = status;
    char temp[3] = {0x80,0x00,0x00};
    temp[1] = status;
    QByteArray cmd(temp,3);
    g_dialog->writeUdpCmd(0,cmd);
    ui->pushButton_v4->setStyleSheet(styleSheet[isOpen[3]]);
}

void FormVibrationAdjust::on_pushButton_v5_clicked()
{
    if(isBeep)beep(50000,96);
    isOpen[4] = !isOpen[4];
    if(isOpen[4])
    {
        status |= V5;
    }
    else
    {
        status &= ~V5;
    }
    g_dialog->fileManager->config.vibratorStatusU8 = status;
    char temp[3] = {0x80,0x00,0x00};
    temp[1] = status;
    QByteArray cmd(temp,3);
    g_dialog->writeUdpCmd(0,cmd);
    ui->pushButton_v5->setStyleSheet(styleSheet[isOpen[4]]);
}

void FormVibrationAdjust::on_pushButton_v6_clicked()
{
    if(isBeep)beep(50000,97);
    isOpen[5] = !isOpen[5];
    if(isOpen[5])
    {
        status |= V6;
    }
    else
    {
        status &= ~V6;
    }
    g_dialog->fileManager->config.vibratorStatusU8 = status;
    char temp[3] = {0x80,0x00,0x00};
    temp[1] = status;
    QByteArray cmd(temp,3);
    g_dialog->writeUdpCmd(0,cmd);
    ui->pushButton_v6->setStyleSheet(styleSheet[isOpen[5]]);
}

void FormVibrationAdjust::on_pushButton_v7_clicked()
{
    if(isBeep)beep(50000,98);
    isOpen[6] = !isOpen[6];
    if(isOpen[6])
    {
        status |= V7;
    }
    else
    {
        status &= ~V7;
    }
    g_dialog->fileManager->config.vibratorStatusU8 = status;
    char temp[3] = {0x80,0x00,0x00};
    temp[1] = status;
    QByteArray cmd(temp,3);
    g_dialog->writeUdpCmd(0,cmd);
    ui->pushButton_v7->setStyleSheet(styleSheet[isOpen[6]]);
}


void FormVibrationAdjust::deltaSlider(int index, int delta)
{
    bool tempBeep = isBeep;
    isBeep = false;
    bool tempIsAll = isAll;
    isAll = false;
    for(int i = 0;i<7;i++)
        if(i != index - 1)
            listSlider.at(i)->setValue(listSlider.at(i)->value()+delta);

    lastValue[0] = ui->verticalSlider1->value();
    lastValue[1] = ui->verticalSlider2->value();
    lastValue[2] = ui->verticalSlider3->value();
    lastValue[3] = ui->verticalSlider4->value();
    lastValue[4] = ui->verticalSlider5->value();
    lastValue[5] = ui->verticalSlider6->value();
    lastValue[6] = ui->verticalSlider7->value();
    isBeep = tempBeep;
    isAll = tempIsAll;
}

void FormVibrationAdjust::on_toolButton_Single_clicked()
{
    if(isBeep)beep(50000,99);
    isAll = false;
    ui->toolButton_Single->setStyleSheet(styleSheet[1]);
    ui->toolButton_All->setStyleSheet(styleSheet[0]);
}

void FormVibrationAdjust::on_toolButton_All_clicked()
{
    if(isBeep)beep(50000,100);
    isAll = true;
    ui->toolButton_Single->setStyleSheet(styleSheet[0]);
    ui->toolButton_All->setStyleSheet(styleSheet[1]);
}

void FormVibrationAdjust::on_toolButtonVibrator_clicked()
{
    beep(50000,2100);
    g_setVibrator();
}

void FormVibrationAdjust::on_toolButtonValve_clicked()
{
    beep(50000,2101);
    g_setValve();
}

void FormVibrationAdjust::setVibratorEnable(bool value)
{
    ui->toolButtonVibrator->setEnabled(value);
}
