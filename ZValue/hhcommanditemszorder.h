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
	// ����
	void uperLayer();

	// �ö�
	void topLayer();

	// �õ�
	void bottomLayer();

	// ����
	void lowerLayer();

    void saveUpperItems();
    void restoreFromUpperItems();


    QGraphicsItem * getLowerItem(QGraphicsItem *item);
    QGraphicsItem * getUperItem(QGraphicsItem  *item);

    bool isItemInSelections(QGraphicsItem  *item);

    QVector<IHHPrimitiveItem *> sortItems(QVector< IHHPrimitiveItem* > items);

private:
	HHSlide *m_pSlide;
	// Z������
	// ���ƣ�m_strType == "ID_HH_ITEM_EDIT_ZORDER_PRE"
	// ���ƣ�m_strType == "ID_HH_ITEM_EDIT_ZORDER_NEXT"
	// �ö���m_strType == "ID_HH_ITEM_EDIT_ZORDER_TOP"
	// �õף�m_strType == "ID_HH_ITEM_EDIT_ZORDER_BOTTOM"
	QString  m_strType;

	// Ҫ����Z���Item
    QVector< IHHPrimitiveItem* > m_items;

    QVector< QGraphicsItem* >  m_refItems;

public:
    virtual void execute();
    virtual void undo();
    virtual void redo();
};

#endif // HHCOMMANDITEMSZORDER_H
