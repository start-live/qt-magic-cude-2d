#ifndef ISCENEWIDGETUI_H
#define ISCENEWIDGETUI_H

#include "iabstractwidgetui.h"

class IBoardWidget;
class QPushButton;

class ISceneWidgetUi : public IAbstractWidgetUi
{
public:
    ISceneWidgetUi();
    virtual ~ISceneWidgetUi();

protected:
    virtual bool instance(QWidget *pWidget) override;
    virtual bool retranslateUi(QWidget *pWidget) override;
    void layout(QWidget *pWidget) override;
    virtual bool connect(QWidget *pWidget) override;
    virtual void objectNameSetting(QWidget *pWidget) override;
    virtual bool decorate(QWidget *pWidget) override;
    virtual void release() override;

protected:
    QVBoxLayout* m_pMainLayout;
    IBoardWidget* m_pBoardWidget;
    QHBoxLayout* m_pButtonLayout;
    QSpacerItem* m_pLeftHorizontalSpacer;
    QPushButton* m_pUpButton;
    QPushButton* m_pDownButton;
    QPushButton* m_pLeftButton;
    QPushButton* m_pRightButton;
    QSpacerItem* m_pRightHorizontalSpacer;
};

#endif // ISCENEWIDGETUI_H
