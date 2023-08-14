#include "stdafx.h"
#include "Snake.h"

void Snake::update(void)
{
}

void Snake::render(void)
{
    draw();
    animation();
}

void Snake::move()
{
}

void Snake::animation(void)
{
    if (_state == STATE_IDLE)
    {
       
    }
    else if (_state == STATE_ATTACK)
    {
       
    }
    else if (_state == STATE_MOVE)
    {
      
    }
    else if (_state == STATE_DIE)
    {
      
    }
}

Snake::Snake()
{
}

Snake::~Snake()
{
}
