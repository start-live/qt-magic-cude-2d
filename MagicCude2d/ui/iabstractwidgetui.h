#ifndef IABSTRACTWIDGETUI_H
#define IABSTRACTWIDGETUI_H

#include <QtCore/qobject.h>
#include <QtCore/qcoreapplication.h>

#define I_INSTANCE(ptr, Class, parent) \
    ptr = new Class(parent); \
    if (ptr == nullptr) \
        return false; \

#define I_RELEASE(ptr) \
    if (ptr != nullptr) \
    { \
        delete ptr; \
        ptr = nullptr; \
    } \

class IUiSetting : public QObject
{
public:
    explicit IUiSetting(QObject* pParent = nullptr);
    explicit IUiSetting(bool result, QObject* pParent = nullptr);
    explicit IUiSetting(const QString& prompt, QObject* pParent = nullptr);
    explicit IUiSetting(bool result, const QString& prompt, QObject* pParent = nullptr);
    IUiSetting(const IUiSetting& us);
    IUiSetting &operator=(const IUiSetting& us);
    ~IUiSetting();

    void setResult(bool result);
    bool getResult() const;

    void setPrompt(const QString& prompt);
    QString getPrompt() const;

private:
    bool m_result;
    QString m_prompt;
};

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;

class IAbstractWidgetUi
{
public:
    explicit IAbstractWidgetUi();
    virtual ~IAbstractWidgetUi();

    IUiSetting setupUi(QWidget* pWidget);

protected:
    virtual bool instance(QWidget* pWidget) = 0;
    virtual bool retranslateUi(QWidget* pWidget) = 0;
    virtual void layout(QWidget* pWidget) = 0;
    virtual bool connect(QWidget* pWidget) = 0;
    virtual void objectNameSetting(QWidget* pWidget) = 0;
    virtual bool decorate(QWidget* pWidget) = 0;
    virtual void release() = 0;
};

#endif // IABSTRACTWIDGETUI_H
