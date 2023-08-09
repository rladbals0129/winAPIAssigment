#pragma once
class GImage
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0, LOAD_FILE,	//���ҽ�,����
		LOAD_EMPTY, LOAD_END				// �� ��Ʈ��, �ε�Done
	};

	typedef struct tagImage
	{
		DWORD	 resID;
		HDC		 hMemDC;
		HBITMAP  hBit;
		HBITMAP  hObit;
		float	 x;						//�̹��� x��ǥ
		float	 y;
		int		 width;
		int		 height;
		int		 currentFrameX;			//���� ������ x		//
		int		 currentFrameY;			//
		int		 maxFrameX;				//�ִ� ������ x ����
		int		 maxFrameY;				//
		int		 frameWidth;			//1������ ����ũ��
		int		 frameHeight;
		BYTE	 loadType;


		tagImage()
		{
			resID = 0;
			hMemDC = NULL;		//�ܵ����� ���� ���ǰ������� �������� ������ ������ߴ�
			hBit = NULL;		//�ܵ����� ���� ���ǰ������� �������� ������ ������ߴ�
			hObit = NULL;		//�ܵ����� ���� ���ǰ������� �������� ������ ������ߴ�
			x = y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
		}
	}IMAGE_INFO, *LPIMAGE_INFO; //������

private:
	LPIMAGE_INFO _imageInfo; //�̹��� ������ ���� ����ü
	char*		 _fileName; // �ε�����(������ ã�� ���� ����)
	bool		 _isTrans;  // (�̹����� �� ���� ó��) ����� �E���� � ������ �E���̳�. //���ٰ���?
	// - ����Ÿ �������� ����(��ȫ���) ����: ���ӿ��� ���� �Ⱦ��� �����̶�.
	COLORREF	 _transColor; //���� RGB�� (255,0,255)

	/*
	COLORREF - ��������
	-��������� ������ ǥ���� ���� ��ȣ���� 32��Ʈ ������
	�� R,G,B ���� 1����Ʈ(8��Ʈ) �̸� 0~255������ ���� ǥ���ϴµ� ����ȭ �Ǿ��ִ�.
	*/

	BLENDFUNCTION _blendFunc;	//���ĺ��忡 ���� ��� (����)
	LPIMAGE_INFO _blendImage;   // ���ĺ��� �̹���  (����)
	//������ �ʱ�� �Լ��� �ʿ��ϴ�.

public:
	//�̹��� �ʺ���̷� �ʱ�ȭ
	HRESULT init(int width, int height);

	//�̹��� ���ҽ��� �ʱ�ȭ									BOOL -> c��� �����迭�� bool�� ���������� ������
	HRESULT init(const DWORD resID, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	//�̹��� ���Ϸ� �ʱ�ȭ
	HRESULT init(const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	//BOOL �� �ϸ� �ȵǴ����� -> BOOL������ �����迭�� 
//																Ȯ���̱� ������ ��ǻ�Ͱ� ������ �ν�
	HRESULT init(const char* fileName, float x, float y, int width, int height,
		bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));		//�ѹ� ���� ���� �ȹٲٴ¾ֵ�
	// �� ex) ��� ��, ������ӵ��� ��浵 ���������ִ�

	HRESULT init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY,
		bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	HRESULT init(const char* fileName, float x, float y, int width, int height,
		int maxFrameX, int maxFrameY,
		bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));



	HRESULT initForAlphaBlend(void);
	//���� �÷�Ű ����
	void setTransColor(bool isTrans, COLORREF transColor);
	//����
	void release(void);

	//����
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY); //��x�� ��y
	void render(HDC hdc, int destX, int destY, int destWidth, int destHight);
	//�̹���Ŭ���� (�߶�׸���)
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHight);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHight, int destWidth, int destHight);
	
	//dx, ��� ����x,����y ,�ڸ��κ� ����x,����y, ũ��xũ��y
	//���ķ��� BYTE 0~255
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHight, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY,int destWidth,int destHight, int sourX, int sourY, int sourWidth, int sourHight, BYTE alpha);


	//===================������ ����=================== �׷����¹���� ��ٷο����״� �ζ����Լ����߰��غ���
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	//=================��������=====================
	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY); //ex) ���ð��� ���, ���װ��� ��� (Ȱ���ϸ� ī�޶�������)
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	// ==�ζ����Լ�==
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }
	
	inline float getX(void) { return _imageInfo->x; }
	inline void setX(float x) { _imageInfo->x = x; }

	inline float getY(void) { return _imageInfo->y; }
	inline void setY(float y) { _imageInfo->y = y; }

	//�̹��� ������ǥ
	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}
	//�̹��� ���μ���ũ��
	inline int getWidth(void) { return _imageInfo->width; }
	inline int getHeight(void) { return _imageInfo->height; }

	//�ٿ���ڽ�(�浹�뷺Ʈ) �������� ���̴� �浹ü�� �����ϱ����� (����Ƽ box collider)
	inline RECT boundimgBox(void)
	{
		RECT rc =
		{
			(int)_imageInfo->x,
			(int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->width,
			(int)_imageInfo->y + _imageInfo->height
		};

		return rc;
	}


	//�ٿ���ڽ�(�浹�뷺Ʈ)
	inline RECT boundimgBoxWithFrame(void)
	{
		RECT rc =
		{
			(int)_imageInfo->x,
			(int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->frameWidth,
			(int)_imageInfo->y + _imageInfo->frameHeight
		};

		return rc;
	}


	//===�����ӿ� ���� �ζ���
	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}

	}
	//������ x y�� max�� �Ѿ�� max�� �����ش�
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }
	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}

	}

	//�̹��� 1�����ӿ� ���� ���μ���ũ��
	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }

	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

	//�ִ� ������ xy ����
	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }

	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }

	


	
	GImage(); // �����ڴ� ���� �Ҹ��ڸ� �Ⱦ��� ����? -> �߻�ü�⶧���� 
	~GImage() {}
};


