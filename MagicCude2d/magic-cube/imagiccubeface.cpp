#include "imagiccubeface.h"

IMagicCubeFace::IMagicCubeFace(QObject *parent)
    : QObject(parent)
    , m_order(0)
    , m_color(IBlockColor::Red)
    , m_pCurrentBlock(nullptr)
    , m_pOppositeFace(nullptr)
    , m_pUpFace(nullptr)
    , m_pDownFace(nullptr)
    , m_pLeftFace(nullptr)
    , m_pRightFace(nullptr)
{

}

IMagicCubeFace::~IMagicCubeFace()
{
    clearBlock();
}

quint32 IMagicCubeFace::order() const
{
    return m_order;
}

void IMagicCubeFace::setOrder(const quint32 &order)
{
    if (order == 0)
        return;

    if (order != m_order)
    {
        m_order = order;
        orderCahnged();
    }
}

QList<IMagicCubeBlock *> IMagicCubeFace::blockList() const
{
    return m_blockList;
}

void IMagicCubeFace::setBlockList(const QList<IMagicCubeBlock *> &blockList)
{
    m_blockList = blockList;
}

void IMagicCubeFace::clearBlock()
{
    for (IMagicCubeBlock* pBlock : m_blockList)
    {
        delete pBlock;
    }
    m_blockList.clear();
}

void IMagicCubeFace::setColor(const IBlockColor &color)
{
    m_color = color;
    for (IMagicCubeBlock* pBlock : m_blockList)
    {
        pBlock->setColor(color);
    }
}

void IMagicCubeFace::setColor(const QPoint &blockPos, const IBlockColor &color)
{
    for (IMagicCubeBlock* pBlock : m_blockList)
    {
        if (pBlock->pos() == blockPos)
        {
            pBlock->setColor(color);
            break;
        }
    }
}

IBlockColor IMagicCubeFace::color(const QPoint &blockPos) const
{
    for (IMagicCubeBlock* pBlock : m_blockList)
    {
        if (pBlock->pos() == blockPos)
        {
            return pBlock->color();
        }
    }
    return m_color;
}

void IMagicCubeFace::setColor(qint32 row, qint32 column, const IBlockColor &color)
{
    QPoint pos(column, row);
    setColor(pos, color);
}

IBlockColor IMagicCubeFace::color(qint32 row, qint32 column) const
{
    QPoint pos(column, row);
    return color(pos);
}

void IMagicCubeFace::orderCahnged()
{
    clearBlock();
    QPoint pos;
    for (quint32 x = 0; x < m_order; x++)
    {
        pos.setX(x);
        for (quint32 y = 0; y < m_order; y++)
        {
            pos.setY(y);
            IMagicCubeBlock* pBlock = new IMagicCubeBlock(this);
            if (pBlock == nullptr)
            {
                clearBlock();
                emit blockCreateFail();
                return;
            }

            pBlock->setPos(pos);
            pBlock->setColor(m_color);
            m_blockList.append(pBlock);
        }
    }
}

IMagicCubeFace *IMagicCubeFace::rightFace() const
{
    return m_pRightFace;
}

void IMagicCubeFace::setRightFace(IMagicCubeFace *pRightFace)
{
    m_pRightFace = pRightFace;
}

//左旋
void IMagicCubeFace::rotateLeft()
{
    QPoint originalPos;
    QPoint newPos;
    for (quint32 x = 0; x < m_order; x++)
    {
        for (quint32 y = 0; y < m_order; y++)
        {
            originalPos.setX(x);
            originalPos.setY(y);

            newPos.setX(y);
            newPos.setY(m_order - x - 1);

            //交换颜色
            IBlockColor tempColor = this->color(originalPos);
            this->setColor(originalPos, this->color(newPos));
            this->setColor(newPos, tempColor);
        }
    }
}

