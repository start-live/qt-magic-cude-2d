#ifndef IMAGICCUBE_H
#define IMAGICCUBE_H

#include <QtCore/qobject.h>

#include "imagiccubeface.h"

enum class IFacePosition
{
    Up,
    Down,
    Front,
    Rear,
    Left,
    Right
};

enum class ITurnDirection
{
    Up,
    Down,
    Left,
    Right
};

enum class IMagicCubeState
{
    Disruption,
    Reduction
};

class IMagicCube : public QObject
{
    Q_OBJECT
public:
    explicit IMagicCube(QObject *parent = nullptr);
    ~IMagicCube();

    void initFace(quint32 order);

    quint32 order() const;
    void setOrder(const quint32 &order);

    void clearFace();
    void setCurrentFace(const IFacePosition& position);
    IMagicCubeFace* currentFace() const;

    QList<IMagicCubeFace *> faceList() const;
    void setFaceList(const QList<IMagicCubeFace *> &faceList);

    void clickPos(const QPoint& pos);

    void turnUp();
    void turnDown();
    void turnLeft();
    void turnRight();

    bool isReduction() const;

private:

signals:
    void faceCreateFail();
    void currentFaceChanged();

private:
    quint32 m_order;
    IMagicCubeFace* m_pUp;
    IMagicCubeFace* m_pDown;
    IMagicCubeFace* m_pFront;
    IMagicCubeFace* m_pRear;
    IMagicCubeFace* m_pLeft;
    IMagicCubeFace* m_pRight;
    QList<IMagicCubeFace*> m_faceList;
    IMagicCubeFace* m_pCurrentFace;
};

#endif // IMAGICCUBE_H
