#ifndef HHCOMMANDITEMSZORDER_H
#define HHCOMMANDITEMSZORDER_H

#include "hhcommand.h"

//
class QGraphicsItem;
class IHHPrimitiveItem;
class HHCommandItemsZOrder : public HHCommand
{
public:
    HHCommandItemsZOrder( HHSlide *slide, QVector< IHHPrimitiveItem* > selections, QString type );
    virtual ~HHCommandItemsZOrder();

private:
	// 上移
	void uperLayer();

	// 置顶
	void topLayer();

	// 置底
	void bottomLayer();

	// 下移
	void lowerLayer();

    void saveUpperItems();
    void restoreFromUpperItems();


    QGraphicsItem * getLowerItem(QGraphicsItem *item);
    QGraphicsItem * getUperItem(QGraphicsItem  *item);

    bool isItemInSelections(QGraphicsItem  *item);

    QVector<IHHPrimitiveItem *> sortItems(QVector< IHHPrimitiveItem* > items);

private:
	HHSlide *m_pSlide;
	// Z序类型
	// 上移：m_strType == "ID_HH_ITEM_EDIT_ZORDER_PRE"
	// 下移：m_strType == "ID_HH_ITEM_EDIT_ZORDER_NEXT"
	// 置顶：m_strType == "ID_HH_ITEM_EDIT_ZORDER_TOP"
	// 置底：m_strType == "ID_HH_ITEM_EDIT_ZORDER_BOTTOM"
	QString  m_strType;

	// 要调整Z序的Item
    QVector< IHHPrimitiveItem* > m_items;

    QVector< QGraphicsItem* >  m_refItems;

public:
    virtual void execute();
    virtual void undo();
    virtual void redo();
};

#endif // HHCOMMANDITEMSZORDER_H