//右旋
void IMagicCubeFace::rotateRight()
{
    QPoint originalPos;
    QPoint newPos;
    for (quint32 x = 0; x < m_order; x++)
    {
        for (quint32 y = 0; y < m_order; y++)
        {
            originalPos.setX(x);
            originalPos.setY(y);

            newPos.setX(m_order - y - 1);
            newPos.setY(x);

            //交换颜色
            IBlockColor tempColor = this->color(originalPos);
            this->setColor(originalPos, this->color(newPos));
            this->setColor(newPos, tempColor);
        }
    }
}

bool IMagicCubeFace::sameColor() const
{
    if (m_blockList.isEmpty())
        return true;

    IBlockColor color = m_blockList[0]->color();
    for (IMagicCubeBlock* pBlock : m_blockList)
    {
        if (pBlock->color() != color)
            return false;
    }

    return true;
}

IMagicCubeFace *IMagicCubeFace::leftFace() const
{
    return m_pLeftFace;
}

void IMagicCubeFace::setLeftFace(IMagicCubeFace *pLeftFace)
{
    m_pLeftFace = pLeftFace;
}

IMagicCubeFace *IMagicCubeFace::downFace() const
{
    return m_pDownFace;
}

void IMagicCubeFace::setDownFace(IMagicCubeFace *pDownFace)
{
    m_pDownFace = pDownFace;
}

IMagicCubeFace *IMagicCubeFace::upFace() const
{
    return m_pUpFace;
}

void IMagicCubeFace::setUpFace(IMagicCubeFace *pUpFace)
{
    m_pUpFace = pUpFace;
}

IMagicCubeFace *IMagicCubeFace::oppositeFace() const
{
    return m_pOppositeFace;
}

void IMagicCubeFace::setOppositeFace(IMagicCubeFace *pOppositeFace)
{
    m_pOppositeFace = pOppositeFace;
}

QRect IMagicCubeFace::textRect() const
{
    return m_textRect;
}

void IMagicCubeFace::setTextRect(const QRect &textRect)
{
    m_textRect = textRect;
}

void IMagicCubeFace::clickPos(const QPoint &pos)
{
    for (IMagicCubeBlock* pBlock : m_blockList)
    {
        if (pBlock->blockRect().contains(pos))
        {
            m_pCurrentBlock = pBlock;
            m_currentRow = m_pCurrentBlock->row();
            emit currentBlockChanged();
            return;
        }
    }
    m_pCurrentBlock = nullptr;
}

IMagicCubeBlock *IMagicCubeFace::currentBlock() const
{
    return m_pCurrentBlock;
}

void IMagicCubeFace::setCurrentBlock(IMagicCubeBlock *pBlock)
{
    m_pCurrentBlock = pBlock;
}

//上下旋转看列
void IMagicCubeFace::turnUp()
{
    if (m_pCurrentBlock == nullptr)
        return;

    qint32 column = m_pCurrentBlock->column();
    if (column == 0)
    {
        //左面向左旋转
        m_pLeftFace->rotateLeft();
        //todo 颜色交换顺序：this->m_up->m_opp->m_down->this
    }
    else if (quint32(column) == m_order - 1)
    {
        //右面向右旋转
        m_pRightFace->rotateRight();
        //todo 颜色交换顺序：this->m_up->m_opp->m_down->this
    }
    else
    {
        //todo 颜色交换顺序：this->m_up->m_opp->m_down->this
    }

    //四面颜色交换
    for (quint32 row = 0; row < m_order; row++)
    {
        IBlockColor colColor = this->color(row, column);
        this->setColor(row, column, m_pDownFace->color(row, column));
        m_pDownFace->setColor(row, column, m_pOppositeFace->color(row, column));
        m_pOppositeFace->setColor(row, column, m_pUpFace->color(row, column));
        m_pUpFace->setColor(row, column, colColor);
    }
}

