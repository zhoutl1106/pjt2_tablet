#ifndef FORMACCURACYADJUST_H
#define FORMACCURACYADJUST_H

#include <QWidget>
#include "../multistatustoolbutton.h"
#include "../longclicktoolbutton.h"
#include <QSlider>

namespace Ui {
class FormAccuracyAdjust;
}

class FormAccuracyAdjust : public QWidget
{
    Q_OBJECT

public:
    explicit FormAccuracyAdjust(QWidget *parent = 0);
    ~FormAccuracyAdjust();

signals:
    void switchToPage(int index);

private slots:
    void on_toolButton_clicked();
    void lbtnValue(int index, int value);

    void onCameraClicked();

    void on_toolButton_2_clicked();

private:
    Ui::FormAccuracyAdjust *ui;
    void checkDataRange(int &v, int min, int max);
    MultiStatusToolButton *btn;
    QList<QWidget*> listWidget;
    QList<QSlider*> listSlider;
    LongClickToolButton *lbtn[18];
};

#endif // FORMACCURACYADJUST_H
