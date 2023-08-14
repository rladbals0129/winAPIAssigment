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
	
public:
	HRESULT init(void);
	HRESULT init(const char* imageName, POINT position);

	void release(void);
	void update(void);
	void render(void);
	Enemy(void);
	~Enemy(void) {}
	void draw(void);


};

/*void move(void);
void draw(void);
void animation(void);*/