#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QTimer>
#include "dialogautoclosemessagebox.h"

#ifdef _WIN32
#define UNLOCK_FILENAME "E:/dat/zt_license"
#define DATE_FILENAME "E:/dat/zt_dates"
#define LAST_INDEX_FILENAME "E:/dat/zt_lastIndex"
#define CONFIG_FILENAME_HEAD "E:/dat/zt_config"
#else
#define UNLOCK_FILENAME "/dat/zt_license"
#define DATE_FILENAME "/dat/zt_dates"
#define LAST_INDEX_FILENAME "/dat/zt_lastIndex"
#define CONFIG_FILENAME_HEAD "/dat/zt_config"
#endif

#define ASH_MODE_AUTO 1
#define ASH_MODE_TIME 2

class FileManager : public QObject
{
    Q_OBJECT
public:
    explicit FileManager(QObject *parent = 0);
    void writeConfig(int mode, int index);
    void writeLastConfig();
    int readConfig(int mode, int index);
    void getLastConfigIndex();
    int sendCmds();
    void setLights();
    void configChange();

    struct config_t
    {
        double delay[14];
        double pulse_width[14];
        double frontLuminanceThreshold;
        double endLuminanceThreshold;
        double frontMotorVoltage;
        double endMotorVoltage;
        int accuracy[14][3];
        int vibration[7];
        int ash_delay;
        int ash_mode;
        int ash_interval;
        int times[14];
        int showUpper;
        int showLower;
        quint8 vibratorStatusU8;
        quint8 nop[7];
    }config;
    int mode;
    int mem;
    int m_lastMode;
    int m_lastIndex;

signals:
    //void updateConfig(QString str,int index);
    //void sendCmd(int type,QByteArray cmd);
    void updateInitialStatus(bool exit, QString str);
    void switchToPage(int index);
    void bkgShow();
    void sigConfigChanged();

public slots:
    bool checkDate();
    bool passwardReceived(QString ori, QString code);

private:
    QTimer *timer;
    DialogAutoCloseMessageBox *dlg;
};

#endif // FILEMANAGER_H
