#include "mygraphicsview.h"

#include <QGraphicsScene>

MyGraphicsView::MyGraphicsView(QWidget * parent) : QGraphicsView(parent)
{
    this->setMouseTracking(true);
}

void MyGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton && m_isInCreating)
    {
        m_freeItem->endCreate();
        m_isInCreating = false;
    }
    else
    {
        if( !m_isInCreating)
        {
            m_freeItem = new FreeDrawingItem;
            this->scene()->addItem(m_freeItem);
            m_freeItem->startCreate(mapToScene(event->pos()));

            m_isInCreating = true;
        }
        else
        {
            m_freeItem->downWhenCreating(mapToScene(event->pos()));
        }
    }

//    QGraphicsView::mousePressEvent(event);
}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if((scene()->items().contains(m_freeItem)) && m_isInCreating)
    {
        m_freeItem->upWhenCreating(mapToScene(event->pos()));
    }
//    QGraphicsView::mouseReleaseEvent(event);
}

void MyGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if((scene()->items().contains(m_freeItem)) && m_isInCreating)
    {
        m_freeItem->moveWhenCreating(mapToScene(event->pos()));
    }
//    QGraphicsView::mouseMoveEvent(event);
}
