#include "stdafx.h"
#include "GImage.h"


GImage::GImage() :_imageInfo(nullptr),
_fileName(nullptr),
_isTrans(false),
_transColor(RGB(0, 0, 0)),
_blendImage(NULL)
{


}

HRESULT GImage::init(int width, int height) //dc가 없네?? dc를 얻어와야할거같은데
{
	if (_imageInfo != nullptr) this->release(); //재 초기화 방지. 혹시 값이있다면 이상한짓 하지말고 릴리즈하고 접근해라

	HDC hdc = GetDC(_hWnd); //권한이 낮은getdc 도화지가 그려지고있으면 그 안에있는 내용을 바꿔줄수있는 서브dc

	_imageInfo = new IMAGE_INFO;

	/*
		resID = 0;
		hMemDC = NULL;
		hBit = NULL;
		hObit = NULL;
		width = 0;
		heidht = 0;
		loadType = LOAD_RESOURCE;
	*/

	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc); //너 메모리dc 뭐쓸거야?
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hObit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit); //셀렉오브젝트로 그린다.
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = nullptr; //파일을쓰는건 오버로딩으로 아래 따로 있음

	_isTrans = false;
	_transColor = RGB(0, 0, 0);

	//리소스를 얻어오는데 실패했다면
	if (_imageInfo->hBit == 0) //-> 이게 없으면 이미지 없을때 랜덤으로 아무대나 오류찍고 종료댐
	{
		release();
		return E_FAIL;// 얘 호출하면서 꺼버려라
	}

	ReleaseDC(_hWnd, hdc);
	return S_OK;
}


//이미지 아이디로 이미지 불러오기
HRESULT GImage::init(const DWORD resID, int width, int height, bool isTrans, COLORREF transColor)
{
	if (_imageInfo != nullptr) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;

	_imageInfo->loadType = LOAD_RESOURCE;
	_imageInfo->resID = resID;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc); //너 메모리dc 뭐쓸거야?
	_imageInfo->hBit = (HBITMAP)LoadBitmap(_hInstance, MAKEINTRESOURCE(_imageInfo->resID)); //
	_imageInfo->hObit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit); //셀렉오브젝트로 그린다.
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = nullptr; //파일을쓰는건 오버로딩으로 아래 따로 있음

	_isTrans = isTrans;
	_transColor = transColor;

	//리소스를 얻어오는데 실패했다면
	if (_imageInfo->hBit == 0) //-> 이게 없으면 이미지 없을때 랜덤으로 아무대나 오류찍고 종료댐
	{
		release();
		return E_FAIL;// 얘 호출하면서 꺼버려라
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

//파일네임으로 이미지 불러오기
HRESULT GImage::init(const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	if (_imageInfo != nullptr) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;

	_imageInfo->loadType = LOAD_RESOURCE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc); //너 메모리dc 뭐쓸거야?
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE); //
	_imageInfo->hObit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit); //셀렉오브젝트로 그린다.
	_imageInfo->width = width;
	_imageInfo->height = height;

	int len = strlen(fileName);
	_fileName = new char[len + 1];
	//strcpy -> 인자1개 더 추가
	//ㄴ 고질적인 문자/문자열에서 사이즈 문제를 해결한 함수
	// strcpy_s: (복사받을 변수,최대길이,원본)
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	//리소스를 얻어오는데 실패했다면
	if (_imageInfo->hBit == 0) //-> 이게 없으면 이미지 없을때 랜덤으로 아무대나 오류찍고 종료댐
	{
		release();
		return E_FAIL;// 얘 호출하면서 꺼버려라
	}

	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

