#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
#include <QMatrix>
#include <QTransform>
#include <QDebug>
#include <time.h>
#include <QCryptographicHash>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "pixitem.h"
#include <QPushButton>
#include <QTimer>
#include <QPainter>
#include "textitem.h"

#ifdef Q_OS_LINUX
#include <X11/extensions/shape.h>
#endif
#ifdef Q_OS_WIN
#include <windows.h>
#endif

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setGeometry(0, 0, qApp->desktop()->width(), qApp->desktop()->height());

    QGraphicsView *myView = new QGraphicsView(this);
    myView->resize(this->size());
    myView->viewport()->setStyleSheet("background:black;");

    QGraphicsScene *myScene = new QGraphicsScene;
    myView->setScene(myScene);

    for(int i = 0; i < 8; ++i) {
        PixItem *pixItem = new PixItem;
//        pixItem->setMyPixmap(QString(":/PixmapRes/%1.jpg").arg(i + 11));
        myScene->addItem(pixItem);
        m_itemList.append(pixItem);
        pixItem->setVisible(false);
    }

    QPushButton *button = new QPushButton(myView);
    button->setGeometry(this->width() - 150, this->height() - 150, 100, 40);
    button->setText(u8"开始");
    connect(button, &QPushButton::clicked, this, [=]{
        for(int i = 0; i < m_itemList.size(); ++i) {
            //延时启动
            QTimer::singleShot(3580*i, this, [=]{
                m_itemList.at(i)->setVisible(true);
                m_itemList.at(i)->start();
                qDebug() << __FUNCTION__ << "song" << m_itemList.at(i)->boundingRect();
            });
        }
    });

    m_pTextItem = new TextItem(myView);
    m_pTextItem->setMyText(u8"希望在未来的每一天里我们都能快快乐乐，让每一天都像情人节一样");
    m_pTextItem->setGeometry(0, 800, this->width(), 100);

    TextItem *pTextItem = new TextItem(myView);
    pTextItem->setMyText(u8"2021情人节快乐呀");
    pTextItem->setGeometry(0, 100, this->width(), 100);

    /////////////////////////////////
    int i, j;
    int frame = 2;
    QTransform transform;
    transform.rotate(90.0);
    //transform = QPixmap::trueMatrix(transform, 128, 128);
    for(i = 0; i < MAX_PIXMAP; i++)
    {
        pixmapList[i].clear();
        pixmapList[i].append(QPixmap(":/PixmapRes/"+QString::number(i)+".png"));
        for(j = 0; j < frame-1; j++)
            pixmapList[i].append(pixmapList[i].at(j).transformed(transform));
    }

    for(i = 0; i < MAX_PICS; i++)
    {
        snow[i] = new SnowWidget(this, frame);
        snow[i]->setGeometry(-128, -128, 64, 64);
        snow[i]->SetSpeed(3, 8);
        snow[i]->SetEdges(0, this->width(), 0, this->height());
        //snow[i]->show();
    }

    swing = new Swing(this, 120, 60, 200);
    startTimer(TIMEOUT_TIME);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::timerEvent(QTimerEvent *e)
{
    const int timeinit = 10;
    static int timeCount = timeinit;
    static int initLabel = MAX_PICS;
    if(--timeCount <= 0)
    {
        qsrand(::time(NULL));
        timeCount = timeinit;
        if(initLabel > 0)
        {
            --initLabel;
            snow[initLabel]->move(0, -snow[initLabel]->height());
        }
    }

    //action flow down
    FlashSnow();
}

void MainWindow::FlashSnow()
{
    int i;
    for(i = 0; i < MAX_PICS; i++)
    {
        if(snow[i] == NULL) continue;
        if(snow[i]->y() == -snow[i]->height())
        {
            //repaint label's backgroud
            int imgId = (qrand()%MAX_PIXMAP);
            //resize label
            int size = (qrand()%(SnowSizeMax-SnowSizeMin))+SnowSizeMin;
            snow[i]->SetPixmapToLabel(pixmapList[imgId], size, size);

            //init place
            int x = (qrand()%this->width());
            snow[i]->move(x, 10-snow[i]->height());
        }
        else if(snow[i]->x() == -128) continue;  //初始化为-128
        else
        {
            //snow flow down
            snow[i]->SetDirection(swing->GetDirection());
            snow[i]->UpdateSnow(true);
        }
    }
}
