#ifndef IMAINWIDGET_H
#define IMAINWIDGET_H

#include <QWidget>

class IMainWidget : public QWidget
{
    Q_OBJECT

public:
    IMainWidget(QWidget *parent = nullptr);
    ~IMainWidget();
};
#endif // IMAINWIDGET_H
