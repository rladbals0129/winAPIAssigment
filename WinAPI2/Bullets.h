#pragma once
#include "GameNode.h"

#define BULLETS_COUNT 4.0f

//���� �Ѿ˾��� ���� �Ѿ˾���.. ���ð��ӿ��� �翬�ϴ�. ����Ǵ� Ư������ ��������
//����� ������ �������ִ°� ����
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

//�Ѿ��� ���갴ü. �������� ��� �߻�ȴ�
//��� �Ѿ��� ������ : �����̰�, �׷�����, �浹�Ѵ�

//�迭ó�� �̸� ������ �صΰ� �߻�
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

// �߻簡 �ɶ����� ����� ����
class MissileM1 : public GameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
	float _range;

	int _bulletMax; // �����̵����� �ʱ⶧���� �ʿ�

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