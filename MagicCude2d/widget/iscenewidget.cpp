#include "iscenewidget.h"

#include "widget/iboardwidget.h"

ISceneWidget::ISceneWidget(QWidget *parent)
    : QWidget(parent)
    , ISceneWidgetUi()
{
    setupUi(this);
}

void ISceneWidget::onUpButtonClicked()
{
    m_pBoardWidget->turnUp();
}

void ISceneWidget::onDownButtonClicked()
{
    m_pBoardWidget->turnDown();
}

void ISceneWidget::onLeftButtonClicked()
{
    m_pBoardWidget->turnLeft();
}

void ISceneWidget::onRightButtonClicked()
{
    m_pBoardWidget->turnRight();
}
