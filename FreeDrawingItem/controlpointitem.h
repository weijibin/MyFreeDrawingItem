#ifndef CONTROLPOINTITEM_H
#define CONTROLPOINTITEM_H
#include "customitem.h"

class AnchorPointItem;

class ControlPointItem : public CustomItem
{
public:
    ControlPointItem(QGraphicsItem *parent = nullptr);

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;

    void setPointItem(AnchorPointItem *item){ m_pointItem = item;}

    void setPosType(QString type) { m_type = type;}

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    qreal m_radius;
    AnchorPointItem * m_pointItem=nullptr;
    QString m_type;

    QPointF m_downPoint;
};

#endif // CONTROLPOINTITEM_H
