#pragma once
#include "GameNode.h"
#include <math.h>

#define PI 3.141592
#define REDIAN(dig)  ((dig) * PI) / 180.0f
#define BULLET_MAX 20
struct CANNON
{
	int startX;
	int startY;
	int endX;
	int endY;
	float angleMove;
};

struct BULLET
{
	bool fire;
	RECT rc;
	int startX;
	int startY;
	int angle;
	float speed;
	int collisionX;
	int collisionY;
	float gravity;

};


class MainGame10 : public GameNode
{
private:
	int _redius;
	int _currentX, _currentY;


	CANNON _cannon;
	BULLET _bullet[BULLET_MAX];
public:
	HRESULT init();
	void release(void);
	void update(void);
	void render(void);

	void fireBullet(void);


};

