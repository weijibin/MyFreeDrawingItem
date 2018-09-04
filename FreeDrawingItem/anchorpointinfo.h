#ifndef ANCHORPOINTINFO_H
#define ANCHORPOINTINFO_H

#include <QPointF>

class AnchorPointInfo
{
public:
    //data
    QPointF anchorPoint = QPointF();  //
    QPointF pre_CtrlPoint = QPointF(-10000,-10000); //  默认值为无效值
    QPointF post_CtrlPoint = QPointF(-10000,-10000); //

    //property
    int state = 0; // 0,1
};

#endif // ANCHORPOINTINFO_H
