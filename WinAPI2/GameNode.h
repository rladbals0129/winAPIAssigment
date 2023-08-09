#pragma once
#include "GImage.h"

static GImage* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZE_X, WINSIZE_Y);

class GameNode
{
private:
	//GImage* _DoubleBuffer;
	//void setDoubleBuffer(void);
	HDC _hdc;
	bool _managerInit;
public:
	virtual HRESULT init(void);
	virtual HRESULT init(bool managerInit);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	//GImage* getDoubleBuffer(void) { return _DoubleBuffer; }
	
	GImage* getBackBuffer(void) { return _backBuffer; }

	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }
	
	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);


	virtual ~GameNode();
};

