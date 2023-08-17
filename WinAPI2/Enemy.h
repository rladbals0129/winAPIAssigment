#pragma once
#include "GameNode.h"
class Enemy : public GameNode
{
protected:
	GImage* _image;
	RECT _rc;

	int _currentFrameX;
	int _currentFrameY;

	float _x, _y;
	float _rndTimeCount;
	float _worldTimeCount;

	float _angle;
	float _startAngle;
	bool _die;
	
	float radius;
	POINT _center;
	virtual void move(void);
	virtual void draw(void);
	virtual void animation(void); 
	
public:
	virtual HRESULT init(void);
	virtual HRESULT init(const char* imageName, POINT position);
	virtual HRESULT init(const char* imageName, POINT position, float startAngle);
	void release(void);
	virtual void update(void);
	virtual void render(void);
	RECT getPos() { return _rc; }

	bool getDie() { return _die; }
	void setDie(bool die) { _die = die; }
	Enemy(void);
	~Enemy(void) {}

};

/*void move(void);
void draw(void);
*/

/*
	if (_rndTimeCount + _worldTimeCount <= GetTickCount())
	{
		_worldTimeCount = GetTickCount();
		_currentFrameX++;
		if (_image->getMaxFrameX() < _currentFrameX)
		{
			_currentFrameX = 0;
		}
	}
*/