#pragma once
#include "GameNode.h"
#include "Flame.h"
#include "Bullets.h"

#define ROCKET_SPEED 3.0f

enum EWeapon
{
	MISSILE,BEAM
};

class Rocket : public GameNode
{
private:
	GImage* _image; 
	Flame* _flame;



	//skill
	EWeapon _setWeapon;
	MissileM1* _missile;
	Beam* _beam;
	bool _beamIrradiation;


	RECT _rc;
	float _x, _y;

	

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();

	void usingSkill();

	MissileM1* getMissileM1() { return _missile; }
	Beam* getBeam() { return _beam; }
	RECT getRect(void) { return _rc; }
	void removeMissile(int arrNum);
};
