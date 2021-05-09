#include "swing.h"
#include <time.h>

Swing::Swing(QObject *parent, unsigned int strongMax, unsigned int strongMin, unsigned int timeout) :
	QObject(parent)
{
	if(strongMin >= strongMax) strongMin = 0;
	StrongMax = strongMax;
	StrongMin = strongMin;
	Direction = 0;
	Strong = 0;
	startTimer(timeout);
}

int Swing::GetDirection()
{
	return Direction;
}

void Swing::Update()
{
	if(Strong == 0)
	{
		RandDirection();
		return;
	}
	Process();
}

void Swing::timerEvent(QTimerEvent *e)
{
	Update();
}

void Swing::RandDirection()
{
	qsrand(::time(NULL)+Strong);
	if(Direction != LEFT_DIRECTION && Direction != RIGHT_DIRECTION) //如果既不是左边, 也不是右边
	{
		Direction = qrand()%5; //则随机选择方向
	}
	else
	{
		Direction = NO_DIRECTION; //否则, 下落一段时间. 避免突然由左边转向右边这类情况发生
	}
	Strong = qrand()%(StrongMax-StrongMin) + StrongMin;
	StrongUp = 0;
	StrongDown = Strong;
}

void Swing::Process()
{
	if(++StrongUp >= Strong)
	{
		Strong = 0;
		return;
	}
}
