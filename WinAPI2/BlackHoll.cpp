#include "stdafx.h"
#include "BlackHoll.h"

HRESULT BlackHoll::init(void)
{
	GameNode::init(true);
	_hole = new Hole;
	_hole->init();

	for (int i = 0; i < 1000; i++)
	{
		Object obj;
		obj.init();
		_object.push_back(obj);
	}
	
	
	for (auto iter = _object.begin(); iter != _object.end(); ++iter)
	{
		iter->setTurnNum(RND->getFromFloatTo(2.3f,PI));
	}

	return S_OK;
}

void BlackHoll::release(void)
{
	SAFE_DELETE(_hole);
	
}

void BlackHoll::update(void)
{
	GameNode::update();
	_hole->update();

	for (auto iter = _object.begin(); iter != _object.end();) //
	{
		
		float hcx = _hole->getCenterX();
		float hcy = _hole->getCenterY();
		float ocx = iter->getCenterX();
		float ocy = iter->getCenterY();
		float dx = hcx - ocx;
		float dy = hcy - ocy;
		float distance = sqrt(dx * dx + dy * dy);
		//if (abs(dx) < 2 && abs(dy) < 2)
		if (distance <= 4)
		{
			iter->setCollider(true);
			
		}
		if (iter->getCollider() == true)
		{
			_radian = atan2(_hole->getCenterY() - iter->getCenterY(), _hole->getCenterX() - iter->getCenterX())
				- iter->getTurnNum();				
		}
		else
		{			
			_radian = atan2(_hole->getCenterY() - iter->getCenterY(), _hole->getCenterX() - iter->getCenterX());
		}	
		iter->setCenterX(iter->getCenterX() + cosf(_radian) * 3.0f);
		iter->setCenterY(iter->getCenterY() + sinf(_radian) * 3.0f);

		if (iter == _object.begin()) { cout << distance << endl; }

		if (iter->getCenterX() < 0 || iter->getCenterY() < 0 ||
			iter->getCenterX() > WINSIZE_X || iter->getCenterY() > WINSIZE_Y)
		{
			iter->setCollider(false);		
			iter = _object.erase(iter);
			createDust();
			++iter;
			
		}
		else 
		{
			++iter;
		}
		
			
	
	}
	
}

void BlackHoll::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	_hole->render();
	for (auto iter = _object.begin(); iter != _object.end(); ++iter)
	{
		EllipaseMakeCenter(getMemDC(), iter->getCenterX(), iter->getCenterY(), iter->getRedius());
		//cout << iter->getCenterX() << "   " << iter->getCenterY() << "   "<< iter->getRedius();
	}
	

	this->getBackBuffer()->render(getHDC());
}

void BlackHoll::createDust()
{

	Object obj;
	obj.init();
	_object.push_back(obj);

	for (auto iter = _object.begin(); iter != _object.end(); ++iter)
	{
		iter->setTurnNum(RND->getFromFloatTo(2.3f, PI));
	}
}