HRESULT GImage::init(const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	if (_imageInfo != nullptr) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;

	_imageInfo->loadType = LOAD_RESOURCE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc); //너 메모리dc 뭐쓸거야?
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE); //
	_imageInfo->hObit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit); //셀렉오브젝트로 그린다.
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;

	int len = strlen(fileName);
	_fileName = new char[len + 1];
	//strcpy -> 인자1개 더 추가
	//ㄴ 고질적인 문자/문자열에서 사이즈 문제를 해결한 함수
	// strcpy_s: (복사받을 변수,최대길이,원본)
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	//리소스를 얻어오는데 실패했다면
	if (_imageInfo->hBit == 0) //-> 이게 없으면 이미지 없을때 랜덤으로 아무대나 오류찍고 종료댐
	{
		release();
		return E_FAIL;// 얘 호출하면서 꺼버려라
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT GImage::init(const char * fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
	if (_imageInfo != nullptr) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;

	_imageInfo->loadType = LOAD_RESOURCE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc); //너 메모리dc 뭐쓸거야?
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE); //
	_imageInfo->hObit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit); //셀렉오브젝트로 그린다.
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = maxFrameX - 1;
	_imageInfo->maxFrameY = maxFrameY - 1;
	_imageInfo->frameWidth = width / maxFrameX;
	_imageInfo->frameHeight = height / maxFrameY;

	int len = strlen(fileName);
	_fileName = new char[len + 1];
	//strcpy -> 인자1개 더 추가
	//ㄴ 고질적인 문자/문자열에서 사이즈 문제를 해결한 함수
	// strcpy_s: (복사받을 변수,최대길이,원본)
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	//리소스를 얻어오는데 실패했다면
	if (_imageInfo->hBit == 0) //-> 이게 없으면 이미지 없을때 랜덤으로 아무대나 오류찍고 종료댐
	{
		release();
		return E_FAIL;// 얘 호출하면서 꺼버려라
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT GImage::init(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
	if (_imageInfo != nullptr) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;

	_imageInfo->loadType = LOAD_RESOURCE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc); //너 메모리dc 뭐쓸거야?
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE); //
	_imageInfo->hObit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit); //셀렉오브젝트로 그린다.
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = maxFrameX - 1;
	_imageInfo->maxFrameY = maxFrameY - 1;
	_imageInfo->frameWidth = width / maxFrameX;
	_imageInfo->frameHeight = height / maxFrameY;

	int len = strlen(fileName);
	_fileName = new char[len + 1];
	//strcpy -> 인자1개 더 추가
	//ㄴ 고질적인 문자/문자열에서 사이즈 문제를 해결한 함수
	// strcpy_s: (복사받을 변수,최대길이,원본)
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	//리소스를 얻어오는데 실패했다면
	if (_imageInfo->hBit == 0) //-> 이게 없으면 이미지 없을때 랜덤으로 아무대나 오류찍고 종료댐
	{
		release();
		return E_FAIL;// 얘 호출하면서 꺼버려라
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

// 알파값 이미지 세팅(투명도)
HRESULT GImage::initForAlphaBlend(void)	//셑팅
{
	HDC hdc = GetDC(_hWnd);


	//알파블랜드 옵션
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;	//기본적인 원본파일과 알파가빠진 이미지를 어떻게 처리할거냐? ->후처리하겠다
	_blendFunc.BlendOp = AC_SRC_OVER;	//원본에있는 소스 그대로 그리겠다 -(note)
	//_blendFunc.SourceConstantAlpha = 0; // 그냥 값 집어넣으면 알파값 주겠다. 선처리
					//ㄴ 우린 상황에맞게 알파값이 필요하다 후처리

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_FILE;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc); //너 메모리dc 뭐쓸거야?
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height); // ???????????
	_blendImage->hObit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit); //셀렉오브젝트로 그린다.
	_blendImage->width = WINSIZE_X;
	_blendImage->height = WINSIZE_Y;

	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

void GImage::setTransColor(bool isTrans, COLORREF transColor)
{
	_isTrans = isTrans;
	_transColor = transColor;
}

