#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVector>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    //快速排序
    void quickSort(QVector<int> &vec, int low,int height );
    int partition(QVector<int> &vec, int low,int height);

    //冒泡排序
    void bubbleSort(QVector<int> &vec,int low, int height);

    //选择排序
    void selectSort(QVector<int> &vec, int low, int height);

    //插入排序
    void insertSort(QVector<int>&vec, int low, int height);

    //堆排序
    //希尔排序
    //归并排序
    //基数排序
    //桶排序



private:
    QVector<int> m_vec;
private:
    Ui::Widget *ui;

};

#endif // WIDGET_H
