#ifndef HHCOMMANDFREEDRAWINGITEMCHANGE_H
#define HHCOMMANDFREEDRAWINGITEMCHANGE_H
//#include "hhcommand"
#include "FreeDrawingItem/freedrawingitem.h"
#include "FreeDrawingItem/anchorpointinfo.h"
#include <QVector>

class HHCommandFreeDrawingItemChange /*: public HHCommand*/
{
public:
    HHCommandFreeDrawingItemChange(FreeDrawingItem *item,QVector<AnchorPointInfo> oldInfos);
    ~HHCommandFreeDrawingItemChange();

    virtual void execute()/* override*/;
    virtual void undo() /*override*/;
    virtual void redo() /*override*/;
protected:
    QVector<AnchorPointInfo> m_vecOldInfo;
    QVector<AnchorPointInfo> m_vecNewInfo;
    FreeDrawingItem*  m_pFreeItem;
};

#endif // HHCOMMANDFREEDRAWINGITEMCHANGE_H
