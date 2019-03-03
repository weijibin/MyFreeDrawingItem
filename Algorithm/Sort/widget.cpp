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
    insertSort(m_vec,0,size-1);

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



