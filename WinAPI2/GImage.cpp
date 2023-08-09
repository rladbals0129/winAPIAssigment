#include "stdafx.h"
#include "GImage.h"


GImage::GImage() :_imageInfo(nullptr),
_fileName(nullptr),
_isTrans(false),
_transColor(RGB(0, 0, 0)),
_blendImage(NULL)
{


}

HRESULT GImage::init(int width, int height) //dc�� ����?? dc�� ���;��ҰŰ�����
{
	if (_imageInfo != nullptr) this->release(); //�� �ʱ�ȭ ����. Ȥ�� �����ִٸ� �̻����� �������� �������ϰ� �����ض�

	HDC hdc = GetDC(_hWnd); //������ ����getdc ��ȭ���� �׷����������� �� �ȿ��ִ� ������ �ٲ��ټ��ִ� ����dc

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
	_imageInfo->hMemDC = CreateCompatibleDC(hdc); //�� �޸�dc �����ž�?
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hObit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit); //����������Ʈ�� �׸���.
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = nullptr; //���������°� �����ε����� �Ʒ� ���� ����

	_isTrans = false;
	_transColor = RGB(0, 0, 0);

	//���ҽ��� �����µ� �����ߴٸ�
	if (_imageInfo->hBit == 0) //-> �̰� ������ �̹��� ������ �������� �ƹ��볪 ������� �����
	{
		release();
		return E_FAIL;// �� ȣ���ϸ鼭 ��������
	}

	ReleaseDC(_hWnd, hdc);
	return S_OK;
}


//�̹��� ���̵�� �̹��� �ҷ�����
HRESULT GImage::init(const DWORD resID, int width, int height, bool isTrans, COLORREF transColor)
{
	if (_imageInfo != nullptr) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;

	_imageInfo->loadType = LOAD_RESOURCE;
	_imageInfo->resID = resID;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc); //�� �޸�dc �����ž�?
	_imageInfo->hBit = (HBITMAP)LoadBitmap(_hInstance, MAKEINTRESOURCE(_imageInfo->resID)); //
	_imageInfo->hObit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit); //����������Ʈ�� �׸���.
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = nullptr; //���������°� �����ε����� �Ʒ� ���� ����

	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ��� �����µ� �����ߴٸ�
	if (_imageInfo->hBit == 0) //-> �̰� ������ �̹��� ������ �������� �ƹ��볪 ������� �����
	{
		release();
		return E_FAIL;// �� ȣ���ϸ鼭 ��������
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

//���ϳ������� �̹��� �ҷ�����
HRESULT GImage::init(const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	if (_imageInfo != nullptr) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;

	_imageInfo->loadType = LOAD_RESOURCE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc); //�� �޸�dc �����ž�?
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE); //
	_imageInfo->hObit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit); //����������Ʈ�� �׸���.
	_imageInfo->width = width;
	_imageInfo->height = height;

	int len = strlen(fileName);
	_fileName = new char[len + 1];
	//strcpy -> ����1�� �� �߰�
	//�� �������� ����/���ڿ����� ������ ������ �ذ��� �Լ�
	// strcpy_s: (������� ����,�ִ����,����)
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ��� �����µ� �����ߴٸ�
	if (_imageInfo->hBit == 0) //-> �̰� ������ �̹��� ������ �������� �ƹ��볪 ������� �����
	{
		release();
		return E_FAIL;// �� ȣ���ϸ鼭 ��������
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
	_imageInfo->hMemDC = CreateCompatibleDC(hdc); //�� �޸�dc �����ž�?
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE); //
	_imageInfo->hObit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit); //����������Ʈ�� �׸���.
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;

	int len = strlen(fileName);
	_fileName = new char[len + 1];
	//strcpy -> ����1�� �� �߰�
	//�� �������� ����/���ڿ����� ������ ������ �ذ��� �Լ�
	// strcpy_s: (������� ����,�ִ����,����)
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ��� �����µ� �����ߴٸ�
	if (_imageInfo->hBit == 0) //-> �̰� ������ �̹��� ������ �������� �ƹ��볪 ������� �����
	{
		release();
		return E_FAIL;// �� ȣ���ϸ鼭 ��������
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
	_imageInfo->hMemDC = CreateCompatibleDC(hdc); //�� �޸�dc �����ž�?
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE); //
	_imageInfo->hObit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit); //����������Ʈ�� �׸���.
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
	//strcpy -> ����1�� �� �߰�
	//�� �������� ����/���ڿ����� ������ ������ �ذ��� �Լ�
	// strcpy_s: (������� ����,�ִ����,����)
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ��� �����µ� �����ߴٸ�
	if (_imageInfo->hBit == 0) //-> �̰� ������ �̹��� ������ �������� �ƹ��볪 ������� �����
	{
		release();
		return E_FAIL;// �� ȣ���ϸ鼭 ��������
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
	_imageInfo->hMemDC = CreateCompatibleDC(hdc); //�� �޸�dc �����ž�?
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE); //
	_imageInfo->hObit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit); //����������Ʈ�� �׸���.
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
	//strcpy -> ����1�� �� �߰�
	//�� �������� ����/���ڿ����� ������ ������ �ذ��� �Լ�
	// strcpy_s: (������� ����,�ִ����,����)
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ��� �����µ� �����ߴٸ�
	if (_imageInfo->hBit == 0) //-> �̰� ������ �̹��� ������ �������� �ƹ��볪 ������� �����
	{
		release();
		return E_FAIL;// �� ȣ���ϸ鼭 ��������
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

// ���İ� �̹��� ����(����)
HRESULT GImage::initForAlphaBlend(void)	//�V��
{
	HDC hdc = GetDC(_hWnd);


	//���ĺ��� �ɼ�
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;	//�⺻���� �������ϰ� ���İ����� �̹����� ��� ó���Ұų�? ->��ó���ϰڴ�
	_blendFunc.BlendOp = AC_SRC_OVER;	//�������ִ� �ҽ� �״�� �׸��ڴ� -(note)
	//_blendFunc.SourceConstantAlpha = 0; // �׳� �� ��������� ���İ� �ְڴ�. ��ó��
					//�� �츰 ��Ȳ���°� ���İ��� �ʿ��ϴ� ��ó��

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_FILE;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc); //�� �޸�dc �����ž�?
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height); // ???????????
	_blendImage->hObit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit); //����������Ʈ�� �׸���.
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

