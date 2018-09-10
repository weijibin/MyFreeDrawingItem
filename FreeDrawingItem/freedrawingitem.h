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
    QPainterPath getPath();

    // show   hide
    void show(){setVisible(true);}
    void hide(){setVisible(false);}

    // clone
    FreeDrawingItem * clone();

    // start create
    void startCreate(QPointF point);
    // creating
    void downWhenCreating(QPointF point);
    void moveWhenCreating(QPointF point);
    void upWhenCreating(QPointF point);
    // end creating
    void endCreate();

    void changePathByItem(AnchorPointItem* item);

    // translate item  or  call in command
    void translateItem(QPointF offset);

    // add command notify outside
    void addCommandToSlide(/*HHCommand * command*/){}

    // move the end anchor point  notify outside
    void moveShadow(QPointF offset){}

    // save
    void getJSONObj( QJsonObject& jsonObj );
    // restore
    void fromJSONObj(QJsonObject& jsonObj );

protected:
    // editing
    void downWhenEditing(QPointF point);
    void moveWhenEditing(QPointF point);
    void upWhenEditing(QPointF point);

    void updateBoundingRect();

    void synchronizeAnchorInfo();

    QPainterPath generatePathByInfo(const AnchorPointInfo & first, const AnchorPointInfo & second);

private:

    QRectF m_boundingRect;

//    QPainterPath m_path;

    QVector<QPainterPath> m_subPaths;
    // sub paths
//    QVector<QGraphicsPathItem> m_subPathItems;

//    QVector<AnchorPointInfo> m_AnchorPoints;

    // anchor info
    QVector<AnchorPointItem *> m_AnchorPointItems;

    bool m_isPressed = false;
    QPointF m_downPoint;
};

#endif // FREEDRAWINGITEM_H
