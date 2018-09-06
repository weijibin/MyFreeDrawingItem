#include "widget.h"
#include "mygraphicsview.h"

#include <QGraphicsRectItem>
#include <QHBoxLayout>

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{

    m_view = new MyGraphicsView(this);
    QHBoxLayout * layout = new QHBoxLayout;
    layout->addWidget(m_view);
    this->setLayout(layout);

    m_scene.setSceneRect(-250,-250,500,500);
    m_view->setScene(&m_scene);
//    m_scene.addRect(QRect(0,0,200,50));
}

Widget::~Widget()
{

}
