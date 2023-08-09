#pragma once
#include "GameNode.h"
#define POOP_MAX 50

class Poop
{
private:
	bool isActive;
	RECT _rc;
	
public:
	void SetActive(bool active) { isActive = active; }
	bool IsActive() const { return isActive; }
	void SetRECT(RECT rc) { _rc = rc; }
	RECT getRECT() { return _rc; }
	HRESULT init();
	void release(void);
	void update(void);
	void render(HDC hdc);
};

