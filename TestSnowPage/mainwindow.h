#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

#include <QLabel>
#include <QPixmap>
#include "snowwidget.h"
#include "swing.h"
/*
#define WINDOW_OPACITY		0.5
#define TIMEOUT_TIME		150
#define MAX_PIXMAP			11
#define MAX_PICS			30
*/
namespace Ui {
class Widget;
}

const qreal WINDOW_OPACITY = 0.5;
const int TIMEOUT_TIME = 150;
const int MAX_PIXMAP = 11;
const int MAX_PICS = 100;
const int SnowSizeMax = 64;
const int SnowSizeMin = 16;

class PixItem;
class TextItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected slots:
    void timerEvent(QTimerEvent *e);
    void FlashSnow();

private:
    Ui::MainWindow *ui;

    SnowWidget *snow[MAX_PICS];
    QList<QPixmap> pixmapList[MAX_PIXMAP];
    Swing *swing;
    QList<PixItem *> m_itemList;
    TextItem *m_pTextItem = nullptr;
};

#endif // MAINWINDOW_H
