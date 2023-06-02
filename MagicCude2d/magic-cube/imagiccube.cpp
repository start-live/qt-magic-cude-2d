#include "imagiccube.h"

IMagicCube::IMagicCube(QObject *parent)
    : QObject(parent)
    , m_order(3)
    , m_pUp(nullptr)
    , m_pDown(nullptr)
    , m_pFront(nullptr)
    , m_pRear(nullptr)
    , m_pLeft(nullptr)
    , m_pRight(nullptr)
    , m_pCurrentFace(nullptr)
{
    initFace(m_order);
}

IMagicCube::~IMagicCube()
{
    clearFace();
}

void IMagicCube::initFace(quint32 order)
{
    clearFace();
    IMagicCubeFace* pFace = nullptr;
    qint32 count = 6;
    QList<IBlockColor> colorList = {IBlockColor::Yellow, IBlockColor::White, IBlockColor::Red
                                    , IBlockColor::Orange, IBlockColor::Blue, IBlockColor::Green};
    QStringList nameList = {"上面", "下面", "前面", "后面", "左面", "右面"};
    for (qint32 c = 0; c < count; c++)
    {
        pFace = new IMagicCubeFace(this);
        if (pFace == nullptr)
        {
            clearFace();
            emit faceCreateFail();
            return;
        }

        pFace->setOrder(order);
        pFace->setColor(colorList[c]);
        pFace->setDescription(nameList[c]);
        m_faceList.append(pFace);
    }

    m_pUp = m_faceList[0];
    m_pDown = m_faceList[1];
    m_pFront = m_faceList[2];
    m_pRear = m_faceList[3];
    m_pLeft = m_faceList[4];
    m_pRight = m_faceList[5];

    m_pUp->setOppositeFace(m_pDown);
    m_pUp->setUpFace(m_pRear);
    m_pUp->setDownFace(m_pFront);
    m_pUp->setLeftFace(m_pLeft);
    m_pUp->setRightFace(m_pRight);

    m_pDown->setOppositeFace(m_pUp);
    m_pDown->setUpFace(m_pFront);
    m_pDown->setDownFace(m_pRear);
    m_pDown->setLeftFace(m_pLeft);
    m_pDown->setRightFace(m_pRight);

    m_pFront->setOppositeFace(m_pRear);
    m_pFront->setUpFace(m_pUp);
    m_pFront->setDownFace(m_pDown);
    m_pFront->setLeftFace(m_pLeft);
    m_pFront->setRightFace(m_pRight);

    m_pRear->setOppositeFace(m_pFront);
    m_pRear->setUpFace(m_pUp);
    m_pRear->setDownFace(m_pDown);
    m_pRear->setLeftFace(m_pLeft);
    m_pRear->setRightFace(m_pRight);

    m_pLeft->setOppositeFace(m_pRight);
    m_pLeft->setUpFace(m_pUp);
    m_pLeft->setDownFace(m_pDown);
    m_pLeft->setLeftFace(m_pRear);
    m_pLeft->setRightFace(m_pFront);

    m_pRight->setOppositeFace(m_pLeft);
    m_pRight->setUpFace(m_pUp);
    m_pRight->setDownFace(m_pDown);
    m_pRight->setLeftFace(m_pFront);
    m_pRight->setRightFace(m_pRear);

    m_pCurrentFace = m_pFront;
}

quint32 IMagicCube::order() const
{
    return m_order;
}

void IMagicCube::setOrder(const quint32 &order)
{
    m_order = order;
    for (IMagicCubeFace* pFace : m_faceList)
    {
        pFace->setOrder(m_order);
    }
}

void IMagicCube::clearFace()
{
    for (IMagicCubeFace* pFace: m_faceList)
    {
        delete pFace;
    }
    m_faceList.clear();
}

void IMagicCube::setCurrentFace(const IFacePosition &position)
{
    m_pCurrentFace = m_faceList[quint32(position)];
}

IMagicCubeFace *IMagicCube::currentFace() const
{
    return m_pCurrentFace;
}

QList<IMagicCubeFace *> IMagicCube::faceList() const
{
    return m_faceList;
}

void IMagicCube::setFaceList(const QList<IMagicCubeFace *> &faceList)
{
    m_faceList = faceList;
}

void IMagicCube::clickPos(const QPoint &pos)
{
    for (IMagicCubeFace* pFace : m_faceList)
    {
        if (pFace->infoRect().contains(pos))
        {
            m_pCurrentFace = pFace;
            m_pCurrentFace->clickPos(pos);
            emit currentFaceChanged();
            return;
        }
    }
}

void IMagicCube::turnUp()
{
    if (m_pCurrentFace == nullptr)
        return;

    m_pCurrentFace->turnUp();
}

void IMagicCube::turnDown()
{
    if (m_pCurrentFace == nullptr)
        return;

    m_pCurrentFace->turnDown();
}

void IMagicCube::turnLeft()
{
    if (m_pCurrentFace == nullptr)
        return;

    m_pCurrentFace->turnLeft();
}

void IMagicCube::turnRight()
{
    if (m_pCurrentFace == nullptr)
        return;

    m_pCurrentFace->turnRight();
}

bool IMagicCube::isReduction() const
{
    if (m_faceList.isEmpty())
        return true;

    for (IMagicCubeFace* pFace : m_faceList)
    {
        if (!pFace->sameColor())
            return false;
    }

    return true;
}

