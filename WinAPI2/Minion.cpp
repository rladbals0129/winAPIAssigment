#include "stdafx.h"
#include "Minion.h"

void Minion::update(void)
{
	
}

void Minion::render(void)
{
	draw();
	animation();
}

void Minion::move()
{

}

void Minion::animation(void)
{
	if (_rndTimeCount + _worldTimeCount <= GetTickCount())
	{
		_worldTimeCount = GetTickCount();
		_currentFrameX++;
		if (_image->getMaxFrameX() < _currentFrameX)
		{
			_currentFrameX = 0;

		}
	}
}


Minion::Minion() {
	//!Do Nothing
}

Minion::~Minion() {
	//!Do Nothing
}
