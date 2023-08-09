#pragma once
#include "GameNode.h"
#include <math.h>
#define PI 3.141592
#define REDIAN(dig)  ((dig) * PI) / 180.0f
#define WORM_MAX 20
#define ITEM_MAX 20
struct CREATE
{
	float startX;
	float startY;
	float endX;
	float endY;
	float angleMove;
};

struct WORM
{
	bool fire;
	RECT rc;
	float startX;
	float startY;
	float angle;
	float speed;
	int collisionX;
	int collisionY;
	int centerX, centerY;
};

struct ITEM
{
	int idxNum;
	bool spon;
	bool eat;
	RECT rc;
	int rndL, rndT;
	int sizeX, sizeY;
};


class MainGame13 : public GameNode
{
private:
	int _redius;
	int _currentX, _currentY;
	CREATE _creat;
	WORM _worm[WORM_MAX];
	ITEM _item[ITEM_MAX];
	int _cnt;
	int _createStop;
	char _strNum[128];
	int _stop;
	RECT _collider;
	int _itemCnt;
	

public:

	HRESULT init();
	void release(void);
	void update(void);
	void render(void);


	void fireWorm(void);
	void sponItem(void);
	//void spon
	

};

