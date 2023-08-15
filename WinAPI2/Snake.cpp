#include "stdafx.h"
#include "Snake.h"


void Snake::update(void)
{
    move();

}

void Snake::render(void)
{
    draw();
    animation();
}

void Snake::move()
{
    switch (_state)
    {
    case STATE_IDLE:
       
        break;
    case STATE_ATTACK:
       
        break;
    case STATE_MOVE:
    

        _rc.left += 1;
        _rc.top += 1;

       
        break;
    case STATE_DIE:
        
        break;
    }
}

void Snake::animation(void)
{
    switch (_state)
    {
    case STATE_IDLE:

        break;
    case STATE_ATTACK:

        break;
    case STATE_MOVE:
        if ((_rndTimeCount * 2) + _worldTimeCount <= GetTickCount())
        {
            _worldTimeCount = GetTickCount();
            _currentFrameX++;
            if (_image->getMaxFrameX() < _currentFrameX)
            {
                _currentFrameX = 0;
            }
        }
        break;
    case STATE_DIE:

        break;
    }
	
}

Snake::Snake() : _state(STATE_MOVE)
{
}

Snake::~Snake()
{
}
