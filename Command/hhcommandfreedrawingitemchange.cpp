#include "hhcommandfreedrawingitemchange.h"

HHCommandFreeDrawingItemChange::HHCommandFreeDrawingItemChange(FreeDrawingItem *item,QVector<AnchorPointInfo> oldInfos)
{
    m_pFreeItem = item;
    m_vecOldInfo = oldInfos;
    m_vecNewInfo = m_pFreeItem->getAnchorInfos();
}

HHCommandFreeDrawingItemChange::~HHCommandFreeDrawingItemChange()
{

}

void HHCommandFreeDrawingItemChange::execute()
{

}

void HHCommandFreeDrawingItemChange::redo()
{
    m_pFreeItem->setAnchorInfos(m_vecNewInfo);
}

void HHCommandFreeDrawingItemChange::undo()
{
    m_pFreeItem->setAnchorInfos(m_vecOldInfo);
}
