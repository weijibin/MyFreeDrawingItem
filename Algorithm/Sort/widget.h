#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVector>
#include <map>
#include <string>
using namespace std;

namespace Ui {
class Widget;
}

struct Node
{
    int data;
    struct Node *left = nullptr;
    struct Node *right = nullptr;
} ;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();


    //测试map 属性
    void testMap();

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

    //二分查找
    int binarySearch(QVector<int> vec, int key);

    ///
    /// \brief singleNonDuplicate
    /// \param nums
    /// \return
    ///给定一个只包含整数的有序数组，每个元素都会出现两次，唯有一个数只会出现一次，找出这个数。
    ///示例 1:
    ///输入: [1,1,2,3,3,4,4,8,8]
    ///输出: 2
    ///示例 2:
    ///输入: [3,3,7,7,10,11,11]
    ///输出: 10
    ///注意: 您的方案应该在 O(log n)时间复杂度和 O(1)空间复杂度中运行。
    ///
    ///
    int singleNonDuplicate(QVector<int>& nums);

    ///
    /// \brief findMedianSortedArrays
    /// \param nums1
    /// \param nums2
    /// \return
    ///
    ///给定两个大小为 m 和 n 的有序数组 nums1 和 nums2。
    /// 请你找出这两个有序数组的中位数，并且要求算法的时间复杂度为 O(log(m + n))。
    /// 你可以假设 nums1 和 nums2 不会同时为空。
    /// 示例 1:
    /// nums1 = [1, 3]
    /// nums2 = [2]

    /// 则中位数是 2.0
    /// 示例 2:

    /// nums1 = [1, 2]
    /// nums2 = [3, 4]
    /// 则中位数是 (2 + 3)/2 = 2.5
    ///
    double findMedianSortedArrays(QVector<int>&nums1,QVector<int>&nums2);

    ///
    /// \brief 二叉树的遍历
    /// 递归与非递归的遍历
    ///
    void preOrder(Node*root);
    void inOrder(Node*root);
    void postOrder(Node*root);
    void preOrderNonRecursive(Node*root);
    void inOrderNonRecursive(Node*root);
    void postOrderNonRecursive(Node*root);

    void initTree(Node * &root); //指针的引用
    void deleteTree(Node * root);

signals:
    void test(int );
public slots:
    void sltTest(int);
private:
    QVector<int> m_vec;

    Node*m_root = nullptr;
private:
    Ui::Widget *ui;

};

#endif // WIDGET_H
