#pragma once

#define WC_IMGVIEW			_T("ImageViewWnd_20150521")

#define WM_SETIMGINFO		(WM_USER + 101) //设置图片信息
#define WM_GETIMGHANDLE		(WM_USER + 102) //获取位图的句柄

typedef struct tagIMG_INFO
{
	int x; //滚动视图的当前偏移量
	int y;
	HBITMAP hBitmap;
	LPVOID lpBits; //位图数据
	int bmWidth;
	int bmHeight;
	int bpp;
} IMG_INFO, *LPIMG_INFO;

LRESULT CALLBACK ImgViewWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);