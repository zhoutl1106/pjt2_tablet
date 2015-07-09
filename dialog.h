#ifndef DIALOG_H
#define DIALOG_H

#define VERSION 0
#define SUBVERSION 1

#define UDP_CMD_LINSTEN_PORT    8001
#define UDP_CMD_WRITE_PORT    8000
#define UDP_UPDATE_LINSTEN_PORT    9001
#define UDP_UPDATE_WRITE_PORT    9000

#define UPDATE_TEMP_FILE_NAME   "/2"

#include <QDialog>
#include <QTimer>
#include <QFile>
#include <QUdpSocket>
#include "filemanager.h"
//#include "formkeyboard.h"
//#include "serialmanager.h"
//#include "forms/formwelcome.h"
//#include "forms/formlicense.h"
#include "forms/formmain.h"
#include "forms/formvibrationadjust.h"
//#include "forms/formmodeselect.h"
//#include "forms/formaccuracyadjust.h"
//#include "forms/formsystem.h"
//#include "forms/formshutdown.h"
//#include "forms/formadmin.h"
//#include "forms/formashclean.h"
//#include "forms/formccdcurve.h"
//#include "forms/formvalvetest.h"
//#include "forms/formaccuracydetailadjust.h"
//#include "forms/formwholesetting.h"
//#include "forms/formcntcheck.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    FileManager *fileManager;
//    SerialManager *serialManager;
    void setModeAndMem(int mode, int mem);
    QUdpSocket *cmdSocket;
    void writeUdpCmd(int index, QByteArray cmd);


//    FormWelcome                 *form0_welcome;
//    FormLicense                 *form1_account;
    FormMain                    *form2_main;
    FormVibrationAdjust         *form3_vibrationAdjust;
//    FormModeSelect              *form4_mode;
//    FormAccuracyAdjust          *form5_accuracy;
//    FormSystem                  *form6_system;
//    FormShutdown                *form7_shutdown;
//    FormAdmin                   *form8_admin;
//    FormAshClean                *form9_ash;
//    FormCCDCurve                *form10_bkg;
//    FormValveTest               *form11_valve;
//    FormAccuracyDetailAdjust    *form12_accuracyDetail;
//    FormWholeSetting            *form13_whole;
//    FormCntCheck                *form14_monitor;

private slots:
    void onUpdateUdpRead();
    void onCmdUdpRead();
    void onDisplayTime();

private:
    Ui::Dialog *ui;
    QTimer *displayTimer;
    QFile file;
    QUdpSocket *updateSocket;
    QByteArray cmdBuf;
    void processUdpCmd(QByteArray& buf, QHostAddress sender);
    bool isAnotherCmd(QByteArray buf);
    int m_lastIndex;
};

#endif // DIALOG_H
