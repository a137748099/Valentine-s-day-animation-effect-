#include "myanimation.h"

MyAnimation::MyAnimation(QObject *target, const QByteArray &propertyName, QObject *parent):
    QPropertyAnimation (target, propertyName, parent)
{
    setPathType(LinearPath);
}

void MyAnimation::setPathType(MyAnimation::PathType pathType)
{
    if (pathType >= NPathTypes)
        qWarning("Unknown pathType %d", pathType);

    m_pathType = pathType;
    m_path = QPainterPath();
}

void MyAnimation::updateCurrentTime(int currentTime)
{
    if (m_pathType == CirclePath || m_pathType == ArcPath) {
        if (m_path.isEmpty()) {
            QPointF to = endValue().toPointF();
            QPointF from = startValue().toPointF();
            m_path.moveTo(from);
            if(m_pathType == CirclePath) {
                m_path.addEllipse(QRectF(from, to));
            }
            else {
                qreal tempWidth = from.rx() - to.rx();
                qreal tempHeight = from.ry() - to.ry();
                QRectF tempRect = QRectF(to.x() - tempWidth, to.y(), tempWidth*2, tempHeight*2);
                m_path.arcTo(tempRect, 0, 90);
            }
        }
        int dura = duration();
        const qreal progress = ((dura == 0) ? 1 : ((((currentTime - 1) % dura) + 1) / qreal(dura)));

        qreal easedProgress = easingCurve().valueForProgress(progress);
        if (easedProgress > 1.0) {
            easedProgress -= 1.0;
        } else if (easedProgress < 0) {
            easedProgress += 1.0;
        }
        QPointF pt = m_path.pointAtPercent(easedProgress);
        updateCurrentValue(pt);
        emit valueChanged(pt);
    } else {
        QPropertyAnimation::updateCurrentTime(currentTime);
    }
}
