#include "imagiccubeblock.h"

IMagicCubeBlock::IMagicCubeBlock(QObject *parent)
    : QObject(parent)
{

}

QPoint IMagicCubeBlock::pos() const
{
    return m_pos;
}

void IMagicCubeBlock::setPos(const QPoint &pos)
{
    m_pos = pos;
}

QSize IMagicCubeBlock::size() const
{
    return m_size;
}

void IMagicCubeBlock::setSize(const QSize &size)
{
    m_size = size;
}

IBlockColor IMagicCubeBlock::color() const
{
    return m_color;
}

QColor IMagicCubeBlock::blockColor() const
{
    QList<IBlockColor> colorList = {IBlockColor::Red, IBlockColor::Blue, IBlockColor::Green
                                    , IBlockColor::White, IBlockColor::Orange, IBlockColor::Yellow};
    QList<QColor> bcolorList = {Qt::red, Qt::blue, Qt::green, Qt::white, QColor(245,186,64), Qt::yellow};

    return bcolorList[colorList.indexOf(m_color)];
}

void IMagicCubeBlock::setColor(const IBlockColor &color)
{
    m_color = color;
}

qint32 IMagicCubeBlock::row() const
{
    return m_pos.y();
}

qint32 IMagicCubeBlock::column() const
{
    return m_pos.x();
}

QRect IMagicCubeBlock::blockRect() const
{
    return m_blockRect;
}

void IMagicCubeBlock::setBlockRect(const QRect &blockRect)
{
    m_blockRect = blockRect;
}
