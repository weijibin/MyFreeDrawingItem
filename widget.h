#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>

class MyGraphicsView;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    QGraphicsScene m_scene;
    MyGraphicsView *m_view;

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
