#ifndef IMAGICCUBEBLOCK_H
#define IMAGICCUBEBLOCK_H

#include <QtCore/qobject.h>
#include <QtCore/qpoint.h>
#include <QtCore/qsize.h>
#include <QtCore/qrect.h>
#include <QtGui/qcolor.h>

enum class IBlockColor
{
    Red,
    Yellow,
    Blue,
    White,
    Green,
    Orange
};

class IMagicCubeBlock : public QObject
{
    Q_OBJECT
public:
    explicit IMagicCubeBlock(QObject *parent = nullptr);

    QPoint pos() const;
    void setPos(const QPoint &pos);

    QSize size() const;
    void setSize(const QSize &size);

    IBlockColor color() const;
    QColor blockColor() const;
    void setColor(const IBlockColor &color);

    qint32 row() const;
    qint32 column() const;

    QRect blockRect() const;
    void setBlockRect(const QRect &blockRect);

signals:
    void posChanged(const QPoint& newPos);
    void sizeChanged(const QSize& newSize);
    void colorChanged(const IBlockColor& newColor);

private:
    QPoint m_pos;
    QSize m_size;
    IBlockColor m_color;
    QRect m_blockRect;
};

#endif // IMAGICCUBEBLOCK_H
