#ifndef ANCHORPOINTITEM_H
#define ANCHORPOINTITEM_H
#include "customitem.h"
#include <QPen>
#include "anchorpointinfo.h"
#include "controlpointitem.h"
#include "controllineitem.h"

class AnchorPointItem : public CustomItem
{
public:
    AnchorPointItem(QGraphicsItem *parent = nullptr);

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;

    const  AnchorPointInfo & getPointInfo()  const { return m_info;}

    void setPointInfo(const AnchorPointInfo &info);

    void setAnchorPos(QPointF pos);

    void updatePropertyByInfo();
private:
    QPen m_pen;
    qreal m_radius;

    AnchorPointInfo m_info;

    ControlLineItem m_preLineItem;
    ControlPointItem m_preCtrlPtnItem;

    ControlLineItem m_postLineItem;
    ControlPointItem m_postCtrlPtnItem;
};

#endif // ANCHORPOINTITEM_H
