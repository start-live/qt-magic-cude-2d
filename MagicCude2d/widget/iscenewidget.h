#ifndef ISCENEWIDGET_H
#define ISCENEWIDGET_H

#include <QtWidgets/qwidget.h>

#include "ui/iscenewidgetui.h"

class ISceneWidget
        : public QWidget
        , public ISceneWidgetUi
{
    Q_OBJECT
public:
    explicit ISceneWidget(QWidget *parent = nullptr);

signals:

private slots:
    void onUpButtonClicked();
    void onDownButtonClicked();
    void onLeftButtonClicked();
    void onRightButtonClicked();

private:

};

#endif // ISCENEWIDGET_H
