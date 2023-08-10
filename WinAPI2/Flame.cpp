#include "stdafx.h"
#include "Flame.h"

HRESULT Flame::init(void)
{
	_idx = 0;
	_cnt = 0;
	IMAGEMANAGER->addFrameImage("��", "Resources/Images/ShootingGame/Player/Flame.bmp",
		432, 297,
		9, 1,
		true,
		RGB(255, 0, 255));

	return S_OK;
}

void Flame::release(void)
{
}

void Flame::update(void)
{
	FlameRender();
}

void Flame::render()
{
	IMAGEMANAGER->frameRender("��",getMemDC(), *_posX-25, *_posY+25, _idx, 0);
}

void Flame::FlameRender()
{
	_cnt++;
	if (_cnt % 3 == 0)
	{
		_idx++;
		if (_idx > 8)
		{
			_idx = 0;
		}
	}
}


/*
����1. ���Ͽ� flame�̹��� �߰�

- Flame �̹����� ���������� ������ ��Ų��.

�� Flame Ŭ�������� ���Ͽ� ���� ������ ������ �ȵǸ� MainGame ���� Flame�� ���� ������ �� �ʿ䰡 ����.

- ���Ͽ� �÷����� �־�ߵǳ�?

����2.


*/