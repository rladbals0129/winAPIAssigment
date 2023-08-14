#include "stdafx.h"
#include "TileMap.h"

HRESULT TileMap::init(void)
{

	_size = 10;

	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < _size; j++)
		{
			TagTile tile;
			ZeroMemory(&tile, sizeof(TagTile));
		
			_imgsPerTile = 2;
			
			tile.x = static_cast<float>(j) * (static_cast<float>(WINSIZE_X) / static_cast<float>(_size));
			tile.y = static_cast<float>(i)  * (static_cast<float>(WINSIZE_Y) / static_cast<float>(_size));
			
			tile.rc = RectMake(tile.x, tile.y, WINSIZE_X / _size, WINSIZE_Y / _size);
			
			_vTile.push_back(tile);

			
		}
	}
	int numTiles = _size * _size;
	_imgsPerTile = 2;
	for (int i = 0; i < _imgsPerTile; i++)
	{
		int randIndex = RND->getInt(numTiles);
		if (_vTile[randIndex].img == nullptr)
		{
			_vTile[randIndex].img = new GImage;
			_vTile[randIndex].img->init("Resources/Images/TileMap/Rocket.bmp",
				_vTile[randIndex].rc.right - _vTile[randIndex].rc.left, _vTile[randIndex].rc.bottom - _vTile[randIndex].rc.top);
		}
		else
		{
			i--;
		}
	}
	random_shuffle(_vTile.begin(), _vTile.end());
	return S_OK;
}

void TileMap::release(void)
{
}

void TileMap::update(void)
{


	
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (!selectedTile)
		{
			for (_viTile = _vTile.begin(); _viTile != _vTile.end(); ++_viTile)
			{
				if (PtInRect(&_viTile->rc, _ptMouse) && _viTile->img != nullptr)
				{
					selectedTile = &(*_viTile);
					break;
				}
			}
		}
		if (selectedTile) 
		{
			selectedTile->x = static_cast<float>(_ptMouse.x - (WINSIZE_X / _size) / 2);
			selectedTile->y = static_cast<float>(_ptMouse.y - (WINSIZE_Y / _size) / 2);
		}
	}
	
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		selectedTile = nullptr; 


	}
	
}

void TileMap::render(void)
{
	
	for (_viTile = _vTile.begin(); _viTile != _vTile.end(); ++_viTile)
	{
		DrawRectMake(getMemDC(), _viTile->rc);

		if (_viTile->img != nullptr && &(*_viTile) != selectedTile)
		{
			_viTile->img->render(getMemDC(),
				_viTile->rc.left,
				_viTile->rc.top,
				static_cast<float>(WINSIZE_X) / static_cast<float>(_size),
				static_cast<float>(WINSIZE_Y) / static_cast<float>(_size));
		}
	}

	
	if (selectedTile && selectedTile->img)
	{
		selectedTile->img->render(getMemDC(),
			static_cast<float>(_ptMouse.x) - (static_cast<float>(WINSIZE_X) / static_cast<float>(_size)) / 2,
			static_cast<float>(_ptMouse.y) - (static_cast<float>(WINSIZE_Y) / static_cast<float>(_size)) / 2,
			static_cast<float>(WINSIZE_X) / static_cast<float>(_size),
			static_cast<float>(WINSIZE_Y) / static_cast<float>(_size));
	}
}
