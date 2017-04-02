#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "costumscene.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
private:
    CostumScene costumScene;

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event);
private slots:
    void on_label_linkActivated(const QString &link);
};

#endif // WIDGET_H
