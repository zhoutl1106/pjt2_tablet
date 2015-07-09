#ifndef LONGCLICKTOOLBUTTON_H
#define LONGCLICKTOOLBUTTON_H

#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QToolButton>
#include <QTimer>

class LongClickToolButton : public QToolButton
{
    Q_OBJECT

public:
    LongClickToolButton(QWidget* parent, int index, int delta);
    ~LongClickToolButton();
    void paintEvent(QPaintEvent *);

signals:
    void longClick(int index, int delta);
    void released(int index, int delta);

public slots:
    void onclick();

private slots:
    void pressed();
    void released();
    void onTimer();

private:
    int m_index;
    int m_delta;
    QTimer *timer;
};

#endif // LONGCLICKTOOLBUTTON_H
