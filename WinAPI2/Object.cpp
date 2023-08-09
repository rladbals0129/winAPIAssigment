#include "stdafx.h"
#include "Object.h"



HRESULT Object::init(void)
{
	_centerX = RND->getInt(WINSIZE_X);
	_centerY = RND->getInt(WINSIZE_Y);
	_redius = 5.0f;
	_turnNum = 0.0f;
	_collider = false;
	
	return S_OK;
}

Object::Object()
{
}


Object::~Object()
{
}