//특히 이미지에선 매우중요. 이미지는 용량이 크기 때문에
void GImage::release(void)
{
	//안전벨트
	if (_imageInfo)
	{
		//이미지 삭제
		SelectObject(_imageInfo->hMemDC, _imageInfo->hObit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		//포인터 뺴는중
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE_ARRAY(_fileName);

		//투명 컬러키 초기화 
		_isTrans = false;
		_transColor = RGB(0, 0, 0);
	}

	if (_blendImage)
	{
		SelectObject(_blendImage->hMemDC, _blendImage->hObit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);

		SAFE_DELETE(_blendImage);
	}
}

void GImage::render(HDC hdc)
{
	if (_isTrans)
	{
		// GdiTransparentBlt() : 비트맵을 불러올때 특정 색상을 제외하고 복사한다.
		GdiTransparentBlt
		(
			hdc,							// 복사할 장소의 DC (화면DC)
			0,								// 복사할 장소의 화면 시작x
			0,								// 복사할 장소의 화면 시작y
			_imageInfo->width,				// 복사될 이미지 가로크기
			_imageInfo->height,				// 복사될 이미지 세로크기
			_imageInfo->hMemDC,				// 복사될 대상 DC
			0, 0,							// 복사시작지점 0,0 x,y
			_imageInfo->width,				// 복사될 영역 가로크기
			_imageInfo->height,				// 복사될 영역 세로크기
			_transColor						// 복사할때 제외할 색상(마젠타색상)
		);
	}

	else
	{
		// ◆ BitBlt() : DC간의 영역끼리 서로 고속 복사를 해준다.
		// ㄴ SRCCOPY: 소스 영역을 영역에 복사한다.
		BitBlt(hdc, 0, 0, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void GImage::render(HDC hdc, int destX, int destY)
{
	if (_isTrans)
	{
		// GdiTransparentBlt() : 비트맵을 불러올때 특정 색상을 제외하고 복사한다.
		GdiTransparentBlt
		(
			hdc,							// 복사할 장소의 DC (화면DC)
			destX,							// 복사할 장소의 화면 시작x
			destY,							// 복사할 장소의 화면 시작y
			_imageInfo->width,				// 복사될 이미지 가로크기
			_imageInfo->height,				// 복사될 이미지 세로크기
			_imageInfo->hMemDC,				// 복사될 대상 DC
			0, 0,							// 복사시작지점 0,0 x,y
			_imageInfo->width,				// 복사될 영역 가로크기
			_imageInfo->height,				// 복사될 영역 세로크기
			_transColor						// 복사할때 제외할 색상(마젠타색상)
		);
	}

	else
	{
		// ◆ BitBlt() : DC간의 영역끼리 서로 고속 복사를 해준다.
		// ㄴ SRCCOPY: 소스 영역을 영역에 복사한다.
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void GImage::render(HDC hdc, int destX, int destY, int destWidth, int destHight)
{
	if (_isTrans)
	{
		// GdiTransparentBlt() : 비트맵을 불러올때 특정 색상을 제외하고 복사한다.
		GdiTransparentBlt
		(
			hdc,							// 복사할 장소의 DC (화면DC)
			destX,							// 복사할 장소의 화면 시작x
			destY,							// 복사할 장소의 화면 시작y
			destWidth,				// 복사될 이미지 가로크기
			destHight,				// 복사될 이미지 세로크기
			_imageInfo->hMemDC,				// 복사될 대상 DC
			0, 0,							// 복사시작지점 0,0 x,y
			_imageInfo->width,				// 복사될 영역 가로크기
			_imageInfo->height,				// 복사될 영역 세로크기
			_transColor						// 복사할때 제외할 색상(마젠타색상)
		);
	}

	else
	{
		// ◆ BitBlt() : DC간의 영역끼리 서로 고속 복사를 해준다.
		// ㄴ SRCCOPY: 소스 영역을 영역에 복사한다.
		BitBlt(hdc, destX, destY, destWidth, destHight, _imageInfo->hMemDC, 0, 0, SRCCOPY);
	}

}
//클리핑 : 원본ㅇ미지를 지정해서 가로,세로 크기를 잘라서 내가 원하는 곳에 랜더하겠다
void GImage::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHight)
{													//복사시작x 복사시작y
	if (_isTrans)
	{
		// GdiTransparentBlt() : 비트맵을 불러올때 특정 색상을 제외하고 복사한다.
		GdiTransparentBlt
		(
			hdc,							// 복사할 장소의 DC (화면DC)
			destX,							// 복사할 장소의 화면 시작x
			destY,							// 복사할 장소의 화면 시작y
			sourWidth,				// 복사될 이미지 가로크기
			sourHight,				// 복사될 이미지 세로크기
			_imageInfo->hMemDC,				// 복사될 대상 DC
			sourX, sourY,							// 복사시작지점 0,0 x,y
			sourWidth,				// 복사될 영역 가로크기
			sourHight,				// 복사될 영역 세로크기
			_transColor						// 복사할때 제외할 색상(마젠타색상)
		);
	}
	else
	{
		// ◆ BitBlt() : DC간의 영역끼리 서로 고속 복사를 해준다.
		// ㄴ SRCCOPY: 소스 영역을 영역에 복사한다.
		BitBlt(hdc, destX, destY, sourWidth, sourHight, _imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void GImage::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHight, int destWidth, int destHight)
{
	if (_isTrans)
	{
		// GdiTransparentBlt() : 비트맵을 불러올때 특정 색상을 제외하고 복사한다.
		GdiTransparentBlt
		(
			hdc,							// 복사할 장소의 DC (화면DC)
			destX,							// 복사할 장소의 화면 시작x
			destY,							// 복사할 장소의 화면 시작y
			destWidth,				// 복사될 이미지 가로크기
			destHight,				// 복사될 이미지 세로크기
			_imageInfo->hMemDC,				// 복사될 대상 DC
			sourX, sourY,							// 복사시작지점 0,0 x,y
			sourWidth,				// 복사될 영역 가로크기
			sourHight,				// 복사될 영역 세로크기
			_transColor						// 복사할때 제외할 색상(마젠타색상)
		);
	}
	else
	{
		// ◆ BitBlt() : DC간의 영역끼리 서로 고속 복사를 해준다.
		// ㄴ SRCCOPY: 소스 영역을 영역에 복사한다.
		BitBlt(hdc, destX, destY, destWidth, destHight, _imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void GImage::alphaRender(HDC hdc, BYTE alpha)
{
	//너 알파블랜드 처음쓰니? 그럼 초기화부터 해
	if (!_blendImage) initForAlphaBlend();

	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		//1. 출력해야될 dc에 그려져있는 내용을 블랜드 이미지에 그린다
		BitBlt
		(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			hdc,
			0, 0,
			SRCCOPY
		); //고속복사

		//2. 원본 이미지의 배경을 없앤 후 블랜드 이미지에 그린다

		GdiTransparentBlt
		(

			_blendImage->hMemDC,							// 복사할 장소의 DC (화면DC)
			0, 0,							// 복사할 장소의 화면 시작x							// 복사할 장소의 화면 시작y
			_imageInfo->width,				// 복사될 이미지 가로크기
			_imageInfo->height,				// 복사될 이미지 세로크기
			_imageInfo->hMemDC,				// 복사될 대상 DC
			0, 0,							// 복사시작지점 0,0 x,y
			_imageInfo->width,				// 복사될 영역 가로크기
			_imageInfo->height,				// 복사될 영역 세로크기
			_transColor
		);

		//3. 블랜드 이미지를 화면에 그려준다.
		AlphaBlend
		(
			hdc,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc
		);

	}
	else
	{
		AlphaBlend(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}

}
void GImage::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{//너 알파블랜드 처음쓰니? 그럼 초기화부터 해
	if (!_blendImage) initForAlphaBlend();

	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		//1. 출력해야될 dc에 그려져있는 내용을 블랜드 이미지에 그린다
		BitBlt
		(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			hdc,
			destX, destY,
			SRCCOPY
		); //고속복사

		//2. 원본 이미지의 배경을 없앤 후 블랜드 이미지에 그린다

		GdiTransparentBlt
		(

			_blendImage->hMemDC,							// 복사할 장소의 DC (화면DC)
			0, 0,							// 복사할 장소의 화면 시작x							// 복사할 장소의 화면 시작y
			_imageInfo->width,				// 복사될 이미지 가로크기
			_imageInfo->height,				// 복사될 이미지 세로크기
			_imageInfo->hMemDC,				// 복사될 대상 DC
			0, 0,							// 복사시작지점 0,0 x,y
			_imageInfo->width,				// 복사될 영역 가로크기
			_imageInfo->height,				// 복사될 영역 세로크기
			_transColor
		);

		//3. 블랜드 이미지를 화면에 그려준다.
		AlphaBlend
		(
			hdc,
			destX, destY,
			_imageInfo->width,
			_imageInfo->height,
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc
		);

	}
	else
	{
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}


}

void GImage::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHight, BYTE alpha)
{
	if (!_blendImage) initForAlphaBlend();

	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		BitBlt
		(
			_blendImage->hMemDC,
			0, 0,
			sourWidth,
			sourHight,
			hdc,
			destX, destY,
			SRCCOPY
		); //고속복사

		//2. 원본 이미지의 배경을 없앤 후 블랜드 이미지에 그린다

		GdiTransparentBlt
		(

			_blendImage->hMemDC,			// 복사할 장소의 DC (화면DC)
			0, 0,							// 복사할 장소의 화면 시작x							// 복사할 장소의 화면 시작y
			sourWidth,				// 복사될 이미지 가로크기
			sourHight,				// 복사될 이미지 세로크기
			_imageInfo->hMemDC,				// 복사될 대상 DC
			sourX, sourY,							// 복사시작지점 0,0 x,y
			sourWidth,				// 복사될 영역 가로크기
			sourHight,				// 복사될 영역 세로크기
			_transColor
		);

		//3. 블랜드 이미지를 화면에 그려준다.
		AlphaBlend
		(
			hdc,
			destX, destY,
			sourWidth,
			sourHight,
			_blendImage->hMemDC,
			0, 0,
			sourWidth,
			sourHight,
			_blendFunc
		);

	}
	else
	{
		AlphaBlend(hdc, destX, destY, sourWidth, sourHight,
			_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHight, _blendFunc);
	}
}
void GImage::alphaRender(HDC hdc, int destX, int destY, int destWidth, int destHight, int sourX, int sourY, int sourWidth, int sourHight, BYTE alpha)
{

	if (!_blendImage) initForAlphaBlend();

	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		BitBlt
		(
			_blendImage->hMemDC,
			0, 0,
			destWidth,
			destHight,
			hdc,
			destX, destY,
			SRCCOPY
		); //고속복사

		//2. 원본 이미지의 배경을 없앤 후 블랜드 이미지에 그린다

		GdiTransparentBlt
		(

			_blendImage->hMemDC,			// 복사할 장소의 DC (화면DC)
			0, 0,							// 복사할 장소의 화면 시작x							// 복사할 장소의 화면 시작y
			destWidth,				// 복사될 이미지 가로크기
			destHight,				// 복사될 이미지 세로크기
			_imageInfo->hMemDC,				// 복사될 대상 DC
			sourX, sourY,							// 복사시작지점 0,0 x,y
			sourWidth,				// 복사될 영역 가로크기
			sourHight,				// 복사될 영역 세로크기
			_transColor
		);

		//3. 블랜드 이미지를 화면에 그려준다.
		AlphaBlend
		(
			hdc,
			destX, destY,
			destWidth,
			destHight,
			_blendImage->hMemDC,
			0, 0,
			destWidth,
			destHight,
			_blendFunc
		);

	}
	else
	{
		AlphaBlend(hdc, destX, destY, destWidth, destHight,
			_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHight, _blendFunc);
	}


}
void GImage::frameRender(HDC hdc, int destX, int destY)
{
	if (_isTrans)
	{

		GdiTransparentBlt
		(
			hdc,
			destX,
			destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,			// 
			_imageInfo->currentFrameY * _imageInfo->frameHeight,			// 
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor
		);
	}
	else
	{
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX* _imageInfo->frameWidth, _imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}
void GImage::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{//이미지 예외처리
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	if (_isTrans)
	{

		GdiTransparentBlt
		(
			hdc,
			destX,
			destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX* _imageInfo->frameWidth,			// 
			_imageInfo->currentFrameY * _imageInfo->frameHeight,			// 
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor
		);
	}
	else
	{
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX* _imageInfo->frameWidth, _imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}
void GImage::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	if (offsetX < 0)
	{
		offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	}

	if (offsetY < 0)
	{
		offsetY = _imageInfo->height + (offsetY % _imageInfo->height);
	}

	//그려지는 영역 세팅값
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	RECT rcDest;//그려지는 dc영역 (화면크기)

	//그려야 할 영역
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		if (y + sourHeight > drawAreaH)
		{
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			render(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top, 
				sourWidth, sourHeight);
		}
	}


}
void GImage::loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{


}
//더블버퍼 -> 버퍼 2개를 써서 빈버퍼 사이에 하나의버퍼를넣어둔다.
//빽버퍼 ->버퍼 레이어 뒤에 버퍼를 미리 그려놓는다

//? 다만들었다. 다음엔 어디를가야할까?