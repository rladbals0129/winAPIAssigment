#pragma once
#include "Bullets.h"

class MissileBase : public Missile
{

public:

	MissileBase() {}
	~MissileBase() {}
};


class MissileShotGun : public Missile
{
private:
	int _numPellets;
	float _pelletSpread;
	

public:


	HRESULT init(int bulletMax, float range) override;
	void release(void) override;
	void update(void) override;
	void render() override;

	void fire(float x, float y) override;
	void move(void) override;

	MissileShotGun() : _numPellets(0), _pelletSpread(0.0f) {}
	~MissileShotGun() {}
};