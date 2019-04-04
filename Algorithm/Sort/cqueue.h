#ifndef CQUEUE_H
#define CQUEUE_H
///
/// \brief The CQueue class
///使用栈来实现队列
#include <QStack>

template <typename T>
class CQueue
{
public:
    CQueue(){}

//    void appendTail(const T &t);
//    T popHead();

    void appendTail(const T& t)
    {
        s1.push_back(t);
    }

    T popHead()
    {
        T t;
        if(s2.isEmpty())
        {
            while(!s1.isEmpty())
            {
                T t = s1.pop();
                s2.push(t);
            }
            t = s2.pop();
        }
        else
        {
            t = s2.pop();
        }
        return t;
    }

private:
    QStack<T> s1;
    QStack<T> s2;
};

#endif // CQUEUE_H
