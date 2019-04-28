#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <qprogressbar.h>
#include <QTimeLine>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result) override;

private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    int m_shadowSize = 5;
    QPoint m_offset = QPoint();

    QTimeLine * m_timeLine = nullptr;
    QProgressBar * m_bar = nullptr;
};

#endif // WIDGET_H
