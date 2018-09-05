#include "mygraphicsview.h"

#include <QGraphicsScene>

MyGraphicsView::MyGraphicsView(QWidget * parent) : QGraphicsView(parent)
{
    m_freeItem = new FreeDrawingItem();
    this->setMouseTracking(true);
}

void MyGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if( !(scene()->items().contains(m_freeItem)))
    {
        this->scene()->addItem(m_freeItem);
        m_freeItem->startCreate(mapToScene(event->pos()));
    }
    else
    {
        m_freeItem->downWhenCreating(mapToScene(event->pos()));
    }
//    QGraphicsView::mousePressEvent(event);
}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if((scene()->items().contains(m_freeItem)))
    {
        m_freeItem->upWhenCreating(mapToScene(event->pos()));
    }
//    QGraphicsView::mouseReleaseEvent(event);
}

void MyGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if((scene()->items().contains(m_freeItem)))
    {
        m_freeItem->moveWhenCreating(mapToScene(event->pos()));
    }
//    QGraphicsView::mouseMoveEvent(event);
}
