#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

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
    bool nativeEvent(const QByteArray &eventType, void *message, long *result) override;

private:
    Ui::Widget *ui;
    int m_shadowSize = 5;
};

#endif // WIDGET_H
