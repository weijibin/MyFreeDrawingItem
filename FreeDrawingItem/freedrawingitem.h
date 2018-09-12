#ifndef FREEDRAWINGITEM_H
#define FREEDRAWINGITEM_H

#include <QGraphicsItem>
#include <QPointF>
#include "anchorpointinfo.h"
#include "anchorpointitem.h"

class FreeDrawingItem: public QGraphicsItem
{
    friend class AnchorPointItem;
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

    // get and set infos
    void setAnchorInfos(QVector<AnchorPointInfo> infos);
    QVector<AnchorPointInfo> getAnchorInfos();

protected:
    // change subpath
    void changePathByItem(AnchorPointItem* item,QString type = "");
    // anchor controlPoint show hide setting
    void editingTheAnchorItem(AnchorPointItem * item);

    // record Editing state
    void startEditing();
    void endEditing();

    // editing
    void downWhenEditing(QPointF point);
    void moveWhenEditing(QPointF point);
    void upWhenEditing(QPointF point);

    void updateBoundingRect();
    void synchronizeAnchorInfo();
    QPainterPath generatePathByInfo(const AnchorPointInfo & first, const AnchorPointInfo & second);

private:

    QRectF m_boundingRect;

    //sub paths;
    QVector<QPainterPath> m_subPaths;

    // anchor info
    QVector<AnchorPointItem *> m_AnchorPointItems;

    bool m_isPressed = false;
    QPointF m_downPoint;

    // infos
    QVector<AnchorPointInfo> m_startInfos;
};

#endif // FREEDRAWINGITEM_H