void IMagicCubeFace::turnDown()
{
    if (m_pCurrentBlock == nullptr)
        return;

    qint32 column = m_pCurrentBlock->column();
    if (column == 0)
    {
        //左面向右旋转
        m_pLeftFace->rotateRight();
        //todo 颜色交换顺序：this->m_down->m_opp->m_up->this
    }
    else if (quint32(column) == m_order - 1)
    {
        //右面向左旋转
        m_pRightFace->rotateLeft();
        //todo 颜色交换顺序：this->m_down->m_opp->m_up->this
    }
    else
    {
        //todo 颜色交换顺序：this->m_down->m_opp->m_up->this
    }

    //四面颜色交换
    for (quint32 row = 0; row < m_order; row++)
    {
        IBlockColor colColor = this->color(row, column);
        this->setColor(row, column, m_pUpFace->color(row, column));
        m_pUpFace->setColor(row, column, m_pOppositeFace->color(row, column));
        m_pOppositeFace->setColor(row, column, m_pDownFace->color(row, column));
        m_pDownFace->setColor(row, column, colColor);
    }
}

//左右旋转看行
void IMagicCubeFace::turnLeft()
{
    if (m_pCurrentBlock == nullptr)
        return;

    qint32 row = m_pCurrentBlock->row();
    if (row == 0)
    {
        //上面向右旋转
        m_pUpFace->rightFace();
        //todo 颜色交换顺序：this->m_left->m_opp->m_right->this
    }
    else if (quint32(row) == m_order - 1)
    {
        //下面向左旋转
        m_pDownFace->leftFace();
        //todo 颜色交换顺序：this->m_left->m_opp->m_right->this
    }
    else
    {
        //todo 颜色交换顺序：this->m_left->m_opp->m_right->this
    }

    //四面颜色交换
    for (quint32 column = 0; column < m_order; column++)
    {
        IBlockColor colColor = this->color(row, column);
        this->setColor(row, column, m_pRightFace->color(row, column));
        m_pRightFace->setColor(row, column, m_pOppositeFace->color(row, column));
        m_pOppositeFace->setColor(row, column, m_pLeftFace->color(row, column));
        m_pLeftFace->setColor(row, column, colColor);
    }
}

void IMagicCubeFace::turnRight()
{
    if (m_pCurrentBlock == nullptr)
        return;

    qint32 row = m_pCurrentBlock->row();
    if (row == 0)
    {
        //上面向左旋转
        m_pUpFace->leftFace();
        //todo 颜色交换顺序：this->m_right->m_opp->m_left->this
    }
    else if (quint32(row) == m_order - 1)
    {
        //下面向右旋转
        m_pDownFace->rightFace();
        //todo 颜色交换顺序：this->m_right->m_opp->m_left->this
    }
    else
    {
        //todo 颜色交换顺序：this->m_right->m_opp->m_left->this
    }

    //四面颜色交换
    for (quint32 column = 0; column < m_order; column++)
    {
        IBlockColor colColor = this->color(row, column);
        this->setColor(row, column, m_pLeftFace->color(row, column));
        m_pLeftFace->setColor(row, column, m_pOppositeFace->color(row, column));
        m_pOppositeFace->setColor(row, column, m_pRightFace->color(row, column));
        m_pRightFace->setColor(row, column, colColor);
    }
}

IBlockColor IMagicCubeFace::color() const
{
    return m_color;
}

QRect IMagicCubeFace::faceRect() const
{
    return m_faceRect;
}

void IMagicCubeFace::setFaceRect(const QRect &faceRect)
{
    m_faceRect = faceRect;
}

qint32 IMagicCubeFace::currentRow() const
{
    return m_currentRow;
}

void IMagicCubeFace::setCurrentRow(const qint32 &currentRow)
{
    m_currentRow = currentRow;
}

QString IMagicCubeFace::description() const
{
    return m_description;
}

void IMagicCubeFace::setDescription(const QString &description)
{
    m_description = description;
}

QRect IMagicCubeFace::infoRect() const
{
    return m_infoRect;
}

void IMagicCubeFace::setInfoRect(const QRect &infoRect)
{
    m_infoRect = infoRect;
}
