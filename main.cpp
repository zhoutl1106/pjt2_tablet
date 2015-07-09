#include "widget.h"
#include <QApplication>
#include <QTime>
#include <QFile>
#include <QTextStream>
#include "dialogautoclosemessagebox.h"
#include "dialog.h"

Dialog *g_dialog;
Widget *g_widget;
QString stylesheet;
DialogAutoCloseMessageBox *bkgMsgBoxF;
DialogAutoCloseMessageBox *bkgMsgBoxE;
DialogAutoCloseMessageBox *msgLowPressure;

bool isBeep;

void beep(int length_us, int index = 0)
{
    //qDebug()<<"beep"<<index;
}

bool valveStatus = false;
bool vibratorStatus = false;

void Sleep(int ms)
{
    QTime time = QTime::currentTime().addMSecs(ms);
    while(QTime::currentTime() < time)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

void g_setValve()
{
    valveStatus = !valveStatus;
    g_dialog->form2_main->setValve(valveStatus);
    g_dialog->form3_vibrationAdjust->setValve(valveStatus);
    char tmp[2] = {0x09,0x00};
    tmp[1] = valveStatus;
    QByteArray tmp1(tmp,2);
    g_dialog->cmdSocket->writeDatagram(tmp1,QHostAddress(g_widget->getTarget()),UDP_CMD_WRITE_PORT);
}

void g_setVibrator()
{
    vibratorStatus = !vibratorStatus;
    g_dialog->form2_main->setVibrator(vibratorStatus);
    g_dialog->form3_vibrationAdjust->setVibrator(vibratorStatus);
    char tmp[2] = {0x0a,0x00};
    tmp[1] = vibratorStatus;
    QByteArray tmp1(tmp,2);
    g_dialog->cmdSocket->writeDatagram(tmp1,QHostAddress(g_widget->getTarget()),UDP_CMD_WRITE_PORT);
    if(!vibratorStatus)
        Sleep(10000);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile file(":/qss.qss");
    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    stylesheet = filetext.readAll();
    file.close();
    bkgMsgBoxF = new DialogAutoCloseMessageBox(NULL,"背景板","...","","",30,true);
    bkgMsgBoxE = new DialogAutoCloseMessageBox(NULL,"背景板","...","","",30,true);
    msgLowPressure = new DialogAutoCloseMessageBox(NULL,"警报","气压过低\n请检查气源及气路","重试","确定",30,true);
    Widget w;
    g_widget = &w;
    w.setStyleSheet(stylesheet);
    w.show();

    return a.exec();
}
