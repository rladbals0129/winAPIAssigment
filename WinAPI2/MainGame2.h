#pragma once
#include "GameNode.h"

enum CURRENT_RECT1
{
	CURRENTRECT_A, CURRENTRECT_B,
	CURRENTRECT_C, CURRENTRECT_D,
	CURRENTRECT_E, CURRENTRECT_F,
	CURRENTRECT_G, CURRENTRECT_H,
	CURRENTRECT_I, CURRENTRECT_J,
	CURRENTRECT_K, CURRENTRECT_L,
	CURRENTRECT_M, CURRENTRECT_N,
	CURRENTRECT_O, CURRENTRECT_P,
	CURRENTRECT_NULL
};

enum HAMMER
{
	HAMMER_IDLE,HAMMER_ATTACK
};

class MainGame2 : public GameNode
{
private:
	GImage* _bgImage;
	GImage* _plImage[3];
	GImage* _msImage[2];
	CURRENT_RECT1 _currentRect;
	HAMMER _hammer;
	
	RECT _rc[16];
	RECT _mouse;
	POINT _mousePT;
	int _index;
	int _count;
	int _time;
	int _score;

	bool _bIsSelected;
	bool _bIsOnceCheck;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

