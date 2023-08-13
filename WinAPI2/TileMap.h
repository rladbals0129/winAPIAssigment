#pragma once
#include "GameNode.h"

struct TagTile
{
	GImage* img;
	RECT rc;
	float x, y;
};


class TileMap : public GameNode
{
private:
	TagTile* selectedTile;
	vector<TagTile> _vTile;
	vector<TagTile>::iterator _viTile;

	int _size;
	int _imgCnt;

	int _imgsPerTile;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

