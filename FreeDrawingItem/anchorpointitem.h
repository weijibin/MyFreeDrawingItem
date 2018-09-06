#ifndef ANCHORPOINTITEM_H
#define ANCHORPOINTITEM_H
#include "customitem.h"
#include <QPen>
#include <QGraphicsSceneEvent>
#include <QGraphicsSceneMouseEvent>
#include "anchorpointinfo.h"
#include "controlpointitem.h"
#include "controllineitem.h"

class AnchorPointItem : public CustomItem
{
public:
    AnchorPointItem(QGraphicsItem *parent = nullptr);

    virtual ~AnchorPointItem();

    void deleteCtrl();

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;

    const  AnchorPointInfo & getPointInfo()  const { return m_info;}

    void setPointInfo(const AnchorPointInfo &info);

    void setAnchorPos(QPointF pos);

    void setCtrlVisible(bool visible);

    void updatePropertyByInfo();

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QPen m_pen;
    qreal m_radius;

    AnchorPointInfo m_info;

    bool m_isCtrlVisible  = true;

    ControlLineItem &m_preLineItem;
    ControlPointItem &m_preCtrlPtnItem;

    ControlLineItem &m_postLineItem;
    ControlPointItem &m_postCtrlPtnItem;
};

#endif // ANCHORPOINTITEM_H
