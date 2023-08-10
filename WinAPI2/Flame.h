#pragma once
#include "GameNode.h"

class Flame : public GameNode
{
private:
	float* _posX = nullptr;
	float* _posY = nullptr;

	int _cnt;
	int _idx;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();

	void setFlamePos(float* posX, float* posY)	
	{
		_posX = posX;
		_posY = posY;
	}

	void FlameRender();

};

