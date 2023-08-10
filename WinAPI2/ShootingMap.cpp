#include "stdafx.h"
#include "ShootingMap.h"

HRESULT ShootingMap::init(void)
{
	GameNode::init(true);
	
	IMAGEMANAGER->addImage("½´ÆÃ¸Ê", "Resources/Images/ShootingGame/BackGround/ShootingBG.bmp",
		WINSIZE_X, WINSIZE_Y);

	_rocket = new Rocket;
	_rocket->init();

	return S_OK;
}

void ShootingMap::release(void)
{
	GameNode::release();

}

void ShootingMap::update(void)
{
	GameNode::update();


	_rocket->update();

}

void ShootingMap::render(void)
{
	IMAGEMANAGER->findImage("½´ÆÃ¸Ê")->render(getMemDC());
	_rocket->render();

}
