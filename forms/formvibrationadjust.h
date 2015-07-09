#ifndef FORMVIBRATIONADJUST_H
#define FORMVIBRATIONADJUST_H

#include <QWidget>
#include <QSlider>
#include <QTimer>
#include "../longclicktoolbutton.h"

#define V1 0x01
#define V2 0x02
#define V3 0x04
#define V4 0x08
#define V5 0x10
#define V6 0x20
#define V7 0x40

namespace Ui {
class FormVibrationAdjust;
}

class FormVibrationAdjust : public QWidget
{
    Q_OBJECT

public:
    explicit FormVibrationAdjust(QWidget *parent = 0);
    ~FormVibrationAdjust();
    void setValve(bool value);
    void setVibrator(bool value);
    void setVibratorEnable(bool value);

public slots:
    void updateData();
    void lbtnValue(int index, int value);
    void lbtnRelease(int index,int);

signals:
    void switchToPage(int index);
    void sendCmd(int type,QByteArray cmd);

protected:

private slots:
    void on_toolButton_clicked();

    void on_verticalSlider1_valueChanged(int value);
    void on_verticalSlider2_valueChanged(int value);
    void on_verticalSlider3_valueChanged(int value);
    void on_verticalSlider4_valueChanged(int value);
    void on_verticalSlider5_valueChanged(int value);
    void on_verticalSlider6_valueChanged(int value);
    void on_verticalSlider7_valueChanged(int value);

    void on_verticalSlider1_sliderReleased();
    void on_verticalSlider2_sliderReleased();
    void on_verticalSlider3_sliderReleased();
    void on_verticalSlider4_sliderReleased();
    void on_verticalSlider5_sliderReleased();
    void on_verticalSlider6_sliderReleased();
    void on_verticalSlider7_sliderReleased();

    void on_verticalSlider1_sliderPressed();
    void on_verticalSlider2_sliderPressed();
    void on_verticalSlider3_sliderPressed();
    void on_verticalSlider4_sliderPressed();
    void on_verticalSlider5_sliderPressed();
    void on_verticalSlider6_sliderPressed();
    void on_verticalSlider7_sliderPressed();

    void on_pushButton_v1_clicked();
    void on_pushButton_v2_clicked();
    void on_pushButton_v3_clicked();
    void on_pushButton_v4_clicked();
    void on_pushButton_v5_clicked();
    void on_pushButton_v6_clicked();
    void on_pushButton_v7_clicked();

    void on_toolButton_Single_clicked();

    void on_toolButton_All_clicked();

    void on_toolButtonVibrator_clicked();

    void on_toolButtonValve_clicked();

private:
    Ui::FormVibrationAdjust *ui;
    void deltaSlider(int index, int delta);
    void sendVibrationValue(int index);
    QList<QSlider*> listSlider;
    int lastValue[7];
    bool isAll;
    bool isOpen[7];
    QString styleSheet[2];
    quint8 status;
    LongClickToolButton *btn[14];
    QList<QWidget*> listWidget;
};

#endif // FORMVIBRATIONADJUST_H
