#ifndef CSTACK_H
#define CSTACK_H
///
/// \brief The CStack class
///使用队列来实现栈功能
#include <QQueue>

template<typename T>
class CStack
{
public:
    CStack();
    void appendTail(const T& t);
    T popHead();

private:
    QQueue<T> q1;
    QQueue<T> q2;
};

template<typename T>
CStack<T>::CStack()
{

}

template<typename T>
void CStack<T>::appendTail(const T &t)
{
    if(q1.isEmpty())
    {
        q2.push_back(t);
    }
    else
    {
        q1.push_back(t);
    }
}

template<typename T>
T CStack<T>::popHead()
{
    T ret;
    if(q1.isEmpty() && q2.isEmpty())
    {
        return -10000;
    }
    else
    {
        if(q1.isEmpty())
        {
            int num = q2.size();
            while(num>1)
            {
                T t = q2.front();
                q2.pop_front();
                q1.push_back(t);
                num--;
            }

            ret = q2.front();
            q2.pop_front();
        }
        else
        {
            int num = q1.size();
            while(num > 1)
            {
                T t = q1.front();
                q1.pop_front();
                q2.push_back(t);
                num--;
            }

            ret = q1.front();
            q1.pop_front();
        }
    }
    return ret;
}


#endif // CSTACK_H
