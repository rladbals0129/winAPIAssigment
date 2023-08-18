#include "stdafx.h"
#include "ShootingMap.h"

void ShootingMap::collision(void)
{
	for (int i = 0; i < _rocket->getMissileM1()->getBullets().size(); i++)
	{
		for (int j = 0; j < _em->getMinions().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_rocket->getMissileM1()->getBullets()[i].rc,
				&CollisionAreaResizing(_em->getMinions()[j]->getRect(), 40, 30)))
			{
				_rocket->removeMissile(i);
				_em->removeMinion(j);
				break;
			}
		}
	}

	for (int i = 0; i < _rocket->getBeam()->getBullets().size(); i++)
	{
		for (int j = 0; j < _em->getMinions().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_rocket->getBeam()->getBullets()[i].rc,
				&CollisionAreaResizing(_em->getMinions()[j]->getRect(), 40, 30)))
			{
				
				_em->removeMinion(j);
				break;
			}
		}
	}
}

