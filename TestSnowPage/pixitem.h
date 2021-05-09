#ifndef PIXITEM_H
#define PIXITEM_H

#include <QGraphicsPixmapItem>

class QTimer;
class QParallelAnimationGroup;
class MyAnimation;

class PixItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
    Q_PROPERTY(qreal scale READ scale WRITE setScale)
    Q_PROPERTY(qreal rotate READ getRotate WRITE setRotate)
//    Q_PROPERTY(qreal ZValue READ setZValue WRITE zValue)

public:
    explicit PixItem(QGraphicsItem *parent = nullptr);

    void start();
    void setRotate(qreal val);
    qreal getRotate() const;
private:
    QTimer *m_pTimer = nullptr;
    qreal m_rotate = 0;

    QParallelAnimationGroup *m_pAnimationGroup = nullptr;

};

#endif // PIXITEM_H
