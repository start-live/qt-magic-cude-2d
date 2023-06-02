#include "iboardwidget.h"

#include <QtCore/qdebug.h>

#include <QtGui/qevent.h>
#include <QtGui/qpainter.h>

#include "magic-cube/imagiccube.h"

IBoardWidget::IBoardWidget(QWidget *parent)
    : QWidget(parent)
    , m_pMagicCube(nullptr)
{
    initMagicCube();
}

void IBoardWidget::turnUp()
{
    m_pMagicCube->turnUp();
    update();
}

void IBoardWidget::turnDown()
{
    m_pMagicCube->turnDown();
    update();
}

void IBoardWidget::turnLeft()
{
    m_pMagicCube->turnLeft();
    update();
}

void IBoardWidget::turnRight()
{
    m_pMagicCube->turnRight();
    update();
}

void IBoardWidget::initMagicCube()
{
    m_pMagicCube = new IMagicCube(this);
    connect(m_pMagicCube, &IMagicCube::currentFaceChanged
            , this, &IBoardWidget::onMagicCubeCurrentFaceChanged);
    qint32 order = 3;
    m_pMagicCube->setOrder(order);

    qint32 startX = 30;
    qint32 startY = 30;
    qint32 blockWidth = 40;
    qint32 blockHeight = 40;
    qint32 blockSpace = 5;
    qint32 infoBorderWidth = 10;

    qint32 faceWidth = (order + 1) * blockSpace + order * blockWidth;;
    qint32 faceHeight = faceWidth;

    qint32 infoWidth = infoBorderWidth * 2 + faceWidth;
    qint32 infoHeight = infoBorderWidth * 2 + faceHeight + 50;
    qint32 infoSpace = infoWidth + 10;

    qint32 textWidth = faceWidth;
    qint32 textHeight = 40;

    qint32 boardWidth = infoSpace * 6 + 60;
    qint32 boardHeight = infoHeight + 60;
    this->setMinimumWidth(boardWidth);
    this->setMinimumHeight(boardHeight);

    QList<IMagicCubeFace*> faceList = m_pMagicCube->faceList();
    qint32 count = faceList.count();
    for (qint32 index = 0; index < count; index++)
    {
        IMagicCubeFace* pFace = faceList[index];
        QList<IMagicCubeBlock*> blockList = pFace->blockList();

        //信息块
        qint32 infoX = startX + index * infoSpace;
        qint32 infoY = startY;
        QRect infoRect(infoX, infoY, infoWidth, infoHeight);
        pFace->setInfoRect(infoRect);

        //文字描述
        qint32 textX = infoRect.x() + 10;
        qint32 textY = infoRect.y() + 10;
        QRect textRect(textX, textY, textWidth, textHeight);
        pFace->setTextRect(textRect);

        //面底
        qint32 faceX = infoRect.x() + 10;
        qint32 faceY = infoRect.y() + 60;
        QRect faceRect(faceX, faceY, faceWidth, faceHeight);
        pFace->setFaceRect(faceRect);

        //小方块
        qint32 blockX = faceX + 5;
        qint32 blockY = faceY + 5;
        for (IMagicCubeBlock* pBlock : blockList)
        {
            qint32 x = blockX + pBlock->pos().x() * (blockWidth + blockSpace);
            qint32 y = blockY + pBlock->pos().y() * (blockHeight + blockSpace);
            QRect blockRect(x, y, blockWidth, blockHeight);
            pBlock->setBlockRect(blockRect);
        }
    }
}

void IBoardWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QList<IMagicCubeFace*> faceList = m_pMagicCube->faceList();
    qint32 count = faceList.count();
    for (qint32 index = 0; index < count; index++)
    {
        IMagicCubeFace* pFace = faceList[index];
        QList<IMagicCubeBlock*> blockList = pFace->blockList();

        //信息块
        QRect infoRect = pFace->infoRect();
        painter.fillRect(infoRect, Qt::GlobalColor::lightGray);

        //文字描述
        QRect textRect = pFace->textRect();
        painter.fillRect(textRect, Qt::GlobalColor::gray);
        painter.drawText(textRect, pFace->description(), QTextOption(Qt::AlignmentFlag::AlignCenter));

        //面底
        QRect faceRect = pFace->faceRect();
        painter.fillRect(faceRect, Qt::GlobalColor::black);

        //小方块
        for (IMagicCubeBlock* pBlock : blockList)
        {
            painter.fillRect(pBlock->blockRect(), pBlock->blockColor());
        }

        //选中面高亮
        if (pFace == m_pMagicCube->currentFace())
        {
            drawFaceHightLight(painter, pFace->infoRect());
            IMagicCubeBlock* pFaceCurrentBlock = pFace->currentBlock();
            //选中方块高亮
            if (pFaceCurrentBlock != nullptr)
            {
                drawFaceHightLight(painter, pFaceCurrentBlock->blockRect());
            }
        }
    }

    QWidget::paintEvent(event);
}

void IBoardWidget::drawFaceHightLight(QPainter& painter, const QRect& faceInfoRect)
{
    //找到四个角的中心点
    QPoint topLeftPos = faceInfoRect.topLeft();
    QPoint topRightPos = faceInfoRect.topRight();
    QPoint bottomLeftPos = faceInfoRect.bottomLeft();
    QPoint bottomRight = faceInfoRect.bottomRight();

    //进行绘制
    drawRightAngle(painter, topLeftPos, IRightAngleType::TopLeft);
    drawRightAngle(painter, topRightPos, IRightAngleType::TopRight);
    drawRightAngle(painter, bottomLeftPos, IRightAngleType::BottomLeft);
    drawRightAngle(painter, bottomRight, IRightAngleType::BottomRight);
}

void IBoardWidget::drawRightAngle(QPainter &painter, const QPoint &pos, const IRightAngleType& type)
{
    QPen originalPen = painter.pen();
    QPen pen;
    pen.setWidth(3);
    pen.setColor(QColor(77,133,255));
    painter.setPen(pen);

    qint32 angleLineLength = 15;
    QPoint firstPos;
    QPoint secondPos;
    switch (type) {
    case IRightAngleType::TopLeft:
        firstPos = pos + QPoint(angleLineLength, 0);
        secondPos = pos + QPoint(0, angleLineLength);
        break;
    case IRightAngleType::TopRight:
        firstPos = pos + QPoint(-angleLineLength, 0);
        secondPos = pos + QPoint(0, angleLineLength);
        break;
    case IRightAngleType::BottomLeft:
        firstPos = pos + QPoint(angleLineLength, 0);
        secondPos = pos + QPoint(0, -angleLineLength);
        break;

    case IRightAngleType::BottomRight:
        firstPos = pos + QPoint(-angleLineLength, 0);
        secondPos = pos + QPoint(0, -angleLineLength);
        break;
    default:
        //todo
        return;
    }

    painter.drawLine(pos, firstPos);
    painter.drawLine(pos, secondPos);

    painter.setPen(originalPen);
}

void IBoardWidget::mousePressEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();
    m_pMagicCube->clickPos(pos);
}

void IBoardWidget::onMagicCubeCurrentFaceChanged()
{
    update();
}
