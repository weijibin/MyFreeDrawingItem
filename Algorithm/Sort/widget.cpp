#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <stdio.h>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_vec.append(3);
    m_vec.append(4);
    m_vec.append(2);
    m_vec.append(2);
    m_vec.append(1);
    m_vec.append(7);

    qDebug()<<"before:::"<<m_vec;

    int size = m_vec.size();
//    quickSort(m_vec,0,size-1);
//    bubbleSort(m_vec,0,size-1);
//    selectSort(m_vec,0,size-1);
//    insertSort(m_vec,0,size-1);
//    mergeSort(m_vec,0,size-1);
//    heapSort(m_vec);
//    shellSort(m_vec);
//    shellSort1(m_vec);

//    countingSort(m_vec);

    bucketSort(m_vec);

    qDebug()<<"after:::"<<m_vec;

//    {
//        unsigned int a = 0xf7;
//        unsigned char i = (unsigned char)a;
//        char* b = (char*)&a;
//        printf("%08x, %08x\n", i, *b);
//    }
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
    buildBigTree(vec);

    int size = vec.size();

    for(int j = size-1; j > 0; j--)
    {
        swap(vec,0,j);
        adjustBigTree(vec,0,j);
    }
}

void Widget::buildBigTree(QVector<int> &vec)
{
    int size = vec.size();
    int last = size/2 -1;

    for(int i = last; i>-1; i--)
   {
        adjustBigTree(vec,i,size);
   }
}

void Widget::adjustBigTree(QVector<int> &vec, int root,int size)
{
    int left = root*2 + 1;
    int right = root *2 + 2;
    int largest = root;
    if(right<(size) && vec.at(right) > vec.at(largest))
    {
        largest = right;
    }
    if(left<(size) && vec.at(left) > vec.at(largest))
    {
        largest = left;
    }

    if(largest != root)
    {
        swap(vec,root,largest);
        adjustBigTree(vec,largest,size);
    }
}

void Widget::swap(QVector<int> &vec, int a, int b)
{
    int temp = vec.at(a);
    vec[a] = vec[b];
    vec[b] = temp;
}

//希尔排序
void Widget::shellSort(QVector<int>&vec)
{

}
void Widget::shellSort1(QVector<int>&vec)
{
    int size = vec.size();
    for(int gap = size/2; gap>0 ; gap /=2)
    {
        for(int i = gap; i<size; i++)
        {
            int current = vec[i];
            int preIndex = i-gap;
            while(preIndex>=0 && vec.at(preIndex) > current)
            {
                vec[preIndex+gap] = vec[preIndex];
                preIndex -= gap;
            }
            vec[preIndex+gap] = current;
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


//计数排序  整数 ，且支持 负数
void Widget::countingSort(QVector<int> &vec)
{
    int minValue = vec.at(0);
    int maxValue = vec.at(0);
    int i = 1;
    while(i<vec.size())
    {
        if(vec.at(i) < minValue)
            minValue = vec.at(i);
        if(vec.at(i) > maxValue)
            maxValue = vec.at(i);
        i++;
    }

    QVector<int> bucket(maxValue-minValue+1);
    qDebug()<<bucket.size();
    qDebug()<<"Bucket::::"<<bucket;

    int offset = minValue;

    int size = vec.size();
    for(int i = 0; i<size; i++)
    {
//        if(!bucket[vec.at(i)])
//            bucket[vec.at(i)] = 0;   //如果当前索引下value 不为零  则重置为 0
        bucket[vec.at(i) - offset]++;
    }

    int index = 0;
    for(int j = 0; j<bucket.size(); j++)
    {
        int count = bucket.at(j);
        while (count > 0)
        {
            vec[index] = j+offset;
            count --;
            index++;
        }
    }
}

//基数排序
void Widget::radixSort(QVector<int> &vec)
{

}

//桶排序
void Widget::bucketSort(QVector<int> &vec)
{
    if(vec.size() ==0)
        return;
    int minValue = vec.at(0);
    int maxValue = vec.at(0);
    for(int i = 0; i<vec.size(); i++)
    {
        if(minValue > vec.at(i))
            minValue = vec.at(i);
        if(maxValue < vec.at(i))
            maxValue = vec.at(i);
    }


    //分配到各个桶中
    int defaultBucketSize = 5;
    int bucketsCount = (maxValue-minValue)/defaultBucketSize + 1;
    QVector<QVector<int>>buckets(bucketsCount);
    for(int i = 0; i<vec.size(); i++)
    {
        int data = vec.at(i);
        int index = (data-minValue)/defaultBucketSize;
        buckets[index].append(data);
    }

    //每个桶进行插入排序 并 输出
    vec.clear();
    for(int i = 0; i<buckets.size(); i++)
    {
        insertSort(buckets[i],0,buckets[i].size()-1);

        for(int j = 0; j<buckets.at(i).size(); j++)
        {
            vec.append(buckets.at(i).at(j));
        }
    }
}

