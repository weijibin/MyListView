#pragma once

#define WC_IMGVIEW			_T("ImageViewWnd_20150521")

#define WM_SETIMGINFO		(WM_USER + 101) //����ͼƬ��Ϣ
#define WM_GETIMGHANDLE		(WM_USER + 102) //��ȡλͼ�ľ��

typedef struct tagIMG_INFO
{
	int x; //������ͼ�ĵ�ǰƫ����
	int y;
	HBITMAP hBitmap;
	LPVOID lpBits; //λͼ����
	int bmWidth;
	int bmHeight;
	int bpp;
} IMG_INFO, *LPIMG_INFO;

LRESULT CALLBACK ImgViewWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);