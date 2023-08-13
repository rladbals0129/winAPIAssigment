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
	
		/*	if (_imgCnt < 2)
			{
				tile.img = new GImage;
				tile.img->init("Resources/Images/TileMap/Rocket.bmp",
					tile.rc.right - tile.rc.left, tile.rc.bottom - tile.rc.top);
			}
			else
			{
				tile.img = nullptr;
			}
			_imgCnt++;*/
		
			
			_vTile.push_back(tile);

			
		}
	}
	int numTiles = _size * _size;
	_imgsPerTile = 2; // 각 타일맵에 배치될 이미지 개수 설정
	for (int i = 0; i < _imgsPerTile; i++)
	{
		int randIndex = rand() % numTiles;
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
	POINT mousePos;
	GetCursorPos(&mousePos);
	ScreenToClient(_hWnd, &mousePos);

	// 마우스 왼쪽 버튼을 누르고 있는 경우
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (!selectedTile) // 이전에 선택된 타일이 없다면 새로운 타일을 선택
		{
			for (_viTile = _vTile.begin(); _viTile != _vTile.end(); ++_viTile)
			{
				if (PtInRect(&_viTile->rc, mousePos) && _viTile->img != nullptr)
				{
					selectedTile = &(*_viTile);
					break;
				}
			}
		}
		if (selectedTile) // 선택된 타일이 있는 경우 마우스 위치를 따라 이동
		{
			selectedTile->x = static_cast<float>(mousePos.x - (WINSIZE_X / _size) / 2);
			selectedTile->y = static_cast<float>(mousePos.y - (WINSIZE_Y / _size) / 2);
		}
	}
	// 마우스 버튼을 놓았을 때
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		selectedTile = nullptr; // 선택된 타일을 초기화
	}
	
}

void TileMap::render(void)
{
	//for (_viTile = _vTile.begin(); _viTile != _vTile.end(); ++_viTile)
	//{
	//	
	//	DrawRectMake(getMemDC(), _viTile->rc);
	//
	//	if (_viTile->img != nullptr)
	//	{
	//		_viTile->img->render(getMemDC(),
	//			_viTile->rc.left,
	//			 _viTile->rc.top,
	//			static_cast<float>(WINSIZE_X) / static_cast<float>(_size),
	//			static_cast<float>(WINSIZE_Y) / static_cast<float>(_size));
	//	}

	//}
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

	// 마우스 위치에 선택한 이미지를 그림
	if (selectedTile && selectedTile->img)
	{
		POINT mousePos;
		GetCursorPos(&mousePos);
		ScreenToClient(_hWnd, &mousePos);

		selectedTile->img->render(getMemDC(),
			static_cast<float>(mousePos.x) - (static_cast<float>(WINSIZE_X) / static_cast<float>(_size)) / 2,
			static_cast<float>(mousePos.y) - (static_cast<float>(WINSIZE_Y) / static_cast<float>(_size)) / 2,
			static_cast<float>(WINSIZE_X) / static_cast<float>(_size),
			static_cast<float>(WINSIZE_Y) / static_cast<float>(_size));
	}
}
