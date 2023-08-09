#include "stdafx.h"
#include "MainGame16.h"

HRESULT MainGame16::init(void)
{
	GameNode::init(true);
	_player = new Player0630;
	_player->init();


	return S_OK;
}

void MainGame16::release(void)
{
	_player->release();
	SAFE_DELETE(_player);

}

void MainGame16::update(void)
{
	GameNode::update();
	_player->update();
	
}

void MainGame16::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	_player->render();
	this->getBackBuffer()->render(getHDC());
}

