#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_vec.append(3);
    m_vec.append(4);
    m_vec.append(5);
    m_vec.append(2);
    m_vec.append(1);
    m_vec.append(4);

    qDebug()<<"before:::"<<m_vec;

    int size = m_vec.size();
//    quickSort(m_vec,0,size-1);
//    bubbleSort(m_vec,0,size-1);
//    selectSort(m_vec,0,size-1);
//    insertSort(m_vec,0,size-1);
//    mergeSort(m_vec,0,size-1);
    shellSort(m_vec);

    qDebug()<<"after:::"<<m_vec;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::quickSort(QVector<int> &vec, int low, int height)
{
    if(low < height)
    {
        int p = partition(vec,low,height);
        quickSort(vec,low,p-1);
        quickSort(vec,p+1, height);
    }
}

int Widget::partition(QVector<int> &vec, int low, int height)
{
    int i = low-1;
    int key = vec.at(height);
    for(int j=low; j<height-1; j++)
    {
        if(vec[j]<= key)
        {
            i++;

            int temp = vec[i];
            vec[i] = vec[j];
            vec[j] = temp;
        }
    }
    int temp = vec[i+1];
    vec[i+1] = vec[height];
    vec[height] = temp;
    return i+1;
}



void Widget::bubbleSort(QVector<int> &vec, int low, int height)
{
    for(int i = low; i < height; i++)
    {
        for(int j = low; j< height-i; j++)
        {
            if(vec[j] > vec[j+1])
            {
                int temp = vec[j+1];
                vec[j+1] = vec[j];
                vec[j] = temp;
            }
        }
    }
}

void Widget::selectSort(QVector<int> &vec, int low, int height)
{
    for(int i = low; i<height; i++)
    {
        int minIndex = i;
        for(int j = i; j < height+1; j++)
        {
            if(vec[minIndex] > vec[j])
            {
                minIndex = j;
            }
        }

        int temp = vec[minIndex];
        vec[minIndex] = vec[i];
        vec[i] = temp;

    }
}

void Widget::insertSort(QVector<int> &vec, int low, int height)
{
    for(int i = low+1; i< height+1; i++)
    {
        int current = vec[i];
        int preIndex = i-1;
        while(preIndex >= 0 && vec[preIndex] > current)
        {
            vec[preIndex+1] = vec[preIndex];
            preIndex--;
        }

        vec[preIndex + 1] = current;
    }
}

//堆排序
void Widget::heapSort(QVector<int> &vec)
{

}

//希尔排序
void Widget::shellSort(QVector<int>&vec)
{
    int size = vec.size();
    for(int gap=size/2; gap>0; gap/=2)
    {
        for(int i = gap; i< size; i += 1)
        {

            int inserted = vec[i];
            int j;
            for(j = i-gap; j>=0&&inserted<vec[j]; j-=gap)
            {
                vec[j+gap] = vec[j];
            }
            vec[j+gap] = inserted;

//            {
//                for(int j = i; j<size; j+=gap)
//                {
//                    int current = vec[j];
//                    int preIndex = j-gap;

//                    while(preIndex>=0 && current < vec[preIndex])
//                    {
//                        vec[preIndex+gap] = vec[preIndex];

//                        preIndex = preIndex - gap;
//                    }

//                    vec[preIndex+gap] = current;

//                }
//            }
        }
    }
}

//归并排序
void Widget::mergeSort(QVector<int> &vec, int low, int height)
{
    int n = (low+height)/2;
    if(n>low)
        mergeSort(vec,low,n);
    if(height>(n+1))
        mergeSort(vec,n+1,height);

    merge(vec,low,n,height);
}

void Widget::merge(QVector<int> &vec, int l, int m, int h)
{
    QVector<int> tmp1;
    for(int i = l; i< m+1; i++)
    {
        tmp1.append(vec.at(i));
    }

    QVector<int> tmp2;
    for(int i = m+1; i<h+1; i++)
    {
        tmp2.append(vec.at(i));
    }

    int size1 = tmp1.size();
    int size2 = tmp2.size();

    int i1 = 0;
    int i2 = 0;
    while( i1<size1 && i2<size2)
    {
        if(tmp1.at(i1) < tmp2.at(i2))
        {
            vec[l+i1+i2] = tmp1.at(i1);
            i1++;
        }
        else
        {
            vec[l+i1+i2] = tmp2.at(i2);
            i2++;
        }
    }

    while(i1<size1)
    {
        vec[l+i1+i2] = tmp1.at(i1);
        i1++;
    }
    while(i2<size2)
    {
        vec[l+i1+i2] = tmp2.at(i2);
        i2++;
    }
}








//基数排序
void Widget::radixSort(QVector<int> &vec)
{

}

//桶排序
void Widget::bucketSort(QVector<int> &vec)
{

}

