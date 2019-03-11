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

    void quickSortMy(QVector<int> &vec,int low,int height);

    //冒泡排序
    void bubbleSort(QVector<int> &vec,int low, int height);

    //选择排序
    void selectSort(QVector<int> &vec, int low, int height);

    //插入排序
    void insertSort(QVector<int>&vec, int low, int height);

    //堆排序
    void heapSort(QVector<int> &vec);
    void buildBigTree(QVector<int> &vec);

    void adjustBigTree(QVector<int> & vec,int root,int size);

    void swap(QVector<int> &vec, int a, int b);

    //希尔排序
    void shellSort(QVector<int>&vec);
    void shellSort1(QVector<int>&vec);

    //归并排序
    void mergeSort(QVector<int> &vec,int low, int height);
    void merge(QVector<int> &vec, int l,int m, int h);

    //基数排序
    void radixSort(QVector<int> &vec);
    int getDigit(int num,int d);
    int getAllDigit(int num);

    //桶排序
    void bucketSort(QVector<int> &vec);

    //计数排序
    void countingSort(QVector<int> &vec);



private:
    QVector<int> m_vec;
private:
    Ui::Widget *ui;

};

#endif // WIDGET_H
