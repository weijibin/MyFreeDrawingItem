#include "widget.h"
#include "ui_widget.h"
#include "mygraphicsview.h"

#include <QGraphicsRectItem>
#include <QHBoxLayout>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_view = new MyGraphicsView(this);
    QHBoxLayout * layout = new QHBoxLayout;
    layout->addWidget(m_view);
    this->setLayout(layout);

    m_view->setScene(&m_scene);
    m_scene.addRect(QRect(0,0,200,50));
}

Widget::~Widget()
{
    delete ui;
}
