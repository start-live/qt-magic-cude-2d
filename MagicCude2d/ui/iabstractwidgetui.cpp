#include "iabstractwidgetui.h"

//IUiSetting
IUiSetting::IUiSetting(QObject *pParent)
    : QObject(pParent)
    , m_result(false)
    , m_prompt(QString())
{

}

IUiSetting::IUiSetting(bool result, QObject* pParent)
    : QObject(pParent)
    , m_result(result)
    , m_prompt(QString())
{

}

IUiSetting::IUiSetting(const QString& prompt, QObject* pParent)
    : QObject(pParent)
    , m_result(false)
    , m_prompt(prompt)
{

}

IUiSetting::IUiSetting(bool result, const QString& prompt, QObject* pParent)
    : QObject(pParent)
    , m_result(result)
    , m_prompt(prompt)
{

}

IUiSetting::IUiSetting(const IUiSetting& us)
    : QObject(us.parent())
{
    m_result = us.m_result;
    m_prompt = us.m_prompt;
}

IUiSetting &IUiSetting::operator=(const IUiSetting &us)
{
    setParent(us.parent());
    m_result = us.m_result;
    m_prompt = us.m_prompt;
    return *this;
}

IUiSetting::~IUiSetting()
{

}

void IUiSetting::setResult(bool result)
{
    m_result = result;
}

bool IUiSetting::getResult() const
{
    return m_result;
}

void IUiSetting::setPrompt(const QString &prompt)
{
    m_prompt = prompt;
}

QString IUiSetting::getPrompt() const
{
    return m_prompt;
}

//IAbstractWidgetUi
IAbstractWidgetUi::IAbstractWidgetUi()
{

}

IAbstractWidgetUi::~IAbstractWidgetUi()
{

}

IUiSetting IAbstractWidgetUi::setupUi(QWidget* pWidget)
{
    bool result = true;
    IUiSetting uiSetting(result);

    if (pWidget == nullptr)
    {
        uiSetting.setResult(false);
        uiSetting.setPrompt("widget is nullptr");
        return uiSetting;
    }

    //检测内存分配是否成功
    result = instance(pWidget);
    if (!result)
    {
        uiSetting.setResult(result);
        uiSetting.setPrompt("widget memory allocation failed!");
        return uiSetting;
    }

    //设置文本
    retranslateUi(pWidget);
    //布局
    layout(pWidget);
    //关联信号槽
    connect(pWidget);
    //设置对象名
    objectNameSetting(pWidget);
    //装饰界面
    decorate(pWidget);

    return uiSetting;
}
