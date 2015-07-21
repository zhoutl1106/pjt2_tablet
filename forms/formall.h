#ifndef FORMALL_H
#define FORMALL_H

#include <QWidget>
#include "../longclicktoolbutton.h"
#include <QTimer>

namespace Ui {
class FormAll;
}

class FormAll : public QWidget
{
    Q_OBJECT

public:
    explicit FormAll(QWidget *parent = 0);
    ~FormAll();
    void setValve(bool value);
    void setVibrator(bool value);

private slots:
    void lbtnValue(int index, int value);

    void on_toolButtonOK_clicked();

    void on_toolButtonValve_clicked();

    void on_toolButtonVibrator_clicked();

    void on_toolButtonExit_pressed();

    void on_toolButtonExit_released();
    void onLongPressTimer();

private:
    Ui::FormAll *ui;
    LongClickToolButton *lbtn[2];
    QTimer *longPressTimer;
};

#endif // FORMALL_H
