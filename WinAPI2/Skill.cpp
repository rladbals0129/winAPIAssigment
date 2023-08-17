#include "stdafx.h"
#include "Skill.h"

HRESULT MissileShotGun::init(int bulletMax, float range)
{
	
	_numPellets = 3;
	_pelletSpread = 5;
	
	Missile::init(bulletMax, range);
	/*Missile::InitSettings initSettings;
	initSettings.bulletMax = _numPellets;
	initSettings.range = _range;*/

	return S_OK;
}

void MissileShotGun::release(void)
{
	Missile::release();
}

void MissileShotGun::update(void)
{
	Missile::update();
    //cout << "업데이트" << endl;
}

void MissileShotGun::render()
{
	Missile::render();
    //cout << "랜더" << endl;
}

void MissileShotGun::fire(float x, float y)
{
    float centralAngle = getAngle(x, y, _ptMouse.x, _ptMouse.y);

    for (int i = 0; i < _numPellets; ++i)
    {
        float angleOffset = _pelletSpread * (i - _numPellets / 2.0f);
        float finalAngle = centralAngle + angleOffset;

        // 총알을 발사합니다.
        for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
        {
            if (_viBullet->fire) continue;

            _viBullet->angle = finalAngle;
            Missile::fire(x, y);
            break;
        }
    }
	//Missile::fire(x, y);
}

void MissileShotGun::move(void)
{
	Missile::move();
}
