#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>

class MyGraphicsView;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    QGraphicsScene m_scene;
    MyGraphicsView *m_view;

};

#endif // WIDGET_H
