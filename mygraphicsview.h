#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H
#include <QGraphicsView>
#include <QWidget>
#include <QMouseEvent>
#include "FreeDrawingItem/freedrawingitem.h"

class MyGraphicsView : public QGraphicsView
{
public:
    MyGraphicsView(QWidget *parent = nullptr);
protected:
    virtual void mousePressEvent(QMouseEvent * event)  override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

private:
    FreeDrawingItem * m_freeItem = nullptr;

};

#endif // MYGRAPHICSVIEW_H
