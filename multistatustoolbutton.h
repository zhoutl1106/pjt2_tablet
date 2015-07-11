#ifndef MULTISTATUSTOOLBUTTON_H
#define MULTISTATUSTOOLBUTTON_H


#include <QToolButton>

class MultiStatusToolButton : public QToolButton
{
    Q_OBJECT

public:
    MultiStatusToolButton(QWidget* parent, int statusCnt, ...);
    ~MultiStatusToolButton();
    int currentIndex();
    void setCurrentIndex(int v);

public slots:
    void onclick();

private:
    int m_index;
    QList<QString> textList;
    QList<QString> styleSheetList;
};

#endif // MULTISTATUSTOOLBUTTON_H
