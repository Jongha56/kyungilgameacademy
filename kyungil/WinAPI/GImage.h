#pragma once
class GImage
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0, LOAD_FILE,	//���ҽ��� �ε�, ���Ϸ� �ε�
		LOAD_EMPTY, LOAD_END		//�� ��Ʈ�� �ε�
	};

	/*
	BYTE: unsigned char
	WORD: unsigned short
	DWORD: unsigned long
	*/
	typedef struct tagImage
	{
		DWORD		resID;		//���ҽ� ID
		HDC			hMemDc;		//�޸� DC
		HBITMAP		hBit;		//��Ʈ��
		HBITMAP		hOBit;		//�õ� ��Ʈ��

		float      x;		     //�̹��� x��ǥ(����Ʈ)
		float      y;		    //�̹��� y��ǥ(ž)
		int			width;		//�̹��� ����ũ��
		int			height;		//�̹��� ����ũ��
		int			currentFrameX; //���� ������ x��ǥ
		int			currentFrameY; // ���� ������ y��ǥ
		int         maxFrameX;		//�ִ������� x��ǥ
		int         maxFrameY;		// �ִ� ������ Y��ǥ
		int          frameWidth;     // 1���������� ����
		int          frameHeight;   // 1���� ������ ����

		BYTE		loadType;	//�̹��� �ε� Ÿ��



		tagImage()
		{
			resID = 0;
			hMemDc = nullptr;
			hBit = nullptr;
			hOBit = nullptr;
			x = 0;
			y = 0;
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
	}IMAGE_INFO, * LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;		//�̹��� ����
	char* _fileName;		//�̹��� �̸�
	bool			_isTrans;		//����
	COLORREF		_transColor;	//���� ���� RGB (RGB(255,0,255))

	BLENDFUNCTION _blendfunc;       // ���ĺ����� ���
	LPIMAGE_INFO  _blendImage;       // ���ĺ����� ���



	/*
	COLORREF
	�� ����������� ������ ǥ���ϱ� ���� COLORREF ��� ���������� ����Ѵ�.
		�� ��ȣ ���� 32��Ʈ ������
	�� R,G,B ���� 1����Ʈ(8��Ʈ)�̸� 0 ~ 255 ������ ��(ǥ��)�� ������.
	*/

public:
	//WinAPI �ڷ����� ȥ�յ� ����
	HRESULT init(int width, int height);
	//bool isTrans = false���� bool�� BOOL�� �ٲٸ� �Լ� �����ε� ��Ģ�� �ɷ� �Ʒ� �Լ��� ȣ���Ѵ�.
	//�Լ� �����ε� ��Ģ ����.
	HRESULT init(const DWORD resID, int width, int height, bool isTrans = false,
		COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, int width, int height, bool isTrans = false,
		COLORREF transColor = RGB(0, 0, 0));
	//  ������ �̹��� ���Ϸ� �ʱ�ȭ
	// �������
	HRESULT init(const char* fileName, float x, float y, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	HRESULT init(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY,
		// ���� Ȯ��
		bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	HRESULT initforAlphaBlend(void);



	void setTransColor(bool isTrans, COLORREF transColor);

	void release(void);

	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);

	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);
	void alphaRender(HDC hdc, BYTE alpha); // byte ~ 255���� ǥ��
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha); // ����Ʈ
	//�̹���, �̹���(��ġ��), ���ĺ�����, ������, �ִϸ��̼�, Ŭ����(����ȭ - �ø�(3D))
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	//�� offset: ȭ���� �Ű��ִ� �ӵ�
	//�� ���� �̵��ϸ� �߶� �ű�� �۾�
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);


	// ===========
	// �ζ��� �Լ�
	// ==========


	inline HDC getMemDC(void) { return _imageInfo->hMemDc; }
	inline float getX(void) { return _imageInfo->x; }
	inline void setX(float x) { _imageInfo->x = x; }

	// 
	inline float getY(void) { return _imageInfo->y; }
	inline void setY(float y) { _imageInfo->y = y; }


	// �̹��� ������ǥ
	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x = (_imageInfo->width / 2);
		_imageInfo->y = y = (_imageInfo->height / 2);


	}

	// �̹��� ����, ����ũ��
	inline int getWidth(void) { return _imageInfo->width; }
	inline int getHegiht(void) { return _imageInfo->height; }

	// �ٿ�� �ڽ� (�浹�� ��Ʈ)
	inline RECT boundingBox(void)
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

	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}

	}
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }
	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}

	}
	// �̹��� 1������ ����, ����
	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

	// �ִ������� x y����
	inline int getmaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getmaxFrameY(void) { return _imageInfo->maxFrameY; }

	HBITMAP getHBit() { return _imageInfo->hBit; }




	GImage();
	~GImage() {}
};
