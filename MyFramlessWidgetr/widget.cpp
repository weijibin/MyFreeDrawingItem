#include "widget.h"
#include "ui_widget.h"
#include "windowsx.h"
#include "windows.h"
#include "WinUser.h"
#include <QMouseEvent>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);


    m_timeLine = new QTimeLine(2000,this);
    m_timeLine->setFrameRange(0,100);

    m_bar = new QProgressBar(this);
    m_bar->setRange(0,100);
    this->layout()->addWidget(m_bar);

    connect(m_timeLine,SIGNAL(frameChanged(int)),m_bar,SLOT(setValue(int)));

    connect(m_timeLine,&QTimeLine::frameChanged,[=](int value){
        qDebug()<<"frameChanged<<<<"<<value;
    });

}

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        m_offset = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        move(event->globalPos() - m_offset);
        event->accept();
    }
}

bool Widget::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    if (this->minimumHeight() >= this->maximumHeight()
            && this->minimumWidth() >= this->maximumWidth())
    {
        return QWidget::nativeEvent(eventType, message, result);
    }

    Q_UNUSED(eventType)

    MSG *param = static_cast<MSG*>(message);

    switch (param->message)
    {
        case WM_NCHITTEST:
        {
            HWND hWnd = (HWND)this->winId();
            int nX = GET_X_LPARAM(param->lParam) - this->geometry().x();
            int nY = GET_Y_LPARAM(param->lParam) - this->geometry().y();
            // //指定标题栏区域
            // if (this->childAt(nX, nY))
            // {
            // return false;
            // }
            // else

            {
                *result = HTCAPTION;
            }


            //如果窗口最大化了，则不支持resize


            if (IsZoomed(hWnd))
                return false;

            if (isMaximized())
                return false;


            if (nX > 0 && nX < this->m_shadowSize)
                *result = HTLEFT;


            if (nX > this->width() - this->m_shadowSize && nX < this->width())
                *result = HTRIGHT;


            if (nY > 0 && nY < this->m_shadowSize)
                *result = HTTOP;


            if (nY > this->height() - this->m_shadowSize && nY < this->height())
                *result = HTBOTTOM;


            if (nX > 0 && nX < this->m_shadowSize && nY > 0 && nY < this->m_shadowSize)
                *result = HTTOPLEFT;


            if (nX > this->width() - this->m_shadowSize && nX < this->width() && nY > 0 && nY < this->m_shadowSize)
                *result = HTTOPRIGHT;


            if (nX > 0 && nX < this->m_shadowSize && nY > this->height() - this->m_shadowSize && nY < this->height())
                *result = HTBOTTOMLEFT;


            if (nX > this->width() - this->m_shadowSize && nX < this->width()
                    && nY > this->height() - this->m_shadowSize && nY < this->height())
                *result = HTBOTTOMRIGHT;



            if(*result == HTCAPTION)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    }
    return false;
}

void Widget::on_pushButton_clicked()
{
    if(m_timeLine)
        m_timeLine->start();
}
