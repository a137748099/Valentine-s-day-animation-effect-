#include "pixitem.h"
#include <QTimer>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include "myanimation.h"
#include <QDebug>

PixItem::PixItem(QGraphicsItem *parent):
    QGraphicsPixmapItem (parent)
{
    QPixmap pix(":/PixmapRes/11.jpg");
    pix = pix.scaled(pix.size()*2/5, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    this->setPixmap(pix);
    //初始z值
    this->setZValue(10);

    //路径动画走椭圆
    MyAnimation *pAnimation = new MyAnimation(this, "pos", this);
    pAnimation->setStartValue(QPointF(200, 100));
    pAnimation->setEndValue(QPointF(1000, 180));
    pAnimation->setDuration(27500);
    pAnimation->setPathType(MyAnimation::CirclePath);

    //旋转动画，旋转360度
    QPropertyAnimation *pRotateAnimation = new QPropertyAnimation(this, "rotate", this);
    pRotateAnimation->setDuration(29000);
    pRotateAnimation->setStartValue(270);
    pRotateAnimation->setEndValue(630);

    //缩放动画，不同进度不同的缩放大小
    QPropertyAnimation *pScaleAnimation = new QPropertyAnimation(this, "scale", this);
    pScaleAnimation->setDuration(29000);
    pScaleAnimation->setKeyValueAt(0, 1);
    pScaleAnimation->setKeyValueAt(0.25, 1);
    pScaleAnimation->setKeyValueAt(0.5, 0.8);
    pScaleAnimation->setKeyValueAt(0.75, 0.75);
    pScaleAnimation->setKeyValueAt(1, 1);

    //并行动画组
    m_pAnimationGroup = new QParallelAnimationGroup(this);
    m_pAnimationGroup->addAnimation(pAnimation);
    m_pAnimationGroup->addAnimation(pRotateAnimation);
    m_pAnimationGroup->addAnimation(pScaleAnimation);
    m_pAnimationGroup->setLoopCount(-1);
}

void PixItem::start()
{
    m_pAnimationGroup->start();
}

void PixItem::setRotate(qreal val)
{
    QRectF rect = this->boundingRect();
    m_rotate = val;
    //以y轴进行旋转，位置为负的rect.height()/4
    QTransform transform;
    transform.translate(rect.x(), rect.y() - rect.height()/4);
    transform.rotate(m_rotate, Qt::YAxis);
    transform.translate(-rect.x(), -rect.y() + rect.height()/4);
    this->setTransform(transform);
//    qDebug() << __FUNCTION__ << "song" << "rotate" << m_rotate;
    //转到后面z值变小，不然会档到前面
    if(m_rotate > 450 && m_rotate < 630) {
        this->setZValue(1);
    }
    else {
        this->setZValue(10);
    }
}

qreal PixItem::getRotate() const
{
    return m_rotate;
}
