#ifndef CUSTOMITEM_H
#define CUSTOMITEM_H
#include <QGraphicsItem>
#include <QRectF>

class CustomItem : public QGraphicsItem
{
public:
    CustomItem(QGraphicsItem * parent = nullptr);

    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    virtual void setBoundingBox(QRectF rect) { m_boundingBox = rect;}
    virtual QRectF getBoundingBox() const {return m_boundingBox;}

private:
    QRectF m_boundingBox;
};
#endif // CUSTOMITEM_H
