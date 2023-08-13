#pragma once
#include "GameNode.h"

#define FLAME_COUNT 4.0f

class Flame : public GameNode
{
private:
	GImage* _image;
	RECT _rc;
	float* _posX = nullptr;
	float* _posY = nullptr;

	float _flameTick;
public:
	HRESULT init(const char* imageName , float* x, float* y);
	void release(void);
	void update(void);
	void render();




};

