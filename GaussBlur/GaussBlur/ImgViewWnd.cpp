#include "stdafx.h"
#include "ImgViewWnd.h"
#include <stdlib.h>

//子窗口的窗口过程

LRESULT CALLBACK ImgViewWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LPIMG_INFO pInfo = NULL;
	if(message != WM_NCCREATE)
	{
		pInfo = (LPIMG_INFO)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		if(pInfo == NULL)
			return FALSE;
	}

	switch (message)
	{
	case WM_NCCREATE: //实际上窗口收到的第一条消息，分配指针的时机
		{
			pInfo = (LPIMG_INFO)malloc(sizeof(IMG_INFO));
			memset(pInfo, 0, sizeof(IMG_INFO));
			SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pInfo);
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;

	case WM_NCDESTROY:
		{
			if(pInfo != NULL)
				free(pInfo);
			SetWindowLongPtr(hWnd, GWLP_USERDATA, 0);
		}
		break;

	case WM_CREATE:
		{
			//禁用滚动条！
			SCROLLINFO si;
			si.cbSize = sizeof(SCROLLINFO);
			si.fMask = SIF_DISABLENOSCROLL //不需要滚动条时，禁用它，而不是隐藏
				| SIF_PAGE | SIF_POS | SIF_RANGE;
			si.nPos = 0;
			si.nMin = 0;
			si.nMax = 0;
			si.nPage = 2;
			SetScrollInfo(hWnd, SB_HORZ, &si, TRUE);
			SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
		}
		break;

	case WM_HSCROLL: //水平，垂直滚动条消息处理。
	case WM_VSCROLL:
		{
			BOOL bVert = (message == WM_VSCROLL);
			int nWhichBar = SB_VERT;
			int* pPos = &pInfo->y;

			if(!bVert)
			{
				nWhichBar = SB_HORZ;
				pPos = &pInfo->x;
			}

			SCROLLINFO si;
			si.cbSize = sizeof(SCROLLINFO);
			si.fMask = SIF_RANGE | SIF_PAGE;
			GetScrollInfo(hWnd, nWhichBar, &si);

			//设置pageup/down 的移动尺寸（略比pagesize小一点点）
			int page_unit = max(4, si.nPage - 24);
			switch(LOWORD(wParam))
			{
			case SB_PAGEDOWN :
				*pPos += page_unit;
				if(*pPos > (int)(si.nMax - (si.nPage - 1)))
					*pPos = si.nMax - (si.nPage - 1);
				break;
			case SB_LINEDOWN :
				*pPos += 16;
				if(*pPos > (int)(si.nMax - (si.nPage - 1)))
					*pPos = si.nMax - (si.nPage - 1);
				break;

			case SB_PAGEUP :
				*pPos -= page_unit;
				if(*pPos < 0)
					*pPos = 0;
				break;

			case SB_LINEUP :
				*pPos -= 16;
				if(*pPos < 0)
					*pPos = 0;
				break;

			case SB_TOP :
				*pPos = 0;
				break;

			case SB_BOTTOM :
				*pPos = si.nMax - (si.nPage - 1);
				break;

			case SB_THUMBPOSITION :
			case SB_THUMBTRACK :
				*pPos = HIWORD(wParam);
				break;
			default :
				break;
			}
			si.fMask = SIF_POS;
			si.nPos = *pPos;
			SetScrollInfo(hWnd, nWhichBar, &si, TRUE) ;
			InvalidateRect(hWnd, NULL, FALSE);
		}
		return TRUE;

	case WM_ERASEBKGND:
		return TRUE;

	case WM_PAINT:
		{
			RECT rc, rcImg;
			PAINTSTRUCT ps;
			GetClientRect(hWnd, &rc);
			HDC hdc = BeginPaint(hWnd, &ps);
			
			if(pInfo->hBitmap != NULL)
			{
				rcImg.left = 0;
				rcImg.top = 0;
				rcImg.right = pInfo->bmWidth - pInfo->x;
				rcImg.bottom = pInfo->bmHeight - pInfo->y;

				HRGN hRgn1 = CreateRectRgn(0, 0, rc.right, rc.bottom);
				HRGN hRgn2 = CreateRectRgn(0, 0, rcImg.right, rcImg.bottom);
				CombineRgn(hRgn1, hRgn1, hRgn2, RGN_DIFF);
				FillRgn(hdc, hRgn1, (HBRUSH)GetStockObject(LTGRAY_BRUSH));

				DeleteObject(hRgn1);
				DeleteObject(hRgn2);

				HDC hdcMem = CreateCompatibleDC(hdc);

				HGDIOBJ hOldBm = SelectObject(hdcMem, pInfo->hBitmap);

				BitBlt(hdc, 0, 0, 
					pInfo->bmWidth - pInfo->x,
					pInfo->bmHeight - pInfo->y,
					hdcMem,
					pInfo->x,
					pInfo->y,
					SRCCOPY);

				SelectObject(hdcMem, hOldBm);
				DeleteDC(hdcMem);
			}
			else
			{
				FillRect(hdc, &rc, (HBRUSH)GetStockObject(LTGRAY_BRUSH));
			}
			//FrameRect(hdc, &rc, (HBRUSH)GetStockObject(DKGRAY_BRUSH));
			EndPaint(hWnd, &ps);
		}
		return TRUE;

		//大小变化时，重设滚动条
	case WM_SIZE:
		{
			if(pInfo->hBitmap == NULL)
				return TRUE;

			int width = LOWORD(lParam);
			int height = HIWORD(lParam);

			SCROLLINFO si;
			si.cbSize = sizeof(SCROLLINFO);

			//如果窗口足够大，则将滚动位置复位！
			si.fMask = SIF_DISABLENOSCROLL | SIF_PAGE | SIF_RANGE;
			si.nPage = width;
			si.nMin = 0;
			si.nMax = pInfo->bmWidth;
			
			if(width >= pInfo->bmWidth)
			{
				pInfo->x = 0;
				si.nPos = 0;
				si.fMask |= SIF_POS;
			}
			else if(pInfo->x + width >= pInfo->bmWidth)
			{
				pInfo->x = pInfo->bmWidth - width;
				si.nPos = pInfo->x;
				si.fMask |= SIF_POS;
			}
			SetScrollInfo(hWnd, SB_HORZ, &si, TRUE);


			//如果窗口足够大，则将滚动位置复位！
			si.fMask = SIF_DISABLENOSCROLL | SIF_PAGE | SIF_RANGE;
			si.nPage = height;
			si.nMin = 0;
			si.nMax = pInfo->bmHeight;
			if(height >= pInfo->bmHeight)
			{
				pInfo->y = 0;
				si.nPos = 0;
				si.fMask |= SIF_POS;
			}
			else if(pInfo->y + height >= pInfo->bmHeight)
			{
				pInfo->y = pInfo->bmHeight - height;
				si.nPos = pInfo->y;
				si.fMask |= SIF_POS;
			}
			SetScrollInfo(hWnd, SB_VERT, &si, TRUE);

			//客户区重绘
			InvalidateRect(hWnd, NULL, FALSE);
		}
		return TRUE;

	case WM_DESTROY:
		return TRUE;

		//
		// 对外接口：
		//

	case WM_SETIMGINFO:
		{
			LPIMG_INFO pNew = (LPIMG_INFO)lParam;
			RECT rc;
			GetClientRect(hWnd, &rc);

			memcpy(pInfo, pNew, sizeof(IMG_INFO));
			pInfo->x = 0;
			pInfo->y = 0;

			SCROLLINFO si;
			si.cbSize = sizeof(SCROLLINFO);
			si.fMask = SIF_DISABLENOSCROLL //不需要滚动条时，禁用它，而不是隐藏
				| SIF_PAGE | SIF_POS | SIF_RANGE;
			si.nPos = 0;

			si.nMin = 0;
			si.nMax = pInfo->bmWidth;
			si.nPage = rc.right;
			SetScrollInfo(hWnd, SB_HORZ, &si, TRUE);

			si.nMin = 0;
			si.nMax = pInfo->bmHeight;
			si.nPage = rc.bottom;
			SetScrollInfo(hWnd, SB_VERT, &si, TRUE);

			InvalidateRect(hWnd, NULL, FALSE);
		}
		return TRUE;

		//得到位图的句柄
	case WM_GETIMGHANDLE:
		return (LRESULT) pInfo->hBitmap;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return FALSE;
}