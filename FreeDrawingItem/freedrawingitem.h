#ifndef FREEDRAWINGITEM_H
#define FREEDRAWINGITEM_H

#include <QGraphicsItem>
#include <QPointF>
#include "anchorpointinfo.h"
#include "anchorpointitem.h"

class FreeDrawingItem: public QGraphicsItem
{
public:
    FreeDrawingItem(QGraphicsItem *parent=nullptr);
    FreeDrawingItem(const FreeDrawingItem &item);


    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // path
    QPainterPath getPath(){return QPainterPath();}

    // show   hide
    void show(){setVisible(true);}
    void hide(){setVisible(false);}

    // clone
    FreeDrawingItem * clone();

    // start create
    void startCreate(){}

    // creating
    void downWhenCreating(QPointF point);
    void moveWhenCreating(QPointF point);
    void upWhenCreating(QPointF point);

    // end creating
    void endCreate();

    // editing
    void downWhenEditing(QPointF point);
    void moveWhenEditing(QPointF point);
    void upWhenEditing(QPointF point);

    // translate item  or  call in command
    void translateItem(QPointF offset);

    // add command
//    void addCommandToSlide(HHCommand * command);

    // save
    void getJSONObj( QJsonObject& jsonObj );

    // restore
    void fromJSONObj(QJsonObject& jsonObj );

private:


private:
//    QVector<QPainterPath> m_subPaths;
    QVector<QGraphicsPathItem> m_subPathItems;

//    QVector<AnchorPointInfo> m_AnchorPoints;
    QVector<AnchorPointItem> m_AnchorPointItems;
};

#endif // FREEDRAWINGITEM_H
