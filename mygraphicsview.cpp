#include "mygraphicsview.h"
#include <QGraphicsScene>
#include <QCursor>
#include <QDebug>

MyGraphicsView::MyGraphicsView(QWidget * parent) : QGraphicsView(parent)
{
    this->setMouseTracking(true);
    setCursor(QCursor(Qt::ArrowCursor));
}

bool MyGraphicsView::event(QEvent* ev)
{
//    if (ev->type() == QEvent::PolishRequest) {
//        // overwrite handling of PolishRequest if any
//        doThings();
//        return true;
//    } else  if (ev->type() == QEvent::Show) {

//        QWidget::event(ev);
//        return true;
//    }
    qDebug()<<"======MyGraphicsView::event======";
    qDebug()<<ev->type();
    qDebug()<<"=============================";

    // Make sure the rest of events are handled
    return QWidget::event(ev);
}

void MyGraphicsView::mousePressEvent(QMouseEvent *event)
{

    //    if(!endCreated)
            QGraphicsView::mousePressEvent(event);

    if(endCreated)
        return;

    if(event->button() == Qt::RightButton && m_isInCreating)
    {
        m_freeItem->endCreate();
        m_isInCreating = false;

        endCreated = true;
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

}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if((scene()->items().contains(m_freeItem)) && m_isInCreating)
    {
        m_freeItem->upWhenCreating(mapToScene(event->pos()));
    }

//    if(!endCreated)
        QGraphicsView::mouseReleaseEvent(event);
}

void MyGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if((scene()->items().contains(m_freeItem)) && m_isInCreating)
    {
        m_freeItem->moveWhenCreating(mapToScene(event->pos()));
    }

//    if(!endCreated)
        QGraphicsView::mouseMoveEvent(event);
}
