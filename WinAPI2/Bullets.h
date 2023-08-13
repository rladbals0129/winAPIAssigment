#pragma once
#include "GameNode.h"

#define BULLETS_COUNT 4.0f

//적도 총알쓰고 나도 총알쓰고.. 슈팅게임에선 당연하다. 공통되는 특성들을 적용하자
//기능을 묶었다 묶을수있는건 묶자
struct tagBullet
{
	GImage* img;
	RECT rc;
	int radius;
	int count;
	float x, y;
	float fireX, fireY;
	float angle;
	float speed;
	float frameTick;
	bool fire;
};

//총알은 서브객체. 누군가가 쏘면 발사된다
//모든 총알의 공통점 : 움직이고, 그려지고, 충돌한다

//배열처럼 미리 장전을 해두고 발사
class Missile : public GameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
	float _range;

public:
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render();

	void fire(float x, float y);
	void draw(void);
	void move(void);

	Missile() {}
	~Missile() {}


};

// 발사가 될때마다 만들고 삭제
class MissileM1 : public GameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
	float _range;

	int _bulletMax; // 장전이되있지 않기때문에 필요

public:
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render();

	void fire(float x, float y);
	void draw(void);
	void move(void);

	MissileM1() {}
	~MissileM1() {}


};