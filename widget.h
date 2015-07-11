#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "dialog.h"
#include <QRadioButton>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    Dialog *dlg;
    int versions[12][2];
    void updateDisplay();
    QString getTarget();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_sync_clicked();

    void on_radioButton_1_clicked();
    void on_radioButton_2_clicked();
    void on_radioButton_3_clicked();
    void on_radioButton_4_clicked();
    void on_radioButton_5_clicked();
    void on_radioButton_6_clicked();
    void on_radioButton_7_clicked();
    void on_radioButton_8_clicked();
    void on_radioButton_9_clicked();
    void on_radioButton_10_clicked();
    void on_radioButton_11_clicked();
    void on_radioButton_12_clicked();
    void on_radioButton_All_clicked();

private:
    Ui::Widget *ui;
    QList<QRadioButton *> list;
};

#endif // WIDGET_H
