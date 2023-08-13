#pragma once
#include "GameNode.h"
#include "Flame.h"
#include "Bullets.h"
#define ROCKET_SPEED 3.0f

class Rocket : public GameNode
{
private:
	GImage* _image; 
	Flame* _flame;
	Missile* _missile;

	RECT _rc;
	float _x, _y;

	

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();
};
