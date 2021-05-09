#ifndef SNOWWIDGET_H
#define SNOWWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QSize>

#define MAX_IMG_NUM	2

namespace Ui {
class SnowWidget;
}

class SnowWidget : public QWidget
{
	Q_OBJECT
	
public:
	explicit SnowWidget(QWidget *parent = 0, int imgCount = 2);
	~SnowWidget();

	void SetPixmapToLabel(const QList<QPixmap> &pixmapList, const QSize &pixmapSize);
	void SetPixmapToLabel(const QList<QPixmap> &pixmapList, const int width, const int height);
	int GetDeadLine();
	void SetDeadLine(int deadLine);
	void SetSpeed(int min, int max);
	void SetDirection(int direction);
	void SetEdges(int left, int right, int top, int bottom);

public slots:
	void SwapImageToShow(int index);
	void SwapNextImageToShow();
	void UpdateSnow(bool bStore = false);
	
private:
	Ui::SnowWidget *ui;
	QLabel **label;
	int ImageCount;
	int ShowIndex, LastShowIndex;
	int DeadLine;
	int MinSpeed, MaxSpeed;
	int incX, incY;
	int Direction;
	int LeftEdge, RightEdge, TopEdge, BottomEdge;
};

#endif // SNOWWIDGET_H
