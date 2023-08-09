#pragma once
#include "GameNode.h"
class Player
{
private :
	RECT _rc;
	bool _isActive;
public:
	HRESULT init();
	void release(void);
	void update(void);
	void render(HDC hdc);

	void setRect(RECT rc) { _rc = rc; }
	RECT getRect() { return _rc; }
};

