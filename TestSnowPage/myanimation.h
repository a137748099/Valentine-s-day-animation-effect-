#ifndef MYANIMATION_H
#define MYANIMATION_H

#include <QPropertyAnimation>
#include <QPainterPath>

class MyAnimation : public QPropertyAnimation
{
    Q_OBJECT
public:
    explicit MyAnimation(QObject *target, const QByteArray &propertyName, QObject *parent = nullptr);

    enum PathType {
        LinearPath,
        CirclePath,
        ArcPath,
        NPathTypes
    };

    void setPathType(PathType pathType);
protected:
    void updateCurrentTime(int currentTime) override;

private:
    QPainterPath m_path;
    PathType m_pathType;

};

#endif // MYANIMATION_H
