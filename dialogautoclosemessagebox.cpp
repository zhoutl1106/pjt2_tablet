#include "dialogautoclosemessagebox.h"
#include "ui_dialogautoclosemessagebox.h"
#include <QDebug>

//extern bool isBeep;
//void beep(int length_us, int index = 0);

DialogAutoCloseMessageBox::DialogAutoCloseMessageBox(QWidget *parent, QString title, QString text,
                                                     QString acceptText, QString rejectText, int delay_s, bool isTimeShow, bool isDefaultAccept) :

    QDialog(parent),
    ui(new Ui::DialogAutoCloseMessageBox)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    m_delay_s = delay_s;
    ui->labelTitle->setText(title);
    ui->label->setText(text);
    ui->labelCntDown->setText(QString::number(m_delay_s) + " s");
    if(acceptText.isEmpty())
        ui->pushButtonOK->setVisible(false);
    else
    {
        ui->pushButtonOK->setText(acceptText);
        ui->pushButtonOK->setVisible(true);
    }
    if(rejectText.isEmpty())
        ui->pushButtonCancel->setVisible(false);
    else
    {
        ui->pushButtonCancel->setText(rejectText);
        ui->pushButtonCancel->setVisible(true);
    }
    timer = new QTimer;
    timer->setInterval(1000);
    connect(timer,SIGNAL(timeout()),this,SLOT(onTimer()));
    if(!isTimeShow)
    {
        ui->labelCntDown->setVisible(false);
        ui->pushButtonOK->setVisible(false);
        ui->pushButtonCancel->setVisible(false);
    }
    setWindowModality(Qt::ApplicationModal);
    m_isDefaultAccept = isDefaultAccept;
}

void DialogAutoCloseMessageBox::setText(QString text)
{
    ui->label->setText(text);
    ui->label->adjustSize();
    ui->label->setWordWrap(true);
    ui->label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

DialogAutoCloseMessageBox::~DialogAutoCloseMessageBox()
{
    delete ui;
}

void DialogAutoCloseMessageBox::onTimer()
{
    m_delay_s --;
    if(m_delay_s >= 0)
        ui->labelCntDown->setText(QString::number(m_delay_s) + " s");
    else
    {
        if(m_isDefaultAccept)
            on_pushButtonOK_clicked();
        else
            on_pushButtonCancel_clicked();
    }
}

void DialogAutoCloseMessageBox::on_pushButtonOK_clicked()
{
    //beep(50000,103);
    qDebug()<<"autocloseMsg 103"<<ui->label->text();
    timer->stop();
    accept();
    close();
}

void DialogAutoCloseMessageBox::on_pushButtonCancel_clicked()
{
    //beep(50000,104);
    qDebug()<<"autocloseMsg 104"<<ui->label->text();
    timer->stop();
    reject();
    close();
}

void DialogAutoCloseMessageBox::setDelay(int s)
{
    m_delay_s = s;
    ui->labelCntDown->setText(QString::number(m_delay_s) + " s");
}

int DialogAutoCloseMessageBox::exec()
{
    timer->start();
    return QDialog::exec();
}
