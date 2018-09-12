#ifndef ANCHORPOINTITEM_H
#define ANCHORPOINTITEM_H
#include "customitem.h"
#include <QPen>
#include <QGraphicsSceneEvent>
#include <QGraphicsSceneMouseEvent>
#include "anchorpointinfo.h"
#include "controlpointitem.h"
#include "controllineitem.h"

class FreeDrawingItem;

class AnchorPointItem : public CustomItem
{
    friend class ControlPointItem;
public:
    AnchorPointItem(QGraphicsItem *parent = nullptr);

    virtual ~AnchorPointItem();

    void deleteCtrl();

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;

    const  AnchorPointInfo & getPointInfo()  const { return m_info;}

    void setPointInfo(const AnchorPointInfo &info,bool needUpdate = true);

    void setFreeDrawingItem(FreeDrawingItem * item);

//    void setAnchorPos(QPointF pos);

    void setCtrlVisible(bool visible);

    void setState(int state);

    // update the point and  line property by info
    void updatePropertyByInfo();

    // update info by controlpoint pos
    void updateInfoByPos(const QString &type);

protected:
    // record Editing state
    void startEditingAnchor();
    void endEditingAnchor();

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

    FreeDrawingItem * m_DrawingItem = nullptr;

    QPointF m_downPoint;
};

#endif // ANCHORPOINTITEM_H
