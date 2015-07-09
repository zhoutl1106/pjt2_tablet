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

private:
    Ui::Widget *ui;
    QList<QRadioButton *> list;
};

#endif // WIDGET_H
