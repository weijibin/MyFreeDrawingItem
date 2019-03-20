#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <stdio.h>
#include <QStack>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_vec.append(3);
    m_vec.append(-4);
    m_vec.append(2);
    m_vec.append(2);
    m_vec.append(1);
    m_vec.append(7);

//    qDebug()<<"before:::"<<m_vec;

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

//    bucketSort(m_vec);

//    radixSort(m_vec);

//    quickSortMy(m_vec,0,size-1);

//    qDebug()<<"after:::"<<m_vec;

//    int ele = 2;
//    qDebug()<<"find Element "<<ele<<"==="<<binarySearch(m_vec,ele);

//    QVector<int> vec = {1,1,2,3,3,4,4};
//     qDebug()<<"before:::"<<vec;
//    qDebug()<<singleNonDuplicate(vec);

//    QVector<int> vec1 = {1,3};
//    QVector<int> vec2 = {2,4};
//    qDebug()<<findMedianSortedArrays(vec1,vec2);

    initTree(m_root);
//    preOrder(m_root);
//    preOrderNonRecursive(m_root);

//    inOrder(m_root);
//    inOrderNonRecursive(m_root);

//    postOrder(m_root);
    postOrderNonRecursive(m_root);

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

int Widget::singleNonDuplicate(QVector<int> &nums)
{
    int size = nums.size();
    int low = 0;
    int height = size-1;
    int mid = (low+height)/2;
    while(mid>low && mid<height)
    {
        bool isL = nums[mid] == nums[mid-1] ;
        bool isR = nums[mid] == nums[mid+1] ;
        if(!isL && !isR)
        {
            return nums[mid];
        }
        if(isL)
        {
            if((mid-low)%2)
            {
                low = mid+1;
            }
            else
            {
                height= mid;
            }
        }
        if(isR)
        {
            if((height-mid)%2)
            {
                height = mid -1;
            }
            else
            {
                low = mid;
            }
        }
        mid = (low+height)/2;
    }
    return nums[mid];
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


void Widget::quickSortMy(QVector<int> &vec, int low, int height)
{
    if(low > height) return;
    int temp = vec.at(low);
    int i = low;
    int j = height;
    while (i < j)
    {
        while(i<j && vec.at(j)>temp)  //如果标兵在最左，则必须先从右向左遍历
        {
            j--;
        }
        while (i<j && vec.at(i)<=temp)
        {
            i++;
        }
        swap(vec,i,j);
    }

    swap(vec,i,low);

    quickSortMy(vec, low,i-1);
    quickSortMy(vec, i+1,height);
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
    if(vec.length() == 0)
        return;
    int offset = vec.at(0);

    int i = 1;
    while(i<vec.size())
    {
        if(offset >vec.at(i))
            offset = vec.at(i);
        i++;
    }

    for(int i =0; i<vec.size(); i++)   //全部转换为非负数 来进行排序
    {
        vec[i] -= offset;
    }

    int minValue = vec.at(0);
    int maxValue = vec.at(0);
    for(int i = 1; i<vec.size(); i++)
    {
        if(maxValue < vec.at(i))
            maxValue = vec.at(i);
        if(minValue > vec.at(i))
            minValue = vec.at(i);
    }

    int times = getAllDigit(minValue) < getAllDigit(maxValue)? getAllDigit(maxValue):getAllDigit(minValue);

    QVector<QVector<int>> radixs(10);  //0,1,2,3,4,5,6,7,8,9

    for(int i =1; i<times+1; i++)
    {
        for(int j =0; j<vec.size(); j++)
        {
            int id = getDigit(vec.at(j),i);
            radixs[id].append(vec.at(j));
        }
        int index = 0;
        for(int m = 0; m<radixs.size(); m++)
        {
            int count = radixs.at(m).size();
            for(int n= 0; n<count; n++)
            {
                vec[index] = radixs.at(m).at(n);
                index++;
            }
            radixs[m].clear();
        }
    }

    for(int i =0; i<vec.size(); i++)
    {
        vec[i] += offset;
    }
}

int Widget::getDigit(int num, int d)//1:个位，2:十位 依次类推
{
    int ret;
    while(d--)
    {
        ret = num%10;
        num /=10;
    }
    return ret;
}

int Widget::getAllDigit(int num) //num 为几位数
{
    int temp = qAbs(num);
    int c = 1;
    while ((temp /= 10) && temp != 0)
    {
        c++;
    }
    return c;
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

int Widget::binarySearch(QVector<int> vec, int key)
{
    int low = 0;
    int height = vec.size()-1;
    int mid;
    int ret = -1;
    while (low<=height)
    {
        mid = (low+height)/2;
        if(vec.at(mid) <  key)
        {
            low = mid+1;
        }
        else if(vec.at(mid) > key)
        {
            height = mid-1;
        }
        else
        {
            ret = mid;
            break;
        }
    }

    return ret;

}

double Widget::findMedianSortedArrays(QVector<int>& nums1, QVector<int>& nums2) {

        double ret = 0.0;

        int size1 = nums1.size();
        int size2 = nums2.size();
        int i =0,j=0;
        std::vector<int> nums;
        while(i<size1 && j<size2)
        {
            if(nums1[i]<nums2[j])
            {
                nums.push_back(nums1[i]);
                i++;
            }
            else
            {
                nums.push_back(nums2[j]);
                j++;
            }
        }

        while(i<size1)
        {
            nums.push_back(nums1[i]);
            i++;
        }
        while(j<size2)
        {
            nums.push_back(nums2[j]);
            j++;
        }

        int size = size1+size2;
        if(size%2)
        {
            ret = nums[size/2];
        }
        else
        {
            double sum = nums[size/2] + nums[(size-1)/2];
//            int sum = nums[size/2] + nums[(size-1)/2];
            ret = sum/2;
        }

        return ret;
    }


void Widget::preOrder(Node *root)
{
    if(root == nullptr)
        return;

    qDebug()<<root->data;
    if(root->left)
        preOrder(root->left);
    if(root->right)
        preOrder(root->right);
}

void Widget::inOrder(Node *root)
{
    if(root == nullptr)
        return;

    if(root->left)
        inOrder(root->left);
    qDebug()<<root->data;
    if(root->right)
        inOrder(root->right);
}

void Widget::postOrder(Node *root)
{
    if(root == nullptr)
        return;

    if(root->left)
        postOrder(root->left);
    if(root->right)
        postOrder(root->right);
    qDebug()<<root->data;
}


void Widget::preOrderNonRecursive(Node *root)
{
    if(root == nullptr)
        return;

    QStack<Node*> stack;
    Node *cur = root;

    while(cur!=nullptr || !stack.isEmpty())
    {
        while(cur!=nullptr)
        {
            stack.push(cur);
            qDebug()<<cur->data;
            cur = cur->left;
        }

        if(!stack.isEmpty())
        {
            Node *t = stack.pop();
            cur = t->right;
        }
    }
}

void Widget::inOrderNonRecursive(Node *root)
{
    if(root == nullptr)
        return;

    QStack<Node*> stack;
    Node * cur = root;

    while(cur!=nullptr || !stack.isEmpty())
    {
        while(cur!=nullptr)
        {
            stack.push(cur);
            cur  = cur->left;
        }

        if(!stack.isEmpty())
        {
            Node* t = stack.pop();
            qDebug()<<t->data;
            cur = t->right;
        }
    }
}

void Widget::postOrderNonRecursive(Node *root)
{
    if(root == nullptr)
        return;

    QStack<Node*> stack;
    Node *cur = root;
    Node *lastPop = nullptr;

    while(cur!=nullptr || !stack.isEmpty())
    {
        while(cur!=nullptr)
        {
            stack.push(cur);
            cur= cur->left;
        }
        if(!stack.isEmpty())
        {
            Node * t = stack.top();
            if(t->right == nullptr || t->right == lastPop)
            {
                qDebug()<<t->data;
                t = stack.pop();
                lastPop = t;
                cur = nullptr;
            }
            else
            {
                cur = t->right;
            }
        }
    }

}

void Widget::initTree(Node * &root)
{
    if(root == nullptr)
    {
        root = new Node;
        root->data =1;

        root->left = new Node;
        root->left->data = 2;

        root->right = new Node;
        root->right->data = 3;

        root->left->right = new Node;
        root->left->right->data = 4;
    }
}

void Widget::deleteTree(Node *root)
{
    if(root != nullptr)
    {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
        root = nullptr;
    }
}
