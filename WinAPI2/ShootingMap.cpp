#include "stdafx.h"
#include "ShootingMap.h"

HRESULT ShootingMap::init(void)
{
	GameNode::init(true);
	
	IMAGEMANAGER->addImage("½´ÆÃ¸Ê", "Resources/Images/ShootingGame/BackGround/ShootingBG.bmp",
		WINSIZE_X, WINSIZE_Y);

	_rocket = new Rocket;
	_rocket->init();
	_em = new EnemyManager;
	_em->init();

	return S_OK;
}

void ShootingMap::release(void)
{
	

}

void ShootingMap::update(void)
{
	GameNode::update();


	_rocket->update();
	_em->update();
}

void ShootingMap::render(void)
{
	IMAGEMANAGER->findImage("½´ÆÃ¸Ê")->render(getMemDC());
	_rocket->render(); 
	_em->render();

}
