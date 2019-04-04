#include "hhcommanditemszorder.h"
#include "hhslide.h"
#include "hhtoolhelper.h"
#include "hhpresentation.h"
#include <QGraphicsItem>

HHCommandItemsZOrder::HHCommandItemsZOrder( HHSlide *slide, QVector< IHHPrimitiveItem* > selections, QString type ) 
{
    m_pSlide = slide;
    m_strType = type;
	// 要调整Z序的Item
    m_items = sortItems(selections);  // 得到降序的items
}

HHCommandItemsZOrder::~HHCommandItemsZOrder() {

}

QVector<IHHPrimitiveItem*> HHCommandItemsZOrder::sortItems(QVector< IHHPrimitiveItem* > selections)
{
    QVector<IHHPrimitiveItem*> retList;

    QList< QGraphicsItem* > items = m_pSlide->getTopQItems( false );
    for(int i = 0; i <items.size(); i++)
    {
        for(int j = 0; j < selections.size(); j++)
        {
            QGraphicsItem * currentItem = qobject_cast< QGraphicsItem* >(selections.at(j)->getObject());
            if(items.at(i) == currentItem)
            {
                retList.append(selections.at(j));
            }
        }
    }

    return retList;
}


void HHCommandItemsZOrder::saveUpperItems()
{
    m_refItems.clear();
    QList< QGraphicsItem* > items = m_pSlide->getTopQItems( false );
    for(int i = 0; i < m_items.size(); i++)
    {
        QGraphicsItem * currentItem = qobject_cast< QGraphicsItem* >(m_items[i]->getObject());
        for(int j = 0; j < items.size(); j++)
        {
            if(currentItem == items.at(j))
            {
                if(j == 0)
                    m_refItems.push_back(NULL);
                else
                    m_refItems.push_back(items.at(j-1));
            }
        }
    }
}

void HHCommandItemsZOrder::restoreFromUpperItems()
{
    for (int i = 0; i < m_items.size(); i++) {
        QGraphicsItem* graphicsItem = qobject_cast< QGraphicsItem* >(m_items.at(i)->getObject());
        m_pSlide->removeItem(graphicsItem);
        m_pSlide->addItem(graphicsItem);
        if (m_refItems[i])
            graphicsItem->stackBefore(m_refItems[i]);
    }
    m_pSlide->update();
}

QGraphicsItem * HHCommandItemsZOrder::getLowerItem(QGraphicsItem *item)
{
    QGraphicsItem * ret  = NULL;
    QList< QGraphicsItem* > items = m_pSlide->getTopQItems( false );
    int count = items.size();
    for(int j = 0; j < count; j++)
    {
        if(item == items.at(j))
        {
            if(j < count - 1)
                ret = items.at(j + 1);
             break;
        }
    }
    return ret;
}

QGraphicsItem * HHCommandItemsZOrder::getUperItem(QGraphicsItem *item)
{
    QGraphicsItem * ret  = NULL;
    QList< QGraphicsItem* > items = m_pSlide->getTopQItems( false );

    int count = items.size();
    for(int j = 0; j < count; j++)
    {
        if(item == items.at(j))
        {
            if(j > 0)
                ret = items.at(j - 1);
             break;
        }
    }
    return ret;
}



// 置于底层  
void HHCommandItemsZOrder::bottomLayer()
{
    saveUpperItems();  // 获取当前选中item的 stackorder

    for(int i=0; i < m_items.size(); i++)
    {
        QList< QGraphicsItem* > items = m_pSlide->getTopQItems( false );

        for(int j = 0; j < items.size(); j++)
        {
            QGraphicsItem *item = items.at(j);

            QGraphicsItem* qItem = qobject_cast< QGraphicsItem* >(m_items[i]->getObject());
            qItem->stackBefore(item);

        }
    }

	m_pSlide->update();
}

// 置于顶层  
void HHCommandItemsZOrder::topLayer()
{
    saveUpperItems();  // 获取当前选中item的 stackorder

    for(int i = m_items.size()-1; i > -1; i--)
    {
        QList< QGraphicsItem* > items = m_pSlide->getTopQItems( false );

        for(int j = items.size() - 1; j > -1; j--)  // 保证不改变原来的顺序
        {
            QGraphicsItem *item = items.at(j);
            {
                QGraphicsItem* qItem = qobject_cast< QGraphicsItem* >(m_items[i]->getObject());
                item->stackBefore(qItem);
            }
        }
    }

    m_pSlide->update();
}

// 上移一层  
void HHCommandItemsZOrder::uperLayer()
{
    saveUpperItems();
    for(int i = 0; i<m_items.size(); i++)
    {
        QGraphicsItem* qItem = qobject_cast< QGraphicsItem* >(m_items[i]->getObject());
        QGraphicsItem * uperItem = getUperItem(qItem);
        if(uperItem)
        {
            if(!isItemInSelections(uperItem))
                uperItem->stackBefore(qItem);
        }
    }
    m_pSlide->update();
}

// 下移一层  
void HHCommandItemsZOrder::lowerLayer()
{
    saveUpperItems();
    for(int i = m_items.size()-1 ; i > -1; i--)
    {
        QGraphicsItem* qItem = qobject_cast< QGraphicsItem* >(m_items[i]->getObject());
        QGraphicsItem * lowerItem = getLowerItem(qItem);
        if(lowerItem)
        {
            if(!isItemInSelections(lowerItem))
                qItem->stackBefore(lowerItem);
        }
    }
    m_pSlide->update();
}

bool HHCommandItemsZOrder::isItemInSelections(QGraphicsItem *item)
{
    bool isContains = false;

    for(int i = 0; i< m_items.size(); i++)
    {
        QGraphicsItem* qItem = qobject_cast< QGraphicsItem* >(m_items[i]->getObject());
        if(qItem == item)
        {
            isContains = true;
            break;
        }
    }
    return isContains;
}

//
void HHCommandItemsZOrder::execute() 
{
    if (m_strType == "ID_HH_ITEM_EDIT_ZORDER_TOP")
    {
		topLayer();
    }
    if (m_strType == "ID_HH_ITEM_EDIT_ZORDER_PRE")
    {
		uperLayer();
    }
    if (m_strType == "ID_HH_ITEM_EDIT_ZORDER_BOTTOM")
    {
		bottomLayer();
	}
    if (m_strType == "ID_HH_ITEM_EDIT_ZORDER_NEXT")
    {
		lowerLayer();
	}
}

void HHCommandItemsZOrder::undo() 
{
    restoreFromUpperItems();
}

void HHCommandItemsZOrder::redo() 
{
    execute();
}
