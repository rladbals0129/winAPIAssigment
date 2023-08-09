#pragma once
#include "GameNode.h"
#include <math.h>
#define PI 3.141592
#define REDIAN(dig) ((dig) * PI) / 180.0f

struct TIMER
{
	int x;
	int y;
};

class MainGame6 : public GameNode
{
private:
	TIMER _second;
	TIMER _minute;
	TIMER _hour;
	int currentX, currentY;
	int _redius;
	SYSTEMTIME _st;

public:

	HRESULT init();
	void release(void);
	void update(void);
	void render(void);
};

