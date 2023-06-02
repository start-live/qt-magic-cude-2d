#ifndef IBOARDWIDGET_H
#define IBOARDWIDGET_H

#include <QtWidgets/qwidget.h>

class IMagicCube;

enum IRightAngleType
{
    TopLeft,
    TopRight,
    BottomLeft,
    BottomRight
};

class IBoardWidget : public QWidget
{
    Q_OBJECT
public:
    explicit IBoardWidget(QWidget *parent = nullptr);
    void turnUp();
    void turnDown();
    void turnLeft();
    void turnRight();

protected:
    void initMagicCube();
    virtual void paintEvent(QPaintEvent *event) override;
    void drawFaceHightLight(QPainter& painter, const QRect& faceInfoRect);
    void drawRightAngle(QPainter& painter, const QPoint& pos, const IRightAngleType& type);

    virtual void mousePressEvent(QMouseEvent *event) override;

signals:

private:
    void onMagicCubeCurrentFaceChanged();

private:
    qint32 m_x;
    qint32 m_y;
    qint32 m_space;
    IMagicCube* m_pMagicCube;
};

#endif // IBOARDWIDGET_H