//Ư�� �̹������� �ſ��߿�. �̹����� �뷮�� ũ�� ������
void GImage::release(void)
{
	//������Ʈ
	if (_imageInfo)
	{
		//�̹��� ����
		SelectObject(_imageInfo->hMemDC, _imageInfo->hObit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		//������ ������
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE_ARRAY(_fileName);

		//���� �÷�Ű �ʱ�ȭ 
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
		// GdiTransparentBlt() : ��Ʈ���� �ҷ��ö� Ư�� ������ �����ϰ� �����Ѵ�.
		GdiTransparentBlt
		(
			hdc,							// ������ ����� DC (ȭ��DC)
			0,								// ������ ����� ȭ�� ����x
			0,								// ������ ����� ȭ�� ����y
			_imageInfo->width,				// ����� �̹��� ����ũ��
			_imageInfo->height,				// ����� �̹��� ����ũ��
			_imageInfo->hMemDC,				// ����� ��� DC
			0, 0,							// ����������� 0,0 x,y
			_imageInfo->width,				// ����� ���� ����ũ��
			_imageInfo->height,				// ����� ���� ����ũ��
			_transColor						// �����Ҷ� ������ ����(����Ÿ����)
		);
	}

	else
	{
		// �� BitBlt() : DC���� �������� ���� ��� ���縦 ���ش�.
		// �� SRCCOPY: �ҽ� ������ ������ �����Ѵ�.
		BitBlt(hdc, 0, 0, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void GImage::render(HDC hdc, int destX, int destY)
{
	if (_isTrans)
	{
		// GdiTransparentBlt() : ��Ʈ���� �ҷ��ö� Ư�� ������ �����ϰ� �����Ѵ�.
		GdiTransparentBlt
		(
			hdc,							// ������ ����� DC (ȭ��DC)
			destX,							// ������ ����� ȭ�� ����x
			destY,							// ������ ����� ȭ�� ����y
			_imageInfo->width,				// ����� �̹��� ����ũ��
			_imageInfo->height,				// ����� �̹��� ����ũ��
			_imageInfo->hMemDC,				// ����� ��� DC
			0, 0,							// ����������� 0,0 x,y
			_imageInfo->width,				// ����� ���� ����ũ��
			_imageInfo->height,				// ����� ���� ����ũ��
			_transColor						// �����Ҷ� ������ ����(����Ÿ����)
		);
	}

	else
	{
		// �� BitBlt() : DC���� �������� ���� ��� ���縦 ���ش�.
		// �� SRCCOPY: �ҽ� ������ ������ �����Ѵ�.
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void GImage::render(HDC hdc, int destX, int destY, int destWidth, int destHight)
{
	if (_isTrans)
	{
		// GdiTransparentBlt() : ��Ʈ���� �ҷ��ö� Ư�� ������ �����ϰ� �����Ѵ�.
		GdiTransparentBlt
		(
			hdc,							// ������ ����� DC (ȭ��DC)
			destX,							// ������ ����� ȭ�� ����x
			destY,							// ������ ����� ȭ�� ����y
			destWidth,				// ����� �̹��� ����ũ��
			destHight,				// ����� �̹��� ����ũ��
			_imageInfo->hMemDC,				// ����� ��� DC
			0, 0,							// ����������� 0,0 x,y
			_imageInfo->width,				// ����� ���� ����ũ��
			_imageInfo->height,				// ����� ���� ����ũ��
			_transColor						// �����Ҷ� ������ ����(����Ÿ����)
		);
	}

	else
	{
		// �� BitBlt() : DC���� �������� ���� ��� ���縦 ���ش�.
		// �� SRCCOPY: �ҽ� ������ ������ �����Ѵ�.
		BitBlt(hdc, destX, destY, destWidth, destHight, _imageInfo->hMemDC, 0, 0, SRCCOPY);
	}

}
//Ŭ���� : ������������ �����ؼ� ����,���� ũ�⸦ �߶� ���� ���ϴ� ���� �����ϰڴ�
void GImage::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHight)
{													//�������x �������y
	if (_isTrans)
	{
		// GdiTransparentBlt() : ��Ʈ���� �ҷ��ö� Ư�� ������ �����ϰ� �����Ѵ�.
		GdiTransparentBlt
		(
			hdc,							// ������ ����� DC (ȭ��DC)
			destX,							// ������ ����� ȭ�� ����x
			destY,							// ������ ����� ȭ�� ����y
			sourWidth,				// ����� �̹��� ����ũ��
			sourHight,				// ����� �̹��� ����ũ��
			_imageInfo->hMemDC,				// ����� ��� DC
			sourX, sourY,							// ����������� 0,0 x,y
			sourWidth,				// ����� ���� ����ũ��
			sourHight,				// ����� ���� ����ũ��
			_transColor						// �����Ҷ� ������ ����(����Ÿ����)
		);
	}
	else
	{
		// �� BitBlt() : DC���� �������� ���� ��� ���縦 ���ش�.
		// �� SRCCOPY: �ҽ� ������ ������ �����Ѵ�.
		BitBlt(hdc, destX, destY, sourWidth, sourHight, _imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void GImage::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHight, int destWidth, int destHight)
{
	if (_isTrans)
	{
		// GdiTransparentBlt() : ��Ʈ���� �ҷ��ö� Ư�� ������ �����ϰ� �����Ѵ�.
		GdiTransparentBlt
		(
			hdc,							// ������ ����� DC (ȭ��DC)
			destX,							// ������ ����� ȭ�� ����x
			destY,							// ������ ����� ȭ�� ����y
			destWidth,				// ����� �̹��� ����ũ��
			destHight,				// ����� �̹��� ����ũ��
			_imageInfo->hMemDC,				// ����� ��� DC
			sourX, sourY,							// ����������� 0,0 x,y
			sourWidth,				// ����� ���� ����ũ��
			sourHight,				// ����� ���� ����ũ��
			_transColor						// �����Ҷ� ������ ����(����Ÿ����)
		);
	}
	else
	{
		// �� BitBlt() : DC���� �������� ���� ��� ���縦 ���ش�.
		// �� SRCCOPY: �ҽ� ������ ������ �����Ѵ�.
		BitBlt(hdc, destX, destY, destWidth, destHight, _imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void GImage::alphaRender(HDC hdc, BYTE alpha)
{
	//�� ���ĺ��� ó������? �׷� �ʱ�ȭ���� ��
	if (!_blendImage) initForAlphaBlend();

	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		//1. ����ؾߵ� dc�� �׷����ִ� ������ ���� �̹����� �׸���
		BitBlt
		(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			hdc,
			0, 0,
			SRCCOPY
		); //��Ӻ���

		//2. ���� �̹����� ����� ���� �� ���� �̹����� �׸���

		GdiTransparentBlt
		(

			_blendImage->hMemDC,							// ������ ����� DC (ȭ��DC)
			0, 0,							// ������ ����� ȭ�� ����x							// ������ ����� ȭ�� ����y
			_imageInfo->width,				// ����� �̹��� ����ũ��
			_imageInfo->height,				// ����� �̹��� ����ũ��
			_imageInfo->hMemDC,				// ����� ��� DC
			0, 0,							// ����������� 0,0 x,y
			_imageInfo->width,				// ����� ���� ����ũ��
			_imageInfo->height,				// ����� ���� ����ũ��
			_transColor
		);

		//3. ���� �̹����� ȭ�鿡 �׷��ش�.
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
{//�� ���ĺ��� ó������? �׷� �ʱ�ȭ���� ��
	if (!_blendImage) initForAlphaBlend();

	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		//1. ����ؾߵ� dc�� �׷����ִ� ������ ���� �̹����� �׸���
		BitBlt
		(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			hdc,
			destX, destY,
			SRCCOPY
		); //��Ӻ���

		//2. ���� �̹����� ����� ���� �� ���� �̹����� �׸���

		GdiTransparentBlt
		(

			_blendImage->hMemDC,							// ������ ����� DC (ȭ��DC)
			0, 0,							// ������ ����� ȭ�� ����x							// ������ ����� ȭ�� ����y
			_imageInfo->width,				// ����� �̹��� ����ũ��
			_imageInfo->height,				// ����� �̹��� ����ũ��
			_imageInfo->hMemDC,				// ����� ��� DC
			0, 0,							// ����������� 0,0 x,y
			_imageInfo->width,				// ����� ���� ����ũ��
			_imageInfo->height,				// ����� ���� ����ũ��
			_transColor
		);

		//3. ���� �̹����� ȭ�鿡 �׷��ش�.
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
		); //��Ӻ���

		//2. ���� �̹����� ����� ���� �� ���� �̹����� �׸���

		GdiTransparentBlt
		(

			_blendImage->hMemDC,			// ������ ����� DC (ȭ��DC)
			0, 0,							// ������ ����� ȭ�� ����x							// ������ ����� ȭ�� ����y
			sourWidth,				// ����� �̹��� ����ũ��
			sourHight,				// ����� �̹��� ����ũ��
			_imageInfo->hMemDC,				// ����� ��� DC
			sourX, sourY,							// ����������� 0,0 x,y
			sourWidth,				// ����� ���� ����ũ��
			sourHight,				// ����� ���� ����ũ��
			_transColor
		);

		//3. ���� �̹����� ȭ�鿡 �׷��ش�.
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
		); //��Ӻ���

		//2. ���� �̹����� ����� ���� �� ���� �̹����� �׸���

		GdiTransparentBlt
		(

			_blendImage->hMemDC,			// ������ ����� DC (ȭ��DC)
			0, 0,							// ������ ����� ȭ�� ����x							// ������ ����� ȭ�� ����y
			destWidth,				// ����� �̹��� ����ũ��
			destHight,				// ����� �̹��� ����ũ��
			_imageInfo->hMemDC,				// ����� ��� DC
			sourX, sourY,							// ����������� 0,0 x,y
			sourWidth,				// ����� ���� ����ũ��
			sourHight,				// ����� ���� ����ũ��
			_transColor
		);

		//3. ���� �̹����� ȭ�鿡 �׷��ش�.
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
{//�̹��� ����ó��
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

	//�׷����� ���� ���ð�
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	RECT rcDest;//�׷����� dc���� (ȭ��ũ��)

	//�׷��� �� ����
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
//������� -> ���� 2���� �Ἥ ����� ���̿� �ϳ��ǹ��۸��־�д�.
//������ ->���� ���̾� �ڿ� ���۸� �̸� �׷����´�

//? �ٸ������. ������ ��𸦰����ұ�?