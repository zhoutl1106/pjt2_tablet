#ifndef FORMMODESELECT_H
#define FORMMODESELECT_H

#include <QWidget>
#include <QButtonGroup>
#include <QToolButton>

namespace Ui {
class FormModeSelect;
}

class FormModeSelect : public QWidget
{
    Q_OBJECT

public:
    explicit FormModeSelect(QWidget *parent = 0);
    ~FormModeSelect();

public slots:
    void updateData();

signals:
    void switchToPage(int index);
    void bkgShow();
    void sendCmd(int i,QByteArray array);

private slots:
    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

    void on_mode_1_clicked();
    void on_mode_2_clicked();
    void on_mode_3_clicked();
    void on_mode_4_clicked();
    void on_mode_5_clicked();

    void on_toolButton_3_clicked();

    void on_mem_11_clicked();
    void on_mem_12_clicked();
    void on_mem_13_clicked();
    void on_mem_21_clicked();
    void on_mem_22_clicked();
    void on_mem_23_clicked();
    void on_mem_31_clicked();
    void on_mem_32_clicked();
    void on_mem_33_clicked();
    void on_mem_41_clicked();
    void on_mem_42_clicked();
    void on_mem_43_clicked();
    void on_mem_51_clicked();
    void on_mem_52_clicked();
    void on_mem_53_clicked();

private:
    void setSelect(int mode, int mem);
    Ui::FormModeSelect *ui;
    int mode;
    int mem;
    QList<QToolButton*> list;
    QString buttonBkgChecked;
    QString buttonBkgUnchecked;
    QString memBkgChecked;
    QString memBkgUnChecked;
};

#endif // FORMMODESELECT_H
