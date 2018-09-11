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
    int state = 0; // 0,1   creating: 0 ,  editing:1

    bool pre_Relation = false;  // 控制点 前相关
    bool post_Relation = false; // 控制点 后相关

    bool isSymmetrical = false;
};

#endif // ANCHORPOINTINFO_H
