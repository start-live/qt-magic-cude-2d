#include "iscenewidgetui.h"

#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlayoutitem.h>
#include <QtWidgets/qpushbutton.h>

#include "widget/iboardwidget.h"

ISceneWidgetUi::ISceneWidgetUi()
    : IAbstractWidgetUi()
{
    m_pMainLayout = nullptr;
    m_pBoardWidget = nullptr;
    m_pButtonLayout = nullptr;
    m_pLeftHorizontalSpacer = nullptr;
    m_pUpButton = nullptr;
    m_pDownButton = nullptr;
    m_pLeftButton = nullptr;
    m_pRightButton = nullptr;
    m_pRightHorizontalSpacer = nullptr;
}

ISceneWidgetUi::~ISceneWidgetUi()
{

}

bool ISceneWidgetUi::instance(QWidget *pWidget)
{
    I_INSTANCE(m_pMainLayout, QVBoxLayout, nullptr);
    I_INSTANCE(m_pBoardWidget, IBoardWidget, pWidget);
    I_INSTANCE(m_pButtonLayout, QHBoxLayout, nullptr);

    m_pLeftHorizontalSpacer = new QSpacerItem(40, 20);
    if (m_pLeftHorizontalSpacer == nullptr)
        return false;

    I_INSTANCE(m_pUpButton, QPushButton, pWidget);
    I_INSTANCE(m_pDownButton, QPushButton, pWidget);
    I_INSTANCE(m_pLeftButton, QPushButton, pWidget);
    I_INSTANCE(m_pRightButton, QPushButton, pWidget);

    m_pRightHorizontalSpacer = new QSpacerItem(40, 20);
    if (m_pRightHorizontalSpacer == nullptr)
        return false;

    return  true;
}

bool ISceneWidgetUi::retranslateUi(QWidget *pWidget)
{
    if (m_pMainLayout == nullptr)
        return false;

    m_pUpButton->setText(QObject::tr("up"));
    m_pDownButton->setText(QObject::tr("down"));
    m_pLeftButton->setText(QObject::tr("left"));
    m_pRightButton->setText(QObject::tr("right"));
    pWidget->setWindowTitle(QObject::tr("magic cube"));

    return true;
}

void ISceneWidgetUi::layout(QWidget *pWidget)
{
    m_pButtonLayout->addItem(m_pLeftHorizontalSpacer);
    m_pButtonLayout->addWidget(m_pUpButton);
    m_pButtonLayout->addWidget(m_pDownButton);
    m_pButtonLayout->addWidget(m_pLeftButton);
    m_pButtonLayout->addWidget(m_pRightButton);
    m_pButtonLayout->addItem(m_pRightHorizontalSpacer);

    m_pMainLayout->addWidget(m_pBoardWidget);
    m_pMainLayout->addLayout(m_pButtonLayout);
    pWidget->setLayout(m_pMainLayout);
}

bool ISceneWidgetUi::connect(QWidget *pWidget)
{
    QMetaObject::Connection connection;
    bool result = true;

    connection = pWidget->connect(m_pUpButton, SIGNAL(clicked())
                                  , pWidget, SLOT(onUpButtonClicked()));
    result &= bool(connection);

    connection = pWidget->connect(m_pDownButton, SIGNAL(clicked())
                                  , pWidget, SLOT(onDownButtonClicked()));
    result &= bool(connection);

    connection = pWidget->connect(m_pLeftButton, SIGNAL(clicked())
                                  , pWidget, SLOT(onLeftButtonClicked()));
    result &= bool(connection);

    connection = pWidget->connect(m_pRightButton, SIGNAL(clicked())
                                  , pWidget, SLOT(onRightButtonClicked()));
    result &= bool(connection);

    return result;
}

void ISceneWidgetUi::objectNameSetting(QWidget *pWidget)
{
    m_pMainLayout->setObjectName("MainLayout");
    m_pBoardWidget->setObjectName("BoardWidget");
    m_pButtonLayout->setObjectName("ButtonLayout");
    m_pUpButton->setObjectName("UpButton");
    m_pDownButton->setObjectName("DownButton");
    m_pLeftButton->setObjectName("LeftButton");
    m_pRightButton->setObjectName("RightButton");
    pWidget->setObjectName("SceneWidget");
}

bool ISceneWidgetUi::decorate(QWidget *pWidget)
{
//    m_pMainLayout;
//    m_pBoardWidget;
//    m_pButtonLayout;

    m_pLeftHorizontalSpacer->changeSize(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

//    m_pUpButton;
//    m_pDownButton;
//    m_pLeftButton;
//    m_pRightButton;

    m_pRightHorizontalSpacer->changeSize(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);;

    pWidget->setAttribute(Qt::WidgetAttribute::WA_StyledBackground);

    return true;
}

void ISceneWidgetUi::release()
{
    I_RELEASE(m_pMainLayout);
    I_RELEASE(m_pBoardWidget);
    I_RELEASE(m_pButtonLayout);
    I_RELEASE(m_pLeftHorizontalSpacer);
    I_RELEASE(m_pUpButton);
    I_RELEASE(m_pDownButton);
    I_RELEASE(m_pLeftButton);
    I_RELEASE(m_pRightButton);
    I_RELEASE(m_pRightHorizontalSpacer);
}
