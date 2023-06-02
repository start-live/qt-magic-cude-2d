#ifndef IMAGICCUBEFACE_H
#define IMAGICCUBEFACE_H

#include <QtCore/qobject.h>
#include <QtCore/qrect.h>

#include "imagiccubeblock.h"

class IMagicCubeFace : public QObject
{
    Q_OBJECT
public:
    explicit IMagicCubeFace(QObject *parent = nullptr);
    ~IMagicCubeFace();

    quint32 order() const;
    void setOrder(const quint32 &order);

    QList<IMagicCubeBlock *> blockList() const;
    void setBlockList(const QList<IMagicCubeBlock *> &blockList);

    void clearBlock();

    IBlockColor color() const;
    void setColor(const IBlockColor& color);
    void setColor(const QPoint& blockPos, const IBlockColor& color);
    IBlockColor color(const QPoint& blockPos) const;
    void setColor(qint32 row, qint32 column, const IBlockColor& color);
    IBlockColor color(qint32 row, qint32 column) const;

    QRect infoRect() const;
    void setInfoRect(const QRect &infoRect);

    QString description() const;
    void setDescription(const QString &description);

    qint32 currentRow() const;
    void setCurrentRow(const qint32 &currentRow);

    QRect faceRect() const;
    void setFaceRect(const QRect &faceRect);

    QRect textRect() const;
    void setTextRect(const QRect &textRect);

    void clickPos(const QPoint& pos);

    IMagicCubeBlock *currentBlock() const;
    void setCurrentBlock(IMagicCubeBlock* pBlock);

    void turnUp();
    void turnDown();
    void turnLeft();
    void turnRight();

    IMagicCubeFace *oppositeFace() const;
    void setOppositeFace(IMagicCubeFace *pOppositeFace);

    IMagicCubeFace *upFace() const;
    void setUpFace(IMagicCubeFace *pUpFace);

    IMagicCubeFace *downFace() const;
    void setDownFace(IMagicCubeFace *pDownFace);

    IMagicCubeFace *leftFace() const;
    void setLeftFace(IMagicCubeFace *pLeftFace);

    IMagicCubeFace *rightFace() const;
    void setRightFace(IMagicCubeFace *pRightFace);

    void rotateLeft();
    void rotateRight();

    bool sameColor() const;

private:
    void orderCahnged();

signals:
    void blockCreateFail();
    void currentBlockChanged();

private:
    qint32 m_currentRow;
    QRect m_infoRect;
    QRect m_faceRect;
    QRect m_textRect;
    QString m_description;
    quint32 m_order;
    IBlockColor m_color;
    IMagicCubeBlock* m_pCurrentBlock;
    QList<IMagicCubeBlock*> m_blockList;
    IMagicCubeFace* m_pOppositeFace;
    IMagicCubeFace* m_pUpFace;
    IMagicCubeFace* m_pDownFace;
    IMagicCubeFace* m_pLeftFace;
    IMagicCubeFace* m_pRightFace;
};

#endif // IMAGICCUBEFACE_H
