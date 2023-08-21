#pragma once
#include "GameNode.h"
#include "PNGRender.h"
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
	int _diePosX;
	int _diePosY;


	float radius;
	POINT _center;
	virtual void move(void);
	virtual void draw(void);
	virtual void animation(void); 
	
private:
	PNGRender* _effectPNGRender;
	int _effectCurrentFrameX;
	int _effectCurrentFrameY;
	bool _effectPlaying;
	int _animationSpeed;
	int _animationCount;

public:
	virtual HRESULT init(void);
	virtual HRESULT init(const char* imageName, POINT position);
	virtual HRESULT init(const char* imageName, POINT position, float startAngle);
	void release(void);
	virtual void update(void);
	virtual void render(void);

	void playEffect();

	RECT getRect(void) { return _rc; }


	int getDiePosX() { return _diePosX; }
	int getDiePosY() { return _diePosY; }


	bool getDie() { return _die; }
	void setDie(bool die) { _die = die; _diePosX =_rc.left - 80; _diePosY = _rc.top - 50; if (die) playEffect(); }
	bool isEffectPlaying(){ return _effectPlaying; }
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